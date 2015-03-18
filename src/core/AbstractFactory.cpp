/*
 * AbstractFactory.cpp
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#include <core/AbstractFactory.h>
#include <core/Module.h>
#include <core/ModuleContext.h>
#include <core/Configuration.h>
#include <core/IssueReporter.h>
#include <core/Util.h>
#include <core/IssueHandler.h>
#include <core/TransformationHandler.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/ADT/StringRef.h>
#include <clang/Tooling/Refactoring.h>

#include <core/Logger.h>

#include <core/ConsoleReporter.h>

namespace opov {

AbstractFactory::AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler) :
		module(nullptr), config(config), currentSource(""), ihandler(ihandler), thandler(thandler) {

}

bool AbstractFactory::handleBeginSource(clang::CompilerInstance &CI,
		llvm::StringRef Filename) {
	currentSource = Filename;
	thandler->setSource(currentSource);
	thandler->setIncludeDirectives(new IncludeDirectives(CI));
	ihandler->setSource(currentSource);
	return true;
}

void AbstractFactory::handleEndSource() {
	// FIXME remove this...
	/*
	ConsoleReporter reporter;
	auto& issues = context->getIssueHandler().getAllIssues();
	for(auto& tu : issues) {
		reporter.addIssues(tu.second.Issues);
	}
	*/
	/*
	auto& issues = context->getIssues();
	reporter->addIssues(issues, currentSource);
	issues.clear();
	*/
	auto& replacements = context->getTransformationHandler().getAllReplacements();
	for(auto& tu : replacements) {
		for(auto& rep : tu.second.Replacements) {
			LOG_DEBUG("Replacement: " << rep.getReplacementText());
		}

	}
}

void AbstractFactory::setModule(Module* m) {
	this->module = m;
}

void AbstractFactory::init() {
	this->context = opov::util::make_unique<ModuleContext>(this->config, this->ihandler, this->thandler);
}

AbstractFactory::~AbstractFactory() {

}

}
