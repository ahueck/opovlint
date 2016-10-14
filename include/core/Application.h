/*
 * Application.h
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include <memory>
#include <string>
#include <vector>

namespace clang {
namespace tooling {
class FrontendActionFactory;
class CompilationDatabase;
} /* namespace tooling */
} /* namespace clang */

namespace opov {

class IFactory;
class Configuration;
class IssueReporter;
class IssueHandler;
class TransformationHandler;
class Module;

class Application {
 private:
  bool addModule(const std::string& name);

 protected:
  std::unique_ptr<IFactory> executor;
  std::unique_ptr<Configuration> config;
  std::unique_ptr<IssueReporter> reporter;
  std::unique_ptr<clang::tooling::FrontendActionFactory> actionFactory;
  std::unique_ptr<IssueHandler> ihandler;
  std::unique_ptr<TransformationHandler> thandler;
  std::vector<std::unique_ptr<Module>> modules;

  virtual void loadConfig() = 0;
  virtual void createReporter() = 0;
  virtual void createIssueHandler();
  virtual void createTransformationHandler();
  virtual void createFactory() = 0;
  virtual void createActionFactory();
  virtual void loadModules();
  virtual void initModules();

 public:
  Application();
  virtual void init();
  virtual void cleanUp();
  virtual int execute(const clang::tooling::CompilationDatabase& db, const std::vector<std::string>& sources);
  virtual int executeOnCode(const std::string& source,
                            const std::vector<std::string>& args = std::vector<std::string>());
  virtual void report();
  virtual std::string getApplicationName();
  template <typename T, typename... Args>
  void addModule(Args&&... arguments);
  virtual ~Application();
};

} /* namespace opov */

#include "Application.hpp"

#endif  // CORE_APPLICATION_H
