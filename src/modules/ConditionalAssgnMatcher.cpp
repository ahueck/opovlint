/*
 * ConditionalAssgnMatcher.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#include <modules/ConditionalAssgnMatcher.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/module/ModuleRegistry.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>

namespace opov {
namespace module {

REGISTER_MODULE(ConditionalAssgnMatcher)

using namespace clang;
using namespace clang::ast_matchers;

ConditionalAssgnMatcher::ConditionalAssgnMatcher() : apply_transform(false) {
}

void ConditionalAssgnMatcher::setupOnce(const Configuration* config) {
  // transformer = util::make_unique<conditional::ConditionalTransformer>(type_s);
  config->getValue("ConditionalAssgnMatcher:transform", apply_transform);
}

void ConditionalAssgnMatcher::setupMatcher() {
  // clang-format off
  /* We warn whenever an active type is present for such code structures.
   * (Even if there is no assignement.)
   *
   * Cases that need to be handled appropriately:
   * 1.
   * if(a > 0)
   *  c = conditional_operator
   *  "add brackets" -->
   * if(a > 0) {
   *  temp_var;
   *  call
   *  c = temp_var;
   * }
   *
   * 2.
   * find appropriate root statement
   * 2.1 a = conditional_op
   *    -> use assignment operator
   *    -> Caveat: nested in a call expr...
   *
   */
  StatementMatcher conditional =
      conditionalOperator(
          anyOf(
              hasTrueExpression(ofType(type_s))
              , hasFalseExpression(ofType(type_s))
          )
      ).bind("conditional");

  /*auto condassign =
      stmt(
          unless(compoundStmt())
          , hasParent(compoundStmt())
          , children_or_self(conditional)
      ).bind("conditional_root");*/
  /*auto root =
      binaryOperator(
          hasOperatorName("=")
          , hasEitherOperand(ignoringParenImpCasts(conditional)));*/

  StatementMatcher condassign =
      conditionalOperator(
          anyOf(
              hasTrueExpression(ofType(type_s))
              , hasFalseExpression(ofType(type_s))
          )
          , unless(
                hasAncestor(conditionalOperator())
            )
          , hasAncestor(
                stmt(
                    unless(compoundStmt())
                    , hasParent(compoundStmt())
                ).bind("conditional_root")
            )
      ).bind("conditional");

  /*auto condassign =
      stmt(
          unless(compoundStmt())
          , hasParent(compoundStmt())
          , children_or_self(conditional)
      ).bind("conditional_root");*/

  // clang-format on
  this->addMatcher(condassign);
  this->addMatcher(conditional);
}

void ConditionalAssgnMatcher::toString(clang::ASTContext& ac, const Expr* e, conditional_data& d) {
  auto cond = dyn_cast<ConditionalOperator>(e->IgnoreParenImpCasts());
  if (cond != nullptr) {
    d.type = type_s;  // We matched, so it should be a scalar type. clutil::typeOf(e);
    auto pos = clutil::posOf(ac.getSourceManager(), cond);
    d.variable = "_oolint_t_" + util::num2str(std::get<0>(pos)) + util::num2str(std::get<1>(pos)) +
                 util::num2str(std::get<2>(pos)) + util::num2str(std::get<3>(pos));
    d.replacement = d.type + " " + d.variable + ";\n" + "condassign(" + d.variable + ", " +
                    clutil::node2str(ac, cond->getCond()) + ", " +
                    (d.lhs == "" ? clutil::node2str(ac, cond->getLHS()) : d.lhs) + ", " +
                    (d.rhs == "" ? clutil::node2str(ac, cond->getRHS()) : d.rhs) + ");";
  }
}

ConditionalAssgnMatcher::conditional_data ConditionalAssgnMatcher::buildReplacement(
    clang::ASTContext& ac, const ConditionalOperator* conditional) {
#define nl_str(STRUCT) (STRUCT.replacement == "" ? "" : (STRUCT.replacement + "\n"))

  conditional_data lhs_dat, rhs_dat, cond_dat;
  toString(ac, conditional->getRHS(), rhs_dat);
  toString(ac, conditional->getLHS(), lhs_dat);
  cond_dat.lhs = lhs_dat.variable;
  cond_dat.rhs = rhs_dat.variable;
  toString(ac, conditional, cond_dat);
  cond_dat.replacement = nl_str(lhs_dat) + nl_str(rhs_dat) + cond_dat.replacement;
  return cond_dat;
}

void ConditionalAssgnMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  auto* root = result.Nodes.getNodeAs<Stmt>("conditional_root");
  auto* conditional = result.Nodes.getNodeAs<ConditionalOperator>("conditional");

  if (root == nullptr) {
    // We report every conditionalOperator (even nested ones)
    auto& ihandle = context->getIssueHandler();
    ihandle.addIssue(conditional, moduleName(), moduleDescription());
  }

  if (apply_transform && transform && root && conditional) {
    // We transform starting from root down to the last conditionalOperator
    auto& thandle = context->getTransformationHandler();
    auto& ac = context->getASTContext();
    conditional_data cond_dat = buildReplacement(ac, conditional);
    // Delete if for some reason ?: has no assignement (root is equal to conditional pointer)
    thandle.addReplacements(
        clang::tooling::Replacement(ac.getSourceManager(), conditional, root == conditional ? "" : cond_dat.variable));
    thandle.addReplacements(trutil::insertString(ac, cond_dat.replacement, root, true, ""));
  }
}

std::string ConditionalAssgnMatcher::moduleName() {
  return "ConditionalAssgnMatcher";
}

std::string ConditionalAssgnMatcher::moduleDescription() {
  return "Conditional assignments (?:) are not allowed with ADOL-C.";
}

ConditionalAssgnMatcher::~ConditionalAssgnMatcher() = default;

} /* namespace module */
} /* namespace opov */
