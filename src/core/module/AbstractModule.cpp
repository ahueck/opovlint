/*
 * AbstractModule.cpp
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#include <core/module/AbstractModule.h>
#include <core/module/ModuleContext.h>
#include <core/configuration/Configuration.h>

#include <clang/AST/Stmt.h>
#include <clang/Basic/SourceManager.h>

namespace opov {

AbstractModule::AbstractModule() :
		context(nullptr) {

}

void AbstractModule::init(const Configuration* config) {
	setupOnce(config);
}

void AbstractModule::execute(ModuleContext* context) {
	this->context = context;
}

AbstractModule::~AbstractModule() {
}

} /* namespace opov */
