/*
 * ClangMatcherExt.h
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#ifndef CORE_UTILITY_CLANGMATCHEREXT_H
#define CORE_UTILITY_CLANGMATCHEREXT_H

#include <core/logging/Logger.h>
#include <core/utility/ClangUtil.h>

#include <clang/ASTMatchers/ASTMatchers.h>

namespace clang {
namespace ast_matchers {

#define OPOV_CKIND(__NAME__)                    \
  AST_MATCHER(CastExpr, is##__NAME__) {         \
    return Node.getCastKind() == CK_##__NAME__; \
  }
OPOV_CKIND(FloatingToBoolean)
OPOV_CKIND(ConstructorConversion)
OPOV_CKIND(LValueToRValue)
#undef OPOV_CKIND

AST_POLYMORPHIC_MATCHER_P(isTypedef, AST_POLYMORPHIC_SUPPORTED_TYPES(Expr, Decl), std::string, type) {
  const auto typeOf_expr = Node.getType().getUnqualifiedType().getAsString();
  return type == typeOf_expr;
}

AST_MATCHER(Stmt, notABinaryExpr) {
  return !isa<BinaryOperator>(Node);
}

// const internal::VariadicDynCastAllOfMatcher<Stmt, ParenExpr> parenExpr;

//#define descendant_or_self(NODE) anyOf(NODE, hasDescendant(NODE))
//#define ancestor_or_self(NODE) anyOf(NODE, hasAncestor(NODE))

template <typename T>
inline auto children_or_self(const T& node) -> decltype(anyOf(node, has(node))) {
  return anyOf(node, has(node));
}

template <typename T>
inline auto ancestor_or_self(const T& node) -> decltype(anyOf(node, hasAncestor(node))) {
  return anyOf(node, hasAncestor(node));
}

template <typename T>
inline auto descendant_or_self(const T& node) -> decltype(anyOf(node, hasDescendant(node))) {
  return anyOf(node, hasDescendant(node));
}

// TODO remove this code duplication (hasThen) once backwards compatibility is not necessary
AST_MATCHER_P(IfStmt, hasThenStmt, internal::Matcher<Stmt>, InnerMatcher) {
  // Taken from the current version of Clangs ASTMatchers.h file: Line 2922
  const Stmt* const Then = Node.getThen();
  return (Then != nullptr && InnerMatcher.matches(*Then, Finder, Builder));
}

// TODO remove this code duplication (hasElse) once backwards compatibility is not necessary
AST_MATCHER_P(IfStmt, hasElseStmt, internal::Matcher<Stmt>, InnerMatcher) {
  // Taken from the current version of Clangs ASTMatchers.h file: Line 2934
  const Stmt* const Else = Node.getElse();
  return (Else != nullptr && InnerMatcher.matches(*Else, Finder, Builder));
}

// AST_MATCHER(TagDecl, isUnion) {
//  return Node.isUnion();
//}

AST_MATCHER_P(Stmt, ofType, std::string, type) {
  opov::clutil::TypeDeducer deducer(type);
  const bool is_type = deducer.hasType(const_cast<Stmt*>(&Node));
  // auto& ct = Finder->getASTContext();
  // LOG_MSG("ofType: '" << type << "' : " << is_type << " Statement: " << opov::clutil::node2str(ct, &Node));
  return is_type;
}

AST_MATCHER_P(CastExpr, hasSubExpr, internal::Matcher<Expr>, InnerMatcher) {
  const Expr* const SubExpression = Node.getSubExpr()->IgnoreParenImpCasts();
  return (SubExpression != nullptr && InnerMatcher.matches(*SubExpression, Finder, Builder));
}

AST_MATCHER_P(CXXConstructExpr, hasImplicitConversion, std::string, type) {
  const auto constr = Node.getConstructor();
  unsigned int ctor_pos = 0;
  const unsigned int num = Node.getNumArgs();
  opov::clutil::TypeDeducer deducer(type);
  for (auto ctor_param : constr->parameters()) {
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

} /* namespace ast_matchers */
} /* namespace clang */

#endif  // CORE_UTILITY_CLANGMATCHEREXT_H
