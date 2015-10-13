/*
 * ImplicitConversion.cpp
 *
 *  Created on: Jun 25, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConversion.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
//#include <modules/ExplicitCastVisitor.h>
#include <core/transformation/TransformationUtil.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ImplicitConversion::ImplicitConversion() {
}

void ImplicitConversion::setupOnce(const Configuration* config) {
}

void ImplicitConversion::setupMatcher() {
  StatementMatcher impl_conversion = materializeTemporaryExpr(hasTemporary(ignoringImpCasts(
      constructExpr(hasImplicitConversion(type_s), unless(temporaryObjectExpr())).bind("conversion"))));
  /*constructExpr(
                  unless(hasParent(varDecl())) // TODO remove varDecl req.?
                                  ,
     hasImplicitConversion(type_s)).bind("conversion");
  */
  this->addMatcher(impl_conversion);
}

void ImplicitConversion::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXConstructExpr* expr = result.Nodes.getNodeAs<CXXConstructExpr>("conversion");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(expr, moduleName(), moduleDescription());  //, message.str());

  if(transform) {
    auto& thandle = context->getTransformationHandler();
    thandle.addReplacements(trutil::castTheExpr(context->getASTContext(), expr, type_s));
  }
}

std::string ImplicitConversion::moduleName() {
  return "ImplicitConversion";
}

std::string ImplicitConversion::moduleDescription() {
  return "Implicit conversions are problematic, since only one user-defined "
         "conversion is allowed on a single value. WIth the complex type, this "
         "can be easily violated.";
}

ImplicitConversion::~ImplicitConversion() {
}

} /* namespace module */
} /* namespace opov */
