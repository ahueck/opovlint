/*
 * AbstractModuleConsumer.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef ABSTRACTMODULECONSUMER_H_
#define ABSTRACTMODULECONSUMER_H_

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
  void HandleTranslationUnit(clang::ASTContext& Context) override;
  virtual ~AbstractModuleConsumer();
};

} /* namespace opov */

#endif /* ABSTRACTMODULECONSUMER_H_ */
