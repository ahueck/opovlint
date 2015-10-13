/*
 * ConditionalAssgnMatcher.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#include <modules/ConditionalAssgnMatcher.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ConditionalAssgnMatcher::ConditionalAssgnMatcher() {
  // TODO Auto-generated constructor stub
}

void ConditionalAssgnMatcher::setupOnce(const Configuration* config) {
}

void ConditionalAssgnMatcher::setupMatcher() {
  // TODO use ofType instead of just typedef?
  StatementMatcher condassign = conditionalOperator(hasDescendant(expr(isTypedef(type_s)))).bind("condassign");
  this->addMatcher(condassign);
}

void ConditionalAssgnMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const ConditionalOperator* e = result.Nodes.getNodeAs<ConditionalOperator>("condassign");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(e, moduleName(), moduleDescription());

  if(transform) {
    auto& thandle = context->getTransformationHandler();
    auto& ast_ctx = context->getASTContext();
    // TODO implement transformation
  }
}

std::string ConditionalAssgnMatcher::moduleName() {
  return "ConditionalAssgnMatcher";
}

std::string ConditionalAssgnMatcher::moduleDescription() {
  return "Conditional assignments (?:) are not allowed with ADOL-C.";
}

ConditionalAssgnMatcher::~ConditionalAssgnMatcher() {
}

} /* namespace module */
} /* namespace opov */
