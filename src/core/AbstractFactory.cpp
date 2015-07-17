/*
 * AbstractFactory.cpp
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#include <core/AbstractFactory.h>
#include <core/module/Module.h>
#include <core/module/ModuleContext.h>
#include <core/configuration/Configuration.h>
#include <core/reporting/IssueReporter.h>
#include <core/utility/Util.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/logging/Logger.h>

#include <clang/Frontend/CompilerInstance.h>
#include <llvm/ADT/StringRef.h>
#include <clang/Tooling/Refactoring.h>

namespace opov {

AbstractFactory::AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler)
    : module(nullptr)
    , config(config)
    , currentSource("")
    , ihandler(ihandler)
    , thandler(thandler) {
}

bool AbstractFactory::handleBeginSource(clang::CompilerInstance& CI, llvm::StringRef Filename) {
  currentSource = Filename;
  thandler->setSource(currentSource);
  thandler->setIncludeDirectives(new IncludeDirectives(CI));
  ihandler->setSource(currentSource);
  return true;
}

void AbstractFactory::handleEndSource() {
}

void AbstractFactory::setModule(Module* m) {
  this->module = m;
}

void AbstractFactory::init() {
  this->context = opov::util::make_unique<ModuleContext>(this->config, this->ihandler, this->thandler);
}

AbstractFactory::~AbstractFactory() {
}

} /* namespace opov */
