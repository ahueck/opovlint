/*
 * AllImplicitConversion.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/AllImplicitConversion.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/module/ModuleRegistry.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>

namespace opov {
namespace module {

REGISTER_MODULE(AllImplicitConversion)

using namespace clang;
using namespace clang::ast_matchers;

AllImplicitConversion::AllImplicitConversion() {
}

/*
 void AllImplicitConversion::setupOnce(const Configuration* config) {
 }
 */
void AllImplicitConversion::setupMatcher() {
  // clang-format off
  StatementMatcher impl_conversion =
      materializeTemporaryExpr(
          hasTemporary(
              ignoringImpCasts(
                  constructExpr(
                      unless(temporaryObjectExpr())
                  ).bind("conversion")
              )
          )
      );
  /* constructExpr(
          unless(
              anyOf(
                  hasDeclaration(
                      constructorDecl(isCopyOrMoveCtor())
                  )
                  , hasParent(
                        explicitCastExpr(
                            isConstructorConversion())
                        )
                  , hasParent(varDecl())
              )
          )
      ).bind("conversion");*/
  // clang-format on
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

AllImplicitConversion::~AllImplicitConversion() = default;

} /* namespace module */
} /* namespace opov */
