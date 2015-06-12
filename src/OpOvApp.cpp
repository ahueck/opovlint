/*
 * OpOvApp.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include "OpOvApp.h"
#include <core/IFactory.h>
#include <core/JSONConfiguration.h>
#include <core/ConsoleReporter.h>
#include <core/CSVReporter.h>
#include <AnalyzerFactory.h>
#include <core/Util.h>
#include <core/IssueHandler.h>
#include <core/TransformationHandler.h>
#include <modules/ImplicitCondition.h>
#include <modules/ExplicitCast.h>
#include <modules/ImplicitConversion.h>
#include <modules/ImplicitConditionMatcher.h>
#include <modules/UnionMatcher.h>
#include <modules/ConditionalAssgnMatcher.h>
#include <modules/ExplicitConstructor.h>
#include <modules/AllImplicitConversion.h>
#include <modules/GlobalScope.h>
#include <modules/GlobalScopeT.h>

OpOvApp::OpOvApp(const std::string& config_path) :
		config_path(config_path) {

}

void OpOvApp::loadConfig() {
	config = opov::util::make_unique<opov::JSONConfiguration>();
	bool success = config->load(config_path);
	if (!success) {
		LOG_FATAL("Could not find configuration file under '" << config_path << "'."
					<< "Exiting...");
		exit(-1);
	}
}

void OpOvApp::createReporter() {
	reporter = opov::util::make_unique<opov::CSVReporter>();
}

void OpOvApp::createFactory() {
	executor = opov::util::make_unique<opov::AnalyzerFactory>(config.get(),
									ihandler.get(), thandler.get());
	executor->init();
}

void OpOvApp::initModules() {
	//addModule(new opov::module::GlobalScopeT());
	//addModule(new opov::module::ExplicitCast());
	//addModule(new opov::module::UnionMatcher());
	addModule(new opov::module::ImplicitConversion());
	//addModule(new opov::module::ImplicitConditionMatcher());
	//addModule(new opov::module::AllImplicitConversion());
	//addModule(new opov::module::ExplicitConstructor());
	//addModule(new opov::module::ConditionalAssgnMatcher());
	// ADOL-C only?
	//addModule(new opov::module::ConditionalAssgnMatcher());
	// General coding conventions...
	/*
	addModule(new opov::module::ExplicitConstructor());
	addModule(new opov::module::AllImplicitConversion());
	*/
}

OpOvApp::~OpOvApp() {

}
