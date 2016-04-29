/*
 * AbstractFactory.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef CORE_IFACTORY_H
#define CORE_IFACTORY_H

#include <clang/Tooling/Tooling.h>

namespace clang {
class AstConsumer;
} /* namespace clang */

namespace opov {

class Module;

class IFactory : public clang::tooling::SourceFileCallbacks {
 public:
  virtual void init() = 0;
  virtual void setModule(Module* m) = 0;
  virtual std::unique_ptr<clang::ASTConsumer> newASTConsumer() = 0;
  ~IFactory() override = default;
};

} /* namespace opov */

#endif // CORE_IFACTORY_H
