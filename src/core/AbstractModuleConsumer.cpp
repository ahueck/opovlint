/*
 * AbstractModuleConsumer.cpp
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#include <core/AbstractModuleConsumer.h>
#include <core/Logger.h>
#include <core/Configuration.h>
#include <core/Module.h>
#include <core/ModuleContext.h>

namespace opov {

AbstractModuleConsumer::AbstractModuleConsumer(
		Module* module, ModuleContext* mcontext) :
		module(module), mcontext(mcontext) {

}

void AbstractModuleConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
	//std::shared_ptr<ModuleContext> m_context = std::make_shared<ModuleContext>();
	mcontext->setASTContext(&Context);
	LOG_DEBUG(
			"AbstractModuleConsumer: Execute Module: " << module->moduleName());
	module->execute(mcontext);
}

AbstractModuleConsumer::~AbstractModuleConsumer() {
}

} /* namespace opov */
