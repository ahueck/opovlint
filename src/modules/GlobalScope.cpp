/*
 * GlobalScope.cpp
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#include <modules/GlobalScope.h>
#include <core/ClangMatcherExt.h>
#include <core/ModuleContext.h>
#include <core/Logger.h>
#include <core/ClangUtil.h>
#include <core/IssueHandler.h>
#include <core/IssueHandler.h>
#include <core/TransformationHandler.h>
#include <core/TransformationUtil.h>
#include <core/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

GlobalScope::GlobalScope() {

}

void GlobalScope::setupOnce(const Configuration* config) {
  config->getValue("global:type", type_s);
  config->getValue("GlobalScope:any_param", check_any);
}

void GlobalScope::setupMatcher() {
  auto functionDecl_matcher = check_any ? functionDecl(hasAnyParameter(isTypedef(type_s))) : functionDecl();
  auto declref_matcher = declRefExpr(to(functionDecl_matcher), has(nestedNameSpecifier(isGlobalNamespace()))).bind("global");
  this->addMatcher(declref_matcher);
}

void GlobalScope::run(
  const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const Expr* call = result.Nodes.getStmtAs<Expr>("global");
  auto& ihandle = context->getIssueHandler();
  auto& thandle = context->getTransformationHandler();
  auto& sm = context->getSourceManager();
  ihandle.addIssue(sm, call, moduleName(), moduleDescription());
}

std::string GlobalScope::moduleName() {
  return "GlobalScope";
}

std::string GlobalScope::moduleDescription() {
  return "Qualified lookup with ::.";
}

GlobalScope::~GlobalScope() {
}

} // namespace module
} /* namespace opov */
