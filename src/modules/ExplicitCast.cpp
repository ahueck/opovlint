/*
 * ExplicitCast.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitCast.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/transformation/TransformationHandler.h>
#include <core/transformation/TransformationUtil.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ExplicitCast::ExplicitCast() {
}

void ExplicitCast::setupOnce(const Configuration* config) {
  config->getValue("ExplicitCast:header", header_cast, "reCast.h");
  config->getValue("ExplicitCast:function", stmt_cast, "reCast");
}

void ExplicitCast::setupMatcher() {
  // clang-format off
  /* We ignore constructor conversions. This case is handled in
   * ImplicitConversion module
   * We do not warn on casts to scalar pointer
   * (hasDestinationType(hasCanonicalType(pointerType())))
   * as we deem it to be legal to write
   * static_cast<scalar*>(&my_scalar);
   */
  StatementMatcher invalid_expl_cast =
      explicitCastExpr(
          unless(
              anyOf(
                  hasDestinationType(hasCanonicalType(pointerType()))
                  , isTypedef(type_s)
                  , isConstructorConversion()
              )
          )
          , hasSourceExpression(ofType(type_s))
      ).bind("cast");
  // clang-format on
  this->addMatcher(invalid_expl_cast);
}

void ExplicitCast::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const ExplicitCastExpr* ecast = result.Nodes.getNodeAs<ExplicitCastExpr>("cast");

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(ecast, moduleName(), moduleDescription());

  if (transform) {
    auto& thandle = context->getTransformationHandler();
    auto replace = trutil::reCast(context->getASTContext(), ecast, type_s, stmt_cast);
    //    thandle.addHeader(header_cast, clutil::locOf(context->getSourceManager(), ecast).getBegin());
    thandle.addReplacements(replace);
  }
}

std::string ExplicitCast::moduleName() {
  return "ExplicitCast";
}

std::string ExplicitCast::moduleDescription() {
  return "C++ explicit casts of a complex object are not possible.";
}

ExplicitCast::~ExplicitCast() = default;

} /* namespace module */
} /* namespace opov */
