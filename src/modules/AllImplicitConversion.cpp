/*
 * AllImplicitConversion.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/AllImplicitConversion.h>

#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

AllImplicitConversion::AllImplicitConversion() {
  // TODO Auto-generated constructor stub
}

void AllImplicitConversion::setupOnce(const Configuration* config) {
}

void AllImplicitConversion::setupMatcher() {
  StatementMatcher impl_conversion = materializeTemporaryExpr(
      hasTemporary(ignoringImpCasts(constructExpr(unless(temporaryObjectExpr())).bind("conversion"))));

  /*constructExpr(unless(anyOf(
                                                                                                  hasDeclaration(constructorDecl(isCopyOrMoveCtor()))
                                                                                                  ,
     hasParent(explicitCastExpr(isConstructorConversion()))
                                                                                                  ,
     hasParent(varDecl())))
                                                                                  ).bind("conversion");*/
  this->addMatcher(impl_conversion);
}

void AllImplicitConversion::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXConstructExpr* expr = result.Nodes.getNodeAs<CXXConstructExpr>("conversion");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(expr, moduleName(), moduleDescription());
}

std::string AllImplicitConversion::moduleName() {
  return "AllImplicitConversion";
}

std::string AllImplicitConversion::moduleDescription() {
  return "Detects *all* implicit conversions.";
}

AllImplicitConversion::~AllImplicitConversion() {
  // TODO Auto-generated destructor stub
}

} /* namespace module */
} /* namespace opov */
