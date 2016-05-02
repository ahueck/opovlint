/*
 * IfElseAssign.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: ahueck
 */

#include <modules/IfElseAssign.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

IfElseAssign::IfElseAssign() : apply_transform(false) {
}

void IfElseAssign::setupOnce(const Configuration* config) {
  config->getValue("IfElseAssign:transform", apply_transform);
}

void IfElseAssign::setupMatcher() {
// clang-format off
// ADOL-C speaks about all types being 'active', we should warn whenever an active type is involved (scalar).
// Caveat:    We limit ourselves to conditionaloperator-like structures (as shown in ADOL-C tech paper)
//            That is if or if-else with each having exactly one assignment with an active type involved
// auto assign = binaryOperator(hasOperatorName("="), hasDescendant(expr(isTypedef(type_s)))).bind(BIND);
// auto single_expr = anyOf(compoundStmt(statementCountIs(1), has(assign)), assign);
#define assign_bind(BIND)                                           \
  binaryOperator(                                                   \
      hasOperatorName("=")                                          \
      , hasLHS(declRefExpr(ofType(type_s)))                         \
      , unless(                                                     \
            hasRHS(                                                 \
                ignoringImpCasts(                                   \
                    conditionalOperator(                            \
                        anyOf(                                      \
                            hasTrueExpression(ofType(type_s))       \
                            , hasFalseExpression(ofType(type_s))    \
                        )                                           \
                    )                                               \
                )                                                   \
            )                                                       \
        )                                                           \
      , hasRHS(                                                     \
            expr(ofType(type_s))                                    \
        )                                                           \
  ).bind(BIND)

#define assign_expr(BIND)               \
  anyOf(                                \
      compoundStmt(                     \
          statementCountIs(1)           \
          , has(                        \
                assign_bind(BIND)       \
            )                           \
      )                                 \
      , assign_bind(BIND)               \
  )

  StatementMatcher conditional =
      ifStmt(
          hasThenStmt(assign_expr("then"))
          , anyOf(
                hasElseStmt(assign_expr("else"))
                , unless(hasElseStmt(stmt()))
            )
      ).bind("conditional");

   /*StatementMatcher conditional =
       ifStmt(
           anyOf(
               allOf(
                   hasThenStmt(assign_expr("then"))
                   , hasElseStmt(assign_expr("else"))
               )
               , hasThenStmt(assign_expr("then"))
               , unless(hasElseStmt(stmt()))
           )
       ).bind("conditional");*/
  // clang-format on
  this->addMatcher(conditional);
}

std::string IfElseAssign::toString(clang::ASTContext& ac, const IfStmt* stmt, const BinaryOperator* then,
                                   const BinaryOperator* else_e) {
  auto then_ref = clutil::nameOf(dyn_cast<DeclRefExpr>(then->getLHS()->IgnoreImpCasts()));

  if (else_e != nullptr && then_ref != clutil::nameOf(dyn_cast<DeclRefExpr>(else_e->getLHS()->IgnoreImpCasts()))) {
    // only transform when in both blocks the same variable is assigned to!
    return "";
  }

  auto replacement = "condassign(" + then_ref + ", " + clutil::node2str(ac, stmt->getCond()) + ", " +
                     clutil::node2str(ac, then->getRHS());
  if (else_e != nullptr) {
    replacement += ", " + clutil::node2str(ac, else_e->getRHS());
  }
  replacement += ")";
  if ((else_e != nullptr && isa<CompoundStmt>(stmt->getElse())) || isa<CompoundStmt>(stmt->getThen())) {
    /*
     * For structures as:
     * if(...)
     *   a = b;
     * the later Replacement does not remove the semicolon of "a = b;"
     */
    replacement += ";";
  }
  return replacement;
}

void IfElseAssign::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  auto* conditional = result.Nodes.getNodeAs<IfStmt>("conditional");
  auto* then_expr = result.Nodes.getNodeAs<BinaryOperator>("then");
  auto* else_expr = result.Nodes.getNodeAs<BinaryOperator>("else");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(conditional, moduleName(), moduleDescription());

  if (apply_transform && transform) {
    auto& ac = context->getASTContext();
    auto replacement = toString(ac, conditional, then_expr, else_expr);
    if (replacement != "") {
      auto& thandle = context->getTransformationHandler();
      thandle.addReplacements(clang::tooling::Replacement(context->getSourceManager(), conditional, replacement));
    }
  }
}

std::string IfElseAssign::moduleName() {
  return "IfElseAssign";
}

std::string IfElseAssign::moduleDescription() {
  return "Conditional assignments through if-else are not allowed with ADOL-C.";
}

IfElseAssign::~IfElseAssign() = default;

} /* namespace module */
} /* namespace opov */
