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
//#include <modules/ConditionalTransformer.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ConditionalAssgnMatcher::ConditionalAssgnMatcher()
: var_counter(0) {

}

void ConditionalAssgnMatcher::setupOnce(const Configuration* config) {
  //transformer = util::make_unique<conditional::ConditionalTransformer>(type_s);
}

void ConditionalAssgnMatcher::setupMatcher() {
  // TODO use ofType instead of just typedef?
  // we merely check for the existence of type scalar, ADOL-C speaks about all types being 'active', but we should warn more frequently.
  auto conditional = conditionalOperator(hasDescendant(expr(isTypedef(type_s)))).bind("conditional");
  auto condassign = stmt(hasParent(compoundStmt()), descendant_or_self(conditional)).bind("conditional_root");

  this->addMatcher(condassign);
  this->addMatcher(conditional);
}


void ConditionalAssgnMatcher::toString(clang::ASTContext& ac, const Expr* e, conditional_data& d, int counter) {
  auto cond = dyn_cast<ConditionalOperator>(e->IgnoreParenImpCasts());
  if(cond) {
    d.type = clutil::typeOf(e);
    d.variable = "_oolint_t_" + util::num2str(cond);
    d.replacement = d.type + " " + d.variable + ";\n" + "condassign(" + d.variable
                                + ", " + clutil::node2str(ac, cond->getCond())
                                + ", "  + (d.lhs == "" ? clutil::node2str(ac, cond->getLHS()) : d.lhs)
                                + ", "  + (d.rhs == "" ? clutil::node2str(ac, cond->getRHS()) : d.rhs) + ");";
  }
}

ConditionalAssgnMatcher::conditional_data ConditionalAssgnMatcher::buildReplacement(clang::ASTContext& ac, const ConditionalOperator* conditional) {
#define nl_str(STRUCT) \
  (STRUCT.replacement == "" ? "" : (STRUCT.replacement + "\n"))

  conditional_data lhs_dat, rhs_dat, cond_dat;
  toString(ac, conditional->getRHS(), rhs_dat, ++var_counter);
  toString(ac, conditional->getLHS(), lhs_dat, ++var_counter);
  cond_dat.lhs = lhs_dat.variable;
  cond_dat.rhs = rhs_dat.variable;
  toString(ac, conditional, cond_dat, ++var_counter);
  cond_dat.replacement = nl_str(lhs_dat) + nl_str(rhs_dat) + cond_dat.replacement;
  return cond_dat;
}

void ConditionalAssgnMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  auto* root = result.Nodes.getNodeAs<Stmt>("conditional_root");
  auto* conditional = result.Nodes.getNodeAs<ConditionalOperator>("conditional");

  if(root == nullptr) {
    // We report every conditionalOperator (even nested ones)
    auto& ihandle = context->getIssueHandler();
    ihandle.addIssue(conditional, moduleName(), moduleDescription());
  }

  if(transform && root && conditional) {
    // We transform starting from root down to the last conditionalOperator
    auto& thandle = context->getTransformationHandler();
    auto& ac = context->getASTContext();
    conditional_data cond_dat = buildReplacement(ac, conditional);
    thandle.addReplacements(clang::tooling::Replacement(ac.getSourceManager(), conditional, cond_dat.variable));
    thandle.addReplacements(trutil::insertString(ac, cond_dat.replacement, root, true, ""));
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
