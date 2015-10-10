/*
 * TransformationUtil.h
 *
 *  Created on: Jul 28, 2014
 *      Author: ahueck
 */

#ifndef TRANSFORMATIONUTIL_H_
#define TRANSFORMATIONUTIL_H_

#include <core/utility/ClangUtil.h>

#include <clang/Tooling/Refactoring.h>

#include <vector>

//#include <clang/Lex/Lexer.h>

namespace opov {
namespace trutil {

using namespace clang::tooling;
using namespace clang;
using namespace clutil;

static inline bool isWhitespace(unsigned char c) {
  switch (c) {
    case ' ':
    case '\t':
    case '\f':
    case '\v':
    case '\r':
      return true;
    default:
      return false;
  }
}

template <typename T>
inline StringRef whitespaces(const clang::SourceManager& sm, T node) {
  // Taken from the clang::Rewriter source code.
  SourceRange range = locOf(sm, node);
  // const char* data = sm.getCharacterData(range.getBegin());
  std::pair<FileID, unsigned> V = sm.getDecomposedLoc(range.getBegin());
  StringRef text = sm.getBufferData(V.first);
  unsigned startLineNo = sm.getLineNumber(V.first, V.second) - 1;
  auto cache = sm.getSLocEntry(V.first).getFile().getContentCache();
  unsigned startLineOff = cache->SourceLineCache[startLineNo];
  unsigned i = startLineOff;
  while (isWhitespace(text[i])) {
    ++i;
  }
  StringRef spaces = text.substr(startLineOff, i - startLineOff);
  return spaces;
}

inline clang::tooling::Replacement removeCastFromExpr(const clang::SourceManager& sm,
                                                      const clang::ExplicitCastExpr* expr) {
  SourceRange range = locOf(sm, expr);
  CharSourceRange cast_crange = CharSourceRange::getCharRange(range);
  StringRef replacement_str(clutil::node2str(sm, expr->getSubExprAsWritten()));
  return Replacement(sm, cast_crange, replacement_str);
}

inline std::vector<clang::tooling::Replacement> addExplicitCompare(const clang::SourceManager& sm,
                                                                   const clang::Expr* expr, StringRef with_type) {
  SourceRange range = locOf(sm, expr);
  SmallString<32> replace(" == ");
  replace += with_type;
  replace += "(0.0)";
  if (isa<UnaryOperator>(expr)) {
    replace += ")";
    return {Replacement(sm, llvm::dyn_cast<UnaryOperator>(expr)->getSubExpr()->getLocStart(), 0, "("),
            Replacement(sm, range.getEnd(), 0, replace)};
  } else {
    return {Replacement(sm, range.getEnd(), 0, replace)};
  }
}
/*
inline std::vector<clang::tooling::Replacement> addExplicitCompare(const
clang::SourceManager& sm, const clang::UnaryOperator* expr, StringRef with_type)
{
        SourceRange range = locOf(sm, expr);
        SmallString<32> replace(" == ");
        replace += with_type;
        replace += "(0.0))";
        return {Replacement(sm, expr->getSubExpr()->getLocStart(), 0, "("),
Replacement(sm, range.getEnd(), 0, replace)};
}
*/
inline clang::tooling::Replacement insertString(const clang::SourceManager& sm, const clang::Stmt* expr, StringRef str,
                                                bool before = false) {
  SourceRange range = locOf(sm, expr);
  std::string formattedStr;
  if (before) {
    formattedStr = str;
    formattedStr += whitespaces(sm, expr);
  } else {
    formattedStr = whitespaces(sm, expr);
    formattedStr += str;
  }
  return Replacement(sm, before ? range.getBegin() : range.getEnd(), 0, formattedStr);
}

inline std::vector<clang::tooling::Replacement> castTheExpr(const clang::SourceManager& sm, const clang::Expr* expr,
                                                            const StringRef type,
                                                            int cast = Expr::CXXFunctionalCastExprClass) {
  SmallString<32> castStr;
  switch (cast) {
    case Expr::CXXStaticCastExprClass:
      castStr = "static_cast<";
      castStr += type;
      castStr += ">";
      break;
    case Expr::CXXFunctionalCastExprClass:
    default:
      castStr = type;
  }
  castStr += "(";
  SourceRange range = locOf(sm, expr);
  return {Replacement(sm, range.getBegin(), 0, castStr), Replacement(sm, range.getEnd(), 0, ")")};
}

template <typename T>
inline clang::tooling::Replacement removeNode(const clang::SourceManager& sm, T node) {
  // FIXME does not remove empty line
  SourceRange loc = locOf(sm, node, 1);
  CharSourceRange cast_crange = CharSourceRange::getCharRange(loc);
  return Replacement(sm, cast_crange, "");
}

template <typename T, typename U>
inline clang::tooling::Replacement insertNode(const clang::SourceManager& sm, T to_insert, U relative_to,
                                              bool before = false, char endl = ';') {
  // FIXME does not preserve indentation
  SourceRange range = locOf(sm, relative_to, 1);
  StringRef replacement_str;
  if (before) {
    replacement_str = clutil::node2str(sm, to_insert) + endl + "\n" + whitespaces(sm, relative_to).str();
    return Replacement(sm, range.getBegin(), 0, replacement_str);
  }
  replacement_str = whitespaces(sm, relative_to).str() + "\n" + clutil::node2str(sm, to_insert) + endl;
  return Replacement(sm, range.getEnd(), 0, replacement_str);
}

}
}

#endif /* TRANSFORMATIONUTIL_H_ */
