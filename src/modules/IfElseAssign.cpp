/*
 * IfElseAssign.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: ahueck
 */

#include <modules/IfElseAssign.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
//#include <modules/ConditionalTransformer.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

IfElseAssign::IfElseAssign() {


}

void IfElseAssign::setupOnce(const Configuration* config) {

}

void IfElseAssign::setupMatcher() {
  // we merely check for LHS of type scalar, ADOL-C speaks about all types being 'active', but we should warn more frequently.
  auto assign = binaryOperator(hasOperatorName("="), hasLHS(descendant_or_self(expr(isTypedef(type_s)))));
  auto single_expr = anyOf(compoundStmt(statementCountIs(1), has(assign)), assign);
  auto conditional = ifStmt(anyOf(allOf(hasThen(single_expr), hasElse(single_expr)), allOf(hasThen(single_expr), unless(hasElse(single_expr))))).bind("conditional");
  this->addMatcher(conditional);
}

void IfElseAssign::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  auto* conditional = result.Nodes.getNodeAs<IfStmt>("conditional");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(conditional, moduleName(), moduleDescription());


  if(transform) {
    auto& thandle = context->getTransformationHandler();
    auto& ac = context->getASTContext();
  }
}

std::string IfElseAssign::moduleName() {
  return "IfElseAssign";
}

std::string IfElseAssign::moduleDescription() {
  return "Conditional assignments through if-else are not allowed with ADOL-C.";
}

IfElseAssign::~IfElseAssign() {

}

} /* namespace module */
} /* namespace opov */
