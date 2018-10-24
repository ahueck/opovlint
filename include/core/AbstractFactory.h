/*
 * AbstractFactory.h
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#ifndef CORE_ABSTRACTFACTORY_H
#define CORE_ABSTRACTFACTORY_H

#include "IFactory.h"

#include <memory>
#include <string>

namespace clang {
class CompilerInstance;
} /* namespace clang */
namespace llvm {
class StringRef;
} /* namespace llvm */

namespace opov {

class Module;
class ModuleContext;
class Configuration;
class IssueHandler;
class TransformationHandler;
class ProgressMonitor;

class AbstractFactory : public IFactory {
 protected:
  Module* module;
  std::unique_ptr<ModuleContext> context;
  Configuration* config;
  std::string currentSource;
  IssueHandler* ihandler;
  TransformationHandler* thandler;
  ProgressMonitor* p_monitor{nullptr};

 public:
  AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
  bool handleBeginSource(clang::CompilerInstance& CI) override;
  void handleEndSource() override;
  void init() override;
  void setModule(Module* m) override;
  void setProgressMonitor(ProgressMonitor* p_monitor);
  ~AbstractFactory() override;
};

} /* namespace opov */

#endif  // CORE_ABSTRACTFACTORY_H
