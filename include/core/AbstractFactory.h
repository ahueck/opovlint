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
#include <vector>
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

class AbstractFactory : public IFactory {
 protected:
  Module* module;
  std::unique_ptr<ModuleContext> context;
  Configuration* config;
  std::string currentSource;
  IssueHandler* ihandler;
  TransformationHandler* thandler;

 public:
  AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
  bool handleBeginSource(clang::CompilerInstance& CI, llvm::StringRef Filename) override;
  void handleEndSource() override;
  void init() override;
  void setModule(Module* m) override;
  ~AbstractFactory() override;
};

} /* namespace opov */

#endif // CORE_ABSTRACTFACTORY_H
