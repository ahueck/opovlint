/*
 * AbstractFactory.cpp
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#include <core/AbstractFactory.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/logging/Logger.h>
#include <core/module/Module.h>
#include <core/module/ModuleContext.h>
#include <core/reporting/IssueReporter.h>
#include <core/reporting/ProgressMonitor.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>

#include <external/IncludeDirectives.h>

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Refactoring.h>
#include <llvm/ADT/StringRef.h>

namespace opov {

AbstractFactory::AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler)
    : module(nullptr), config(config), currentSource(""), ihandler(ihandler), thandler(thandler) {
}

bool AbstractFactory::handleBeginSource(clang::CompilerInstance& CI) {
  auto& sm = CI.getASTContext().getSourceManager();
  currentSource = clutil::mainFilename(sm);
  this->context->setCurrentSource(currentSource);
  // FIXME relocate to modulecontext class
  thandler->setIncludeDirectives(new IncludeDirectives(CI));

  if (p_monitor != nullptr) {
    auto pos = currentSource.find_last_of('/');
    auto file_s = pos != std::string::npos ? currentSource.substr(pos + 1) : currentSource;
    p_monitor->update(module->moduleName() + ": " + file_s);
  }

  return true;
}

void AbstractFactory::handleEndSource() {
  if (thandler->getRewriter().overwriteChangedFiles()) {
    LOG_ERROR("Error while writing source transformations to disk.");
  }
}

void AbstractFactory::setModule(Module* m) {
  this->module = m;
}

void AbstractFactory::setProgressMonitor(ProgressMonitor* p_monitor) {
  this->p_monitor = p_monitor;
}

void AbstractFactory::init() {
  this->context = opov::util::make_unique<ModuleContext>(this->config, this->ihandler, this->thandler);
}

AbstractFactory::~AbstractFactory() = default;

} /* namespace opov */
