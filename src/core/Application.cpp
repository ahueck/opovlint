/*
 * Application.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include <core/Application.h>
#include <core/IFactory.h>
#include <core/module/Module.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/reporting/IssueReporter.h>
#include <core/Logger.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/Util.h>

#include <external/ReplacementHandling.h>

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include <llvm/Support/Path.h>
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Program.h"
#include <limits.h>
#include <algorithm>

namespace opov {

//Application::Application() : executor(nullptr) {
//}

void Application::init() {
	loadConfig();
	createIssueHandler();
	createTransformationHandler();
	createReporter();
	createFactory();
	initModules();
	createActionFactory();
}

void Application::createActionFactory() {
	actionFactory = clang::tooling::newFrontendActionFactory<IFactory>(
			executor.get(), executor.get());
}

void Application::createIssueHandler() {
	ihandler = util::make_unique<IssueHandler>();
}

void Application::createTransformationHandler() {
	thandler = util::make_unique<TransformationHandler>();
}

int Application::execute(const clang::tooling::CompilationDatabase& db,
		const std::vector<std::string>& sources) {
	clang::tooling::ClangTool tool(db, sources);
	ReplacementHandling replacementHandler;
	std::string replacement_loc;
	bool apply_replacements;
	config->getValue("replacement:location", replacement_loc);
	config->getValue("replacement:apply", apply_replacements);	
	int sig = 0;

	if(!replacementHandler.findClangApplyReplacements("")) {
		LOG_ERROR("Could not find clang-apply-replacement");
	}

	for(auto module : modules) {
		executor->setModule(module);
		int sig = tool.run(actionFactory.get());
		if(sig == 1) {
			/*LOG_ERROR("Module '" << module->moduleName() << "' failed.");*/
			//return sig;
		}
	}

	reporter->addIssues(ihandler->getAllIssues());
	ihandler->clear();
/*
	replacementHandler.setDestinationDir(replacement_loc);
	if(!replacementHandler.serializeReplacements(thandler->getAllReplacements())) {
		LOG_DEBUG("Failed to serialize replacements");
	}
	if(apply_replacements) {
		if(!replacementHandler.applyReplacements()) {
			LOG_DEBUG("Failed to apply replacements");
		}
	}
	thandler->getAllReplacements().clear();
*/
	return sig;
}

int Application::executeOnCode(const std::string& source,
		const std::vector<std::string>& args) {
	int sig = 0;
	for(auto module : modules) {
		executor->setModule(module);
		int sig = clang::tooling::runToolOnCodeWithArgs(
				actionFactory->create(), source, args);
		if(sig < 1) {
			LOG_DEBUG("Module '" << module->moduleName() << "' failed.");
			return sig;
		}
	}

	reporter->addIssues(ihandler->getAllIssues());
	ihandler->clear();

	return sig;
}

void Application::addModule(Module* module) {
	LOG_DEBUG("Add module: " << module->moduleName());
	modules.push_back(module);
	module->init(config.get());
}

void Application::cleanUp() {
	for(auto module : modules) {
		delete module;
	}
	modules.clear();
}

std::string Application::getApplicationName() {
	return "GenericApplication";
}

Application::~Application() {
	cleanUp();
}

} /* namespace opov */
