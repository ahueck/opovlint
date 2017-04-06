/*
 * OpOvApp.cpp
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#include "OpOvApp.h"
#include <AnalyzerFactory.h>
#include <core/IFactory.h>
#include <core/configuration/JSONConfiguration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleRegistry.h>
#include <core/reporting/FormattedReporter.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/Util.h>

namespace opov {
namespace module {
LINK_MODULE(UnionMatcher)
LINK_MODULE(ExplicitCast)
LINK_MODULE(ImplicitConversion)
LINK_MODULE(ImplicitConditionMatcher)
LINK_MODULE(ConditionalAssgnMatcher)
LINK_MODULE(IfElseAssign)
LINK_MODULE(LocalScope)
LINK_MODULE(GlobalScope)
} /* namespace module */
} /* namespace opov */

OpOvApp::OpOvApp(const std::string& config_path) : config_path(config_path) {
}

void OpOvApp::loadConfig() {
  config = opov::util::make_unique<opov::JSONConfiguration>();
  bool success = config->load(config_path);
  if (!success) {
    LOG_FATAL("Could not find configuration file under '" << config_path << "'."
                                                          << "Exiting...");
    std::exit(EXIT_FAILURE);
  }
}

void OpOvApp::createReporter() {
  reporter = opov::util::make_unique<opov::FormattedReporter>(config.get());
}

void OpOvApp::createFactory() {
  executor = opov::util::make_unique<opov::AnalyzerFactory>(config.get(), ihandler.get(), thandler.get());
  executor->init();
}
