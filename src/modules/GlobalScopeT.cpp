/*
 * GlobalScopeT.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ahueck
 */




/*
 * GlobalScopeT.cpp
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#include <modules/GlobalScopeT.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/Logger.h>
#include <core/utility/ClangUtil.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/configuration/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

GlobalScopeT::GlobalScopeT() {

}

void GlobalScopeT::setupOnce(const Configuration* config) {
  config->getValue("global:type", type_s);
}

void GlobalScopeT::setupMatcher() {
  auto declref_matcher = //declRefExpr(eachOf(to(functionDecl()), has(nestedNameSpecifier(specifiesNamespace(namespaceDecl(asString("::")))))));//isGlobalNamespace())))).bind("global");
		  declRefExpr(eachOf(to(functionDecl(hasAnyParameter(isTypedef(type_s)))), has(nestedNameSpecifier(isGlobalNamespace())))).bind("global");
  this->addMatcher(declref_matcher);
}

void GlobalScopeT::run(
  const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const Expr* call = result.Nodes.getStmtAs<Expr>("global");

  auto& ihandle = context->getIssueHandler();
  auto& sm = context->getSourceManager();
  auto& ac = context->getASTContext();
  ihandle.addIssue(sm, ac, call, moduleName(), moduleDescription());
}

std::string GlobalScopeT::moduleName() {
  return "GlobalScopeTypedef";
}

std::string GlobalScopeT::moduleDescription() {
  return "Qualified lookup with :: with scalar typedef.";
}

GlobalScopeT::~GlobalScopeT() {
}

} // namespace module
} /* namespace opov */
