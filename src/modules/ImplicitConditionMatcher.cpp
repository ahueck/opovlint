/*
 * ImplicitConditionMatcher.cpp
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConditionMatcher.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/module/ModuleRegistry.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>

#include <clang/Frontend/TextDiagnostic.h>
#include <llvm/Support/raw_ostream.h>

namespace opov {
namespace module {

REGISTER_MODULE(ImplicitConditionMatcher)

using namespace clang;
using namespace clang::ast_matchers;

ImplicitConditionMatcher::ImplicitConditionMatcher() {
}

/*
void ImplicitConditionMatcher::setupOnce(const Configuration* config) {
}
*/

void ImplicitConditionMatcher::setupMatcher() {
  // clang-format off
  StatementMatcher impl =
      implicitCastExpr(
          isFloatingToBoolean()
          , unless(hasParent(binaryOperator()))
          , hasSourceExpression(ofType(type_s))
      ).bind("implicit");

  StatementMatcher unaryMatch =
      unaryOperator(
          hasUnaryOperand(
              implicitCastExpr(
                  isFloatingToBoolean()
                  , hasSourceExpression(ofType(type_s))
              )
          )
      ).bind("unary");

  /*auto typedef_condition =
      hasCondition(
          anyOf(
              unaryMatch
              , expr(hasDescendant(unaryMatch))
              , impl
              , expr(hasDescendant(impl))
          )
      );*/

  auto typedef_condition =
      hasCondition(
          anyOf(
              descendant_or_self(unaryMatch)
              , descendant_or_self(impl)
          )
      );

  StatementMatcher all_cond =
      stmt(
          anyOf(
              ifStmt(typedef_condition)
              , forStmt(typedef_condition)
              , doStmt(typedef_condition)
              , whileStmt(typedef_condition)
              , conditionalOperator(typedef_condition)
          )
     ).bind("stmt");
  // clang-format on
  this->addMatcher(all_cond);
}

void ImplicitConditionMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  /*
   * match unary nodes of "scalar" but only transform OperatorKind (UO_Not, UO_LNot)
   */
  const Expr* implicit_cast = result.Nodes.getNodeAs<Expr>("implicit");
  const Expr* unary_op = result.Nodes.getNodeAs<Expr>("unary");
  const Expr* invalid = implicit_cast == nullptr ? unary_op : implicit_cast;
  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(invalid, moduleName(), moduleDescription());

  if (transform) {
    auto& thandle = context->getTransformationHandler();
    thandle.addReplacements(trutil::addExplicitCompare(context->getASTContext(), invalid, type_s));
  }
}

std::string ImplicitConditionMatcher::moduleName() {
  return "ImplicitConditionMatcher";
}

std::string ImplicitConditionMatcher::moduleDescription() {
  return "Implicit conditions (implicit conversion to a bool) is not possible "
         "with a complex object.";
}

ImplicitConditionMatcher::~ImplicitConditionMatcher() = default;

} /* namespace module */
} /* namespace opov */
