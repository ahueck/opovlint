/*
 * Application.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include <core/Application.h>
#include <core/configuration/Configuration.h>
#include <core/IFactory.h>
#include <core/AbstractFactory.h>
#include <core/issue/IssueHandler.h>
#include <core/logging/Logger.h>
#include <core/module/Module.h>
#include <core/module/ModuleRegistry.h>
#include <core/reporting/IssueReporter.h>
#include <core/reporting/ProgressMonitor.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/Util.h>

#include <external/ReplacementHandling.h>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>
#include <llvm/Support/Regex.h>

#include <algorithm>
#include <limits.h>

namespace opov {

Application::Application() = default;

void Application::init() {
  loadConfig();
  createIssueHandler();
  createTransformationHandler();
  createReporter();
  createFactory();
  loadModules();
  initModules();
  createActionFactory();
}

void Application::createActionFactory() {
  actionFactory = clang::tooling::newFrontendActionFactory<AbstractFactory>(executor.get(), executor.get());
}

void Application::createIssueHandler() {
  ihandler = util::make_unique<IssueHandler>();
}

void Application::createTransformationHandler() {
  thandler = util::make_unique<TransformationHandler>();
}

int Application::execute(const clang::tooling::CompilationDatabase& db, const std::vector<std::string>& sources) {
  clang::tooling::ClangTool tool(db, sources);
  int sig = 0;

  bool show_progress;
  config->getValue("global:progress", show_progress, true);
  std::unique_ptr<ProgressMonitor> p_monitor;
  if (show_progress) {
    p_monitor = util::make_unique<ProgressMonitor>(modules.size() * sources.size());
    executor->setProgressMonitor(p_monitor.get());
  }

  ReplacementHandling replacementHandler;
  bool apply_replacements;
  std::string replacement_loc;
  config->getValue("replacement:location", replacement_loc);

  llvm::SmallVector<char, 32> path;
  path.append(replacement_loc.begin(), replacement_loc.end());
  llvm::sys::fs::make_absolute(path);
  std::string replacement_loc_abs(path.begin(), path.end());

  config->getValue("replacement:apply", apply_replacements);

  if (apply_replacements && !replacementHandler.findClangApplyReplacements("")) {
    LOG_ERROR("Could not find clang-apply-replacement");
    return 0;
  }

  for (auto& module : modules) {
    executor->setModule(module.get());
    int sig = tool.run(actionFactory.get());
    if (sig == 1) {
      // In case a module fails, we only notify
      LOG_DEBUG("Module '" << module->moduleName() << "' failed.");
    }
  }

  report();

  if (apply_replacements) {
    replacementHandler.setDestinationDir(replacement_loc_abs);
    if (!replacementHandler.serializeReplacements(thandler->getAllReplacements())) {
      LOG_DEBUG("Failed to serialize replacements");
    }

    if (!replacementHandler.applyReplacements()) {
      LOG_DEBUG("Failed to apply replacements");
    }
  }

  return sig;
}

int Application::executeOnCode(const std::string& source, const std::vector<std::string>& args) {
  for (auto& module : modules) {
    executor->setModule(module.get());
    const bool success = clang::tooling::runToolOnCodeWithArgs(actionFactory->create(), source, args);
    if (!success) {
      LOG_DEBUG("Module '" << module->moduleName() << "' failed.");
      return -1;
    }
  }

  report();

  return 0;
}

void Application::report() {
  auto issues = ihandler->getAllIssues();
  reporter->addIssues(issues);

  ihandler->clear();
}

void Application::loadModules() {
  using llvm::Regex;
  std::vector<std::string> module_globs;
  bool case_sensitive = false;
  config->getVector("global:modules:filter", module_globs);
  config->getValue("global:modules:case", case_sensitive, false);

  std::vector<Regex> module_filter;
  for (const auto& glob : module_globs) {
    module_filter.emplace_back(Regex(util::glob2regex(glob), !case_sensitive ? Regex::IgnoreCase : Regex::NoFlags));
  }

  for (const auto& entry : ModuleRegistry::entry_map()) {
    llvm::StringRef name(entry.first);
    auto i_pos = std::find_if(module_filter.begin(), module_filter.end(), [&](Regex& r) { return r.match(name); });
    if (i_pos != std::end(module_filter)) {
      addModule(entry.first);
    }
  }
}

bool Application::addModule(const std::string& name) {
  LOG_DEBUG("Adding module: " << name);
  auto module = ModuleRegistry::instance_of(name);
  if (module == nullptr) {
    LOG_DEBUG("Module does not exist in registry.");
    return false;
  }
  LOG_DEBUG("Succeeded");
  module->init(config.get());
  modules.push_back(std::move(module));

  return true;
}

void Application::initModules() {
}

void Application::cleanUp() {
}

std::string Application::getApplicationName() {
  return "GenericApplication";
}

Application::~Application() = default;

} /* namespace opov */
