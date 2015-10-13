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
#include <core/transformation/TransformationUtil.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

UnionMatcher::UnionMatcher() {
}

void UnionMatcher::setupOnce(const Configuration* config) {
  visitor = opov::util::make_unique<FieldDeclCollector>(type_s);
}

void UnionMatcher::setupMatcher() {
  DeclarationMatcher invalid_unions = recordDecl(isUnion(), hasDescendant(fieldDecl(isTypedef(type_s)))).bind("union");

  this->addMatcher(invalid_unions);
}

void UnionMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXRecordDecl* inv_union = result.Nodes.getNodeAs<CXXRecordDecl>("union");
  const bool is_anon = inv_union->isAnonymousStructOrUnion();
  auto fieldDecls = visitor->extractDecl(const_cast<CXXRecordDecl*>(inv_union));

  std::stringstream message;
  message << (is_anon ? "Anonymous union" : "Union") << " with typedef member. " << fieldDecls.size()
          << " fieldDecl violate the convention.";

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(inv_union, moduleName(), moduleDescription(), message.str());

  // TODO improve by using a custom union traversal and slowly building a replacement string
  if(transform) {
    auto& thandle = context->getTransformationHandler();
    auto& ast_ctx = context->getASTContext();
    if(is_anon) {
      const bool remove_union = std::distance(inv_union->field_begin(), inv_union->field_end()) == 1;
      if(remove_union) {
        thandle.addReplacements(trutil::replaceStmt(ast_ctx, inv_union, fieldDecls.front()));
      } else {
        for(auto fd : fieldDecls) {
          thandle.addReplacements(trutil::removeNode(ast_ctx, fd));
          thandle.addReplacements(trutil::insertNode(ast_ctx, fd, inv_union));
        }
      }
    } else {
      thandle.addReplacements(tooling::Replacement(context->getSourceManager(), inv_union->getLocStart(), 5, "struct"));
    }
  }
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
