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

AbstractModule::AbstractModule()
    : context(nullptr)
    , transform(false) {
}

void AbstractModule::init(const Configuration* config) {
  config->getValue("global:type", type_s);
  config->getValue("global:transform", transform, false);
  setupOnce(config);
}

void AbstractModule::execute(ModuleContext* context) {
  this->context = context;
}

AbstractModule::~AbstractModule() {
}

} /* namespace opov */
