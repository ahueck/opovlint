/*
 * ExplicitConstructor.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitConstructor.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/module/ModuleContext.h>
#include <core/module/ModuleRegistry.h>
#include <core/utility/ClangMatcherExt.h>

namespace opov {
namespace module {

REGISTER_MODULE(ExplicitConstructor)

using namespace clang;
using namespace clang::ast_matchers;

ExplicitConstructor::ExplicitConstructor() : warnOnTemplates(false) {
}

void ExplicitConstructor::setupOnce(const Configuration* config) {
  config->getValue("ExplicitConstructor:warnOnTemplates", warnOnTemplates, true);
}

void ExplicitConstructor::setupMatcher() {
  // clang-format off
  auto isTemplSpecialization =
      hasParent(classTemplateSpecializationDecl());
  DeclarationMatcher constructor =
      (warnOnTemplates
           ? cxxConstructorDecl(
               unless(isTemplSpecialization)
             )
           : cxxConstructorDecl(
                 unless(
                     anyOf(
                         isTemplSpecialization
                         , hasParent(
                               recordDecl(hasParent(classTemplateDecl()))
                           )
                     )
                 )
             )
       ).bind("constructor");
  ;
  // clang-format on
  addMatcher(constructor);
}

void ExplicitConstructor::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXConstructorDecl* ctor = result.Nodes.getNodeAs<CXXConstructorDecl>("constructor");

  if (ctor->isOutOfLine() || ctor->isExplicit() || ctor->isImplicit() || ctor->isDeleted() ||
      ctor->isCopyOrMoveConstructor() || ctor->getNumParams() == 0 || ctor->getMinRequiredArguments() > 1) {
    return;
  }

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(ctor, moduleName(), moduleDescription());
}

std::string ExplicitConstructor::moduleName() {
  return "ExplicitConstructor";
}

std::string ExplicitConstructor::moduleDescription() {
  return "Finds (all) non-explicit constructors. Explicit constructors prevent "
         "implicit conversions.";
}

ExplicitConstructor::~ExplicitConstructor() = default;

} /* namespace module */
} /* namespace opov */
