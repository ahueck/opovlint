/*
 * GlobalScope.cpp
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#include <modules/GlobalScope.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/module/ModuleRegistry.h>
#include <core/transformation/TransformationHandler.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>

namespace opov {
namespace module {

REGISTER_MODULE(GlobalScope)

using namespace clang;
using namespace clang::ast_matchers;

GlobalScope::GlobalScope() {
}

/*
void GlobalScope::setupOnce(const Configuration* config) {
}
*/
void GlobalScope::setupMatcher() {
  // clang-format off
  // This matches calls to functions with scalar arguments but also functions with scalar parameters and scalar return type.
  StatementMatcher call_matcher =
      callExpr(
          anyOf(
              callee(
                  functionDecl(hasAnyParameter(varDecl(isTypedef(type_s))))
              )
              , hasAnyArgument(
                    ignoringImpCasts(isTypedef(type_s))
                )
              , isTypedef(type_s))
              , callee(
                    expr(
                        ignoringImpCasts(
                            declRefExpr(
                                has(nestedNameSpecifier(isGlobalNamespace()))
                            )
                        )
                    )
                )
      ).bind("call");
  // clang-format on
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

GlobalScope::~GlobalScope() = default;

} /* namespace module */
} /* namespace opov */
