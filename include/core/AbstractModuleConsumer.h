/*
 * AbstractModuleConsumer.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef CORE_ABSTRACTMODULECONSUMER_H
#define CORE_ABSTRACTMODULECONSUMER_H

#include <clang/AST/ASTConsumer.h>

#include <vector>

namespace opov {

class Module;
class ModuleContext;

class AbstractModuleConsumer : public clang::ASTConsumer {
 protected:
  Module* module;
  ModuleContext* mcontext;

 public:
  AbstractModuleConsumer(Module* module, ModuleContext* mcontext);
  void Initialize(clang::ASTContext& Context) override;
  void HandleTranslationUnit(clang::ASTContext& Context) override;
  ~AbstractModuleConsumer() override;
};

} /* namespace opov */

#endif // CORE_ABSTRACTMODULECONSUMER_H
