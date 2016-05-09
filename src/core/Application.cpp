/*
 * Application.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include <core/Application.h>
#include <core/configuration/Configuration.h>
#include <core/IFactory.h>
#include <core/issue/filter/IFilter.h>
#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/IssueHandler.h>
#include <core/logging/Logger.h>
#include <core/module/Module.h>
#include <core/reporting/IssueReporter.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/Util.h>

#include <external/ReplacementHandling.h>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>

#include <algorithm>
#include <limits.h>

namespace opov {

Application::Application() = default;

void Application::init() {
  loadConfig();
  createIssueHandler();
  createFilter();
  createTransformationHandler();
  createReporter();
  createFactory();
  initModules();
  createActionFactory();
}

void Application::createActionFactory() {
  actionFactory = clang::tooling::newFrontendActionFactory<IFactory>(executor.get(), executor.get());
}

void Application::createIssueHandler() {
  ihandler = util::make_unique<IssueHandler>();
}

void Application::createFilter() {
  filter = util::make_unique<filter::UniqueFilter>();
}

void Application::createTransformationHandler() {
  thandler = util::make_unique<TransformationHandler>();
}

int Application::execute(const clang::tooling::CompilationDatabase& db, const std::vector<std::string>& sources) {
  clang::tooling::ClangTool tool(db, sources);
  int sig = 0;

  ReplacementHandling replacementHandler;
  bool apply_replacements;
  std::string replacement_loc;
  config->getValue("replacement:location", replacement_loc);
  config->getValue("replacement:apply", apply_replacements);

  if (!replacementHandler.findClangApplyReplacements("")) {
    LOG_ERROR("Could not find clang-apply-replacement");
    return 0;
  }

  for (auto& module : modules) {
    executor->setModule(module.get());
    int sig = tool.run(actionFactory.get());
    if (sig == 1) {
      /*LOG_ERROR("Module '" << module->moduleName() << "' failed.");*/
      // return sig;
    }
  }
  report();
  replacementHandler.setDestinationDir(replacement_loc);
  if (!replacementHandler.serializeReplacements(thandler->getAllReplacements())) {
    LOG_DEBUG("Failed to serialize replacements");
  }
  if (apply_replacements) {
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
  bool do_filter;
  config->getValue("global:filter", do_filter, false);
  TUIssuesMap& issuesMap = ihandler->getAllIssues();

  if (do_filter) {
    auto filteredSet = filter->apply(issuesMap);
    reporter->addIssues(filteredSet);
  } else {
    reporter->addIssues(issuesMap);
  }

  ihandler->clear();
}
/*
void Application::addModule(Module* module) {
  LOG_DEBUG("Add module: " << module->moduleName());
  modules.push_back(module);
  module->init(config.get());
}
*/

void Application::cleanUp() {
}

std::string Application::getApplicationName() {
  return "GenericApplication";
}

Application::~Application() = default;

} /* namespace opov */
