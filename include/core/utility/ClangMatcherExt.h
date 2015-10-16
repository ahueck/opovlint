/*
 * ClangMatcherExt.h
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#ifndef CLANGMATCHEREXT_H_
#define CLANGMATCHEREXT_H_

#include <core/utility/ClangUtil.h>
#include <core/logging/Logger.h>

#include <clang/ASTMatchers/ASTMatchers.h>

namespace clang {
namespace ast_matchers {

#define __CKIND(__NAME__)                       \
  AST_MATCHER(CastExpr, is##__NAME__) {         \
    return Node.getCastKind() == CK_##__NAME__; \
  }

__CKIND(FloatingToBoolean)
__CKIND(ConstructorConversion)

AST_POLYMORPHIC_MATCHER_P(isTypedef, AST_POLYMORPHIC_SUPPORTED_TYPES_2(Expr, Decl), std::string, type) {
  const auto typeOf_expr = Node.getType().getUnqualifiedType().getAsString();
  return type == typeOf_expr;
}

AST_MATCHER(Stmt, notABinaryExpr) {
  return !isa<BinaryOperator>(Node);
}

const internal::VariadicDynCastAllOfMatcher<
  Stmt,
  ParenExpr> parenExpr;

#define descendant_or_self(NODE) \
  anyOf(NODE, hasDescendant(NODE))

#define ancestor_or_self(NODE) \
  anyOf(NODE, hasAncestor(NODE))

/*
AST_MATCHER_P(IfStmt, hasThen, internal::Matcher<Stmt>, InnerMatcher) {
  // Taken from the current version of Clangs ASTMatchers.h file: Line 2922
  const Stmt *const Then = Node.getThen();
  return (Then != nullptr && InnerMatcher.matches(*Then, Finder, Builder));
}

AST_MATCHER_P(IfStmt, hasElse, internal::Matcher<Stmt>, InnerMatcher) {
  // Taken from the current version of Clangs ASTMatchers.h file: Line 2934
  const Stmt *const Else = Node.getElse();
  return (Else != nullptr && InnerMatcher.matches(*Else, Finder, Builder));
}
*/

AST_MATCHER(TagDecl, isUnion) {
  return Node.isUnion();
}

AST_MATCHER_P(Stmt, ofType, std::string, type) {
  opov::clutil::TypeDeducer deducer(type);
  const bool is_type = deducer.hasType(const_cast<Stmt*>(&Node));
  //LOG_DEBUG("ofType: '" << type << "' : " << is_type);
  return is_type;
}

AST_MATCHER_P(CastExpr, hasSubExpr, internal::Matcher<Expr>, InnerMatcher) {
  const Expr* const SubExpression = Node.getSubExpr()->IgnoreParenImpCasts();
  return (SubExpression != NULL && InnerMatcher.matches(*SubExpression, Finder, Builder));
}

AST_MATCHER_P(CXXConstructExpr, hasImplicitConversion, std::string, type) {
  const auto constr = Node.getConstructor();
  unsigned int ctor_pos = 0;
  const unsigned int num = Node.getNumArgs();
  opov::clutil::TypeDeducer deducer(type);
  for (auto ctor_param : constr->params()) {
    if (ctor_pos >= num) {
      // Will this ever be true? If yes: assume that default arg is used
      return ctor_param->hasDefaultArg();
    }
    Expr* arg_expr = const_cast<Expr*>(Node.getArg(ctor_pos)->IgnoreParenImpCasts());
    if (opov::clutil::typeOf(ctor_param) == type && !deducer.hasType(arg_expr)) {
      return true;
    }
    ++ctor_pos;
  }
  return false;
}

AST_MATCHER(CXXConstructorDecl, isCopyOrMoveCtor) {
  return Node.isCopyOrMoveConstructor();
}

AST_MATCHER_P(MaterializeTemporaryExpr, hasTemporary, internal::Matcher<Expr>, InnerMatcher) {
  return InnerMatcher.matches(*Node.GetTemporaryExpr(), Finder, Builder);
}

AST_MATCHER(NestedNameSpecifier, isGlobalNamespace) {
  return Node.getKind() == NestedNameSpecifier::SpecifierKind::Global;
}

}  // end namespace ast_matchers
}  // end namespace clang

#endif /* CLANGMATCHEREXT_H_ */
