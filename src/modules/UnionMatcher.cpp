/*
 * UnionMatcher.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#include <modules/UnionMatcher.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include <core/configuration/Configuration.h>
#include <core/transformation/TransformationUtil.h>

#include <algorithm>
#include <vector>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

UnionMatcher::UnionMatcher() {
}

void UnionMatcher::setupOnce(const Configuration* config) {
}

void UnionMatcher::setupMatcher() {
  DeclarationMatcher invalid_unions = recordDecl(isUnion(), hasDescendant(fieldDecl(isTypedef(type_s)))).bind("union");

  this->addMatcher(invalid_unions);
}

void UnionMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const CXXRecordDecl* inv_union = result.Nodes.getNodeAs<CXXRecordDecl>("union");
  const bool is_anon = inv_union->isAnonymousStructOrUnion();
  std::vector<FieldDecl*> fieldDecls(inv_union->field_begin(), inv_union->field_end());
  auto filter_end = std::remove_if(fieldDecls.begin(), fieldDecls.end(),
                                   [&](const FieldDecl* decl) { return clutil::typeOf(decl) != type_s; });
  fieldDecls.erase(filter_end, fieldDecls.end());

  std::stringstream message;
  message << (is_anon ? "Anonymous union" : "Union") << " with typedef member. " << fieldDecls.size()
          << " fieldDecl violate the convention.";

  auto& ihandle = context->getIssueHandler();
  ihandle.addIssue(inv_union, moduleName(), moduleDescription());

  if (transform) {
    auto& thandle = context->getTransformationHandler();
    auto& ast_ctx = context->getASTContext();
    if (is_anon) {
      const int scalar_count = std::distance(fieldDecls.begin(), fieldDecls.end());
      const int decl_count = clutil::declCount(inv_union);
      if (decl_count == 1) {
        /*thandle.addReplacements(FixItHint::CreateReplacement(clutil::locOf(ast_ctx, inv_union),
                                                             clutil::node2str(ast_ctx, fieldDecls.front())));*/
        thandle.addReplacements(tooling::Replacement(context->getSourceManager(), inv_union, clutil::node2str(ast_ctx, fieldDecls.front())));
      } else {
        const auto union_end = clutil::locOf(ast_ctx, inv_union, true).getEnd();
        if ((decl_count - scalar_count) < 2) {
          //thandle.addReplacements(FixItHint::CreateReplacement(clutil::locOf(ast_ctx, inv_union),
          //                                                     clutil::node2str(ast_ctx, *inv_union->field_begin())));
          thandle.addReplacements(tooling::Replacement(context->getSourceManager(), inv_union, clutil::node2str(ast_ctx, *inv_union->field_begin())));
          for (auto it = inv_union->field_begin(); it != inv_union->field_end(); ++it) {
            if (it == inv_union->field_begin()) {
              continue;
            }
            thandle.addReplacements(trutil::insertString(ast_ctx, clutil::node2str(ast_ctx, *it), inv_union));
            /*
            thandle.addReplacements(
                FixItHint::CreateInsertion(union_end, "\n" + clutil::node2str(ast_ctx, *it) + ";", true));
              */
          }
        } else {
          for (auto fd : fieldDecls) {
            thandle.addReplacements(trutil::removeNode(ast_ctx, fd, true));
            //thandle.addReplacements(FixItHint::CreateRemoval(clutil::locOf(ast_ctx, fd, true)));
            thandle.addReplacements(trutil::insertString(ast_ctx, clutil::node2str(ast_ctx, fd), inv_union));
            //thandle.addReplacements(
            //    FixItHint::CreateInsertion(union_end, "\n" + clutil::node2str(ast_ctx, fd) + ";", true));
          }
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
