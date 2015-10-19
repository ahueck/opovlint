/*
 * GlobalScope.cpp
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#include <modules/GlobalScope.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/configuration/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

GlobalScope::GlobalScope() {
}

void GlobalScope::setupOnce(const Configuration* config) {
}

void GlobalScope::setupMatcher() {
  auto declref_matcher = declRefExpr(hasDeclaration(functionDecl(hasAnyParameter(varDecl(isTypedef(type_s))))),
                                     has(nestedNameSpecifier(isGlobalNamespace()))); /*.bind("global_ref");*/
  auto call_matcher = callExpr(callee(expr(ignoringImpCasts(declref_matcher)))).bind("call");
  this->addMatcher(call_matcher);
}

void GlobalScope::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  //auto ref = result.Nodes.getNodeAs<DeclRefExpr>("global_ref");
  auto call = result.Nodes.getNodeAs<CallExpr>("call");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(call, moduleName(), moduleDescription());
}

std::string GlobalScope::moduleName() {
  return "GlobalScope";
}

std::string GlobalScope::moduleDescription() {
  return "Qualified lookup with ::.";
}

GlobalScope::~GlobalScope() {
}

} /* namespace module */
} /* namespace opov */
