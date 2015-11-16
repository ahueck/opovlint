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
  // This matches calls to functions with scalar arguments but also functions with scalar parameters and scalar return type.
  auto call_matcher =
      callExpr(anyOf(
                      callee(functionDecl(hasAnyParameter(varDecl(isTypedef(type_s))))),
                      hasAnyArgument(ignoringImpCasts(isTypedef(type_s))),
                      isTypedef(type_s)

                    ),
               callee(expr(ignoringImpCasts(declRefExpr(has(nestedNameSpecifier(isGlobalNamespace()))))))).bind("call");

  this->addMatcher(call_matcher);
}

void GlobalScope::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  // auto ref = result.Nodes.getNodeAs<DeclRefExpr>("global_ref");
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
