/*
 * UnionMatcher.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#include <modules/UnionMatcher.h>
#include <modules/FieldDeclCollector.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/configuration/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

UnionMatcher::UnionMatcher() {
}

void UnionMatcher::setupOnce(const Configuration* config) {
  config->getValue("global:type", type_s);
  visitor = opov::util::make_unique<FieldDeclCollector>(type_s);
}

void UnionMatcher::setupMatcher() {
  DeclarationMatcher invalid_unions = recordDecl(isUnion(), hasDescendant(fieldDecl(isTypedef(type_s)))).bind("union");

  this->addMatcher(invalid_unions);
}

void UnionMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXRecordDecl* inv_union = result.Nodes.getDeclAs<CXXRecordDecl>("union");
  const bool is_anon = inv_union->isAnonymousStructOrUnion();
  auto fieldDecls = visitor->extractDecl(const_cast<CXXRecordDecl*>(inv_union));

  std::stringstream message;
  message << (is_anon ? "Anonymous union" : "Union") << " with typedef member. " << fieldDecls.size()
          << " fieldDecl violate the convention.";

  auto& ihandle = context->getIssueHandler();
  auto& sm = context->getSourceManager();
  auto& ac = context->getASTContext();
  ihandle.addIssue(sm, ac, inv_union, moduleName(), moduleDescription(), message.str());
}

std::string UnionMatcher::moduleName() {
  return "UnionMatcher";
}

std::string UnionMatcher::moduleDescription() {
  return "Unions do not support complex types (complex constructor, destructor "
         "etc.).";
}

UnionMatcher::~UnionMatcher() {
}

} /* namespace module */
} /* namespace opov */
