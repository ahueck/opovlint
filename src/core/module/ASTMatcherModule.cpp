/*
 * ASTMatcherModule.cpp
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#include <core/module/ASTMatcherModule.h>
#include <core/module/ModuleContext.h>

namespace opov {

ASTMatcherModule::ASTMatcherModule() {

}

void ASTMatcherModule::init(const Configuration* config) {
	setupOnce(config);
	setupMatcher();
}

void ASTMatcherModule::execute(ModuleContext* context) {
	AbstractModule::execute(context);
	//setupMatcher();
	finder.matchAST(context->getASTContext());
}

ASTMatcherModule::~ASTMatcherModule() {
}

} /* namespace opov */
