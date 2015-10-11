/*
 * Application.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include <core/Application.h>
#include <core/IFactory.h>
#include <core/module/Module.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/reporting/IssueReporter.h>
#include <core/logging/Logger.h>
#include <core/transformation/TransformationHandler.h>
#include <core/issue/filter/IFilter.h>
#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/filter/Filtering.h>
#include <core/utility/Util.h>

//#include <external/ReplacementHandling.h>

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include <llvm/Support/Path.h>
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Program.h"
#include <limits.h>
#include <algorithm>

namespace opov {

Application::Application()  {

}

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
  for (auto module : modules) {
    executor->setModule(module);
    int sig = tool.run(actionFactory.get());
    if (sig == 1) {
      /*LOG_ERROR("Module '" << module->moduleName() << "' failed.");*/
      // return sig;
    }
  }

  TUIssuesMap& issuesMap = ihandler->getAllIssues();
  filter::Filtering filtering(filter.get());
  TUIssuesMap filteredMap = filtering.filter(issuesMap);

  reporter->addIssues(filteredMap);
  ihandler->clear();

  return sig;
}

int Application::executeOnCode(const std::string& source, const std::vector<std::string>& args) {
  int sig = 0;
  for (auto module : modules) {
    executor->setModule(module);
    int sig = clang::tooling::runToolOnCodeWithArgs(actionFactory->create(), source, args);
    if (sig < 1) {
      LOG_DEBUG("Module '" << module->moduleName() << "' failed.");
      return sig;
    }
  }

  TUIssuesMap& issuesMap = ihandler->getAllIssues();
  filter::Filtering filtering(filter.get());
  TUIssuesMap filteredMap = filtering.filter(issuesMap);

  reporter->addIssues(filteredMap);
  ihandler->clear();

  return sig;
}

void Application::addModule(Module* module) {
  LOG_DEBUG("Add module: " << module->moduleName());
  modules.push_back(module);
  module->init(config.get());
}

void Application::cleanUp() {
  for (auto module : modules) {
    delete module;
  }
  modules.clear();
}

std::string Application::getApplicationName() {
  return "GenericApplication";
}

Application::~Application() {
  cleanUp();
}

} /* namespace opov */
