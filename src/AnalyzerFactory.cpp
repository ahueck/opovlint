/*
 * AnalyzerFactory.cpp
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#include <AnalyzerFactory.h>
#include <ModuleConsumer.h>
#include <core/logging/Logger.h>
#include <core/module/ModuleContext.h>
#include <core/configuration/Configuration.h>
#include <core/reporting/IssueReporter.h>

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

namespace opov {

AnalyzerFactory::AnalyzerFactory(Configuration *config, IssueHandler *ihandler, TransformationHandler *thandler)
    : AbstractFactory(config, ihandler, thandler) {
}

bool AnalyzerFactory::handleBeginSource(clang::CompilerInstance &CI, clang::StringRef Filename) {
  AbstractFactory::handleBeginSource(CI, Filename);
  LOG_DEBUG("Called AnalyzerFactory beginsource: " << CI.hasASTConsumer());
  return true;
}

void AnalyzerFactory::handleEndSource() {
  AbstractFactory::handleEndSource();
  LOG_DEBUG("Called AnalyzerFactory endsource.");
}

clang::ASTConsumer *AnalyzerFactory::newASTConsumer() {
  LOG_DEBUG("Called AnalyzerFactory: " << this);
  return new ModuleConsumer(module, context.get());
}

AnalyzerFactory::~AnalyzerFactory() {
  LOG_DEBUG("Destroyed AnalyzerFactory: " << this);
}

} /* namespace opov */
