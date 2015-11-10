/*
 * LocalScope.cpp
 *
 *  Created on: Nov 09, 2015
 *      Author: ahueck
 */

#include <modules/LocalScope.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/configuration/Configuration.h>
#include <core/utility/Util.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

LocalScope::LocalScope()
: ns_s(""), keep_global(false) {
}

void LocalScope::setupOnce(const Configuration* config) {
  config->getValue("LocalScope:namespace", ns_s);
  config->getValue("LocalScope:keep_global", keep_global);
}

void LocalScope::setupMatcher() {
  // This matches calls to functions with scalar arguments but also functions with scalar parameters or scalar retun type.
  auto call_matcher =
      callExpr(anyOf(
                      callee(functionDecl(hasAnyParameter(varDecl(isTypedef(type_s))))),
                      hasAnyArgument(ignoringImpCasts(isTypedef(type_s))),
                      isTypedef(type_s)
                    ),
               callee(expr(ignoringImpCasts(declRefExpr(has(nestedNameSpecifier(specifiesNamespace(hasName(ns_s))))))))).bind("call");

  this->addMatcher(call_matcher);
}

void LocalScope::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  auto call = result.Nodes.getNodeAs<CallExpr>("call");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(call, moduleName(), moduleDescription());

  if(transform) {
    auto& thandle = context->getTransformationHandler();
    auto& ac = context->getASTContext();
    auto& sm = context->getSourceManager();
    const unsigned offset = util::startsWith(clutil::node2str(ac, call), "::") ? 4 : 2;
    const std::string replace_str((keep_global && offset == 4) ? "::" : "");
    thandle.addReplacements(tooling::Replacement(sm, call->getLocStart(), ns_s.length() + offset,  replace_str));
  }
}

std::string LocalScope::moduleName() {
  return "LocalScope";
}

std::string LocalScope::moduleDescription() {
  return "Remove qualified lookup.";
}

LocalScope::~LocalScope() {
}

} /* namespace module */
} /* namespace opov */
