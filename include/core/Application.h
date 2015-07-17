/*
 * Application.h
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string>
#include <vector>
#include <memory>

namespace clang {
namespace tooling {
class FrontendActionFactory;
class CompilationDatabase;
}
}

namespace opov {

class IFactory;
class Configuration;
class IssueReporter;
class IssueHandler;
class TransformationHandler;
class Module;

class Application {
 protected:
  std::unique_ptr<IFactory> executor;
  std::unique_ptr<Configuration> config;
  std::unique_ptr<IssueReporter> reporter;
  std::unique_ptr<clang::tooling::FrontendActionFactory> actionFactory;
  std::unique_ptr<IssueHandler> ihandler;
  std::unique_ptr<TransformationHandler> thandler;
  std::vector<Module*> modules;

  virtual void loadConfig() = 0;
  virtual void createReporter() = 0;
  virtual void createIssueHandler();
  virtual void createTransformationHandler();
  virtual void createFactory() = 0;
  virtual void createActionFactory();
  virtual void initModules() = 0;

 public:
  virtual void init();
  virtual void cleanUp();
  virtual int execute(const clang::tooling::CompilationDatabase& db, const std::vector<std::string>& sources);
  virtual int executeOnCode(const std::string& source,
                            const std::vector<std::string>& args = std::vector<std::string>());
  virtual void addModule(Module* module);
  virtual std::string getApplicationName();
  virtual ~Application();
};

} /* namespace opov */

#endif /* APPLICATION_H_ */
