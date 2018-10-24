/*
 * ClangUtil.h
 *
 *  Created on: May 13, 2014
 *      Author: ahueck
 */

#ifndef CORE_UTILITY_CLANGUTIL_H
#define CORE_UTILITY_CLANGUTIL_H

#include <core/logging/Logger.h>

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/TextDiagnostic.h>
#include <clang/Lex/Lexer.h>

#include <llvm/ADT/StringRef.h>

#include <iterator>
#include <sstream>
#include <string>

namespace opov {

namespace clutil {

inline clang::SourceLocation findLocationAfterSemi(clang::SourceLocation loc, clang::ASTContext& Ctx, bool IsDecl);
inline clang::SourceLocation findSemiAfterLocation(clang::SourceLocation loc, clang::ASTContext& Ctx, bool IsDecl);

template <typename T>
inline clang::SourceRange locOf(const clang::SourceManager& sm, T node, unsigned int offset = 0) {
  // offset=1 includes ';' (assuming no whitespaces)
  clang::SourceLocation start(node->getLocStart());
  clang::SourceLocation end(clang::Lexer::getLocForEndOfToken(node->getLocEnd(), 0, sm, clang::LangOptions()));
  return {start, end.getLocWithOffset(offset)};
}

template <typename T>
inline clang::SourceRange locOf(clang::ASTContext& ac, T node, bool semicolon = false) {
  clang::SourceLocation start(node->getLocStart());
  // clang::SourceLocation end(node->getLocEnd());
  clang::SourceLocation end(
      clang::Lexer::getLocForEndOfToken(node->getLocEnd(), 0, ac.getSourceManager(), clang::LangOptions()));
  if (semicolon) {
    clang::SourceLocation semi_end = findLocationAfterSemi(node->getLocEnd(), ac, llvm::isa<clang::Decl>(node));
    // LOG_MSG(semi_end.isValid() << ": " << semi_end.printToString(ac.getSourceManager()) << ", " <<
    // end.printToString(ac.getSourceManager()));
    return {start, semi_end.isValid() ? semi_end : end};
  }
  return {start, end};
}

template <typename T>
inline std::string typeOf(T&& node) {
  auto type = node->getType();
  if (!type.isNull()) {
    return type.getUnqualifiedType().getAsString();
  }
  return "";
}

inline std::string nameOf(const clang::NamedDecl* decl) {
  return decl->getNameAsString();
}

inline std::string nameOf(const clang::DeclRefExpr* expr) {
  return nameOf(expr->getDecl());
}

template <typename T>
inline clang::FileID fileIDOf(const clang::SourceManager& sm, T node) {
  const auto range = locOf(sm, node);
  return sm.getFileID(range.getBegin());
}

template <typename T>
inline const clang::FileEntry* fileEntryOf(const clang::SourceManager& sm, T node) {
  auto file_id = fileIDOf(sm, node);
  return sm.getFileEntryForID(file_id);
}

template <typename T>
inline std::string fileOriginOf(const clang::SourceManager& sm, T node) {
  auto Entry = fileEntryOf(sm, node);
  if (Entry != nullptr) {
    llvm::SmallString<256> FilePath(Entry->getName());
    auto EC = llvm::sys::fs::make_absolute(FilePath);
    return EC ? FilePath.c_str() : Entry->getName();
  }
  return {""};
}

inline llvm::StringRef mainFilename(const clang::SourceManager& sm) {
  if (const auto* F = sm.getFileEntryForID(sm.getMainFileID())) {
    return F->getName();
  }

  return llvm::StringRef();
}

inline unsigned declCount(const clang::TagDecl* node) {
  auto range = node->decls();
  return std::distance(range.begin(), range.end());
}

/*
 * Taken from the official clang documentation:
 * see: http://clang.llvm.org/docs/LibASTMatchersTutorial.html
 */
inline bool areSameExpr(clang::ASTContext* context, const clang::Expr* first, const clang::Expr* second) {
  if (first == nullptr || second == nullptr) {
    return false;
  }
  llvm::FoldingSetNodeID FirstID, SecondID;
  first->Profile(FirstID, *context, true);
  second->Profile(SecondID, *context, true);
  return FirstID == SecondID;
}

template <typename T>
inline std::tuple<unsigned, unsigned> rowOf(const clang::SourceManager& sm, T node, bool semicolon = false) {
  auto range = locOf(sm, node, semicolon);
  return std::make_tuple(sm.getPresumedLineNumber(range.getBegin()), sm.getPresumedLineNumber(range.getEnd()));
}

template <typename T>
inline std::tuple<unsigned, unsigned> colOf(const clang::SourceManager& sm, T node, bool semicolon = false) {
  auto range = locOf(sm, node, semicolon);
  return std::make_tuple(sm.getPresumedColumnNumber(range.getBegin()), sm.getPresumedColumnNumber(range.getEnd()));
}

template <typename T>
inline std::tuple<unsigned, unsigned, unsigned, unsigned> posOf(const clang::SourceManager& sm, T node,
                                                                bool semicolon = false) {
  return std::tuple_cat(rowOf(sm, node, semicolon), colOf(sm, node, semicolon));
}

template <typename T>
inline std::string ast2str(/*const clang::SourceManager& sm,*/ T&& node) {
  std::string exprStr;
  llvm::raw_string_ostream s(exprStr);
  node.dump(s); /*, const_cast<clang::SourceManager&>(sm)); // FIXME const_cast
                    necessary for clang 3.5 */
  return s.str();
}

inline std::string node2str(const clang::ASTContext& ac, const clang::Stmt* node) {
  std::string exprStr;
  llvm::raw_string_ostream s(exprStr);
  node->printPretty(s, nullptr, ac.getPrintingPolicy());
  return s.str();
}

inline std::string node2str(const clang::ASTContext& ac, const clang::Decl* node) {
  std::string declStr;
  llvm::raw_string_ostream s(declStr);
  node->print(s, ac.getPrintingPolicy());
  return s.str();
}

// Both functions taken from File "Transform.cpp": lib/ARCMigrate/Transforms.cpp
inline clang::SourceLocation findLocationAfterSemi(clang::SourceLocation loc, clang::ASTContext& Ctx, bool IsDecl) {
  using namespace clang;
  SourceLocation SemiLoc = findSemiAfterLocation(loc, Ctx, IsDecl);
  if (SemiLoc.isInvalid()) {
    return SourceLocation();
  }
  return SemiLoc.getLocWithOffset(1);
}

inline clang::SourceLocation findSemiAfterLocation(clang::SourceLocation loc, clang::ASTContext& Ctx, bool IsDecl) {
  /// \brief \arg Loc is the end of a statement range. This returns the location
  /// of the semicolon following the statement.
  /// If no semicolon is found or the location is inside a macro, the returned
  /// source location will be invalid.
  using namespace clang;
  using namespace llvm;
  SourceManager& SM = Ctx.getSourceManager();
  if (loc.isMacroID()) {
    if (!Lexer::isAtEndOfMacroExpansion(loc, SM, Ctx.getLangOpts(), &loc)) {
      return SourceLocation();
    }
  }
  loc = Lexer::getLocForEndOfToken(loc, /*Offset=*/0, SM, Ctx.getLangOpts());

  // Break down the source location.
  std::pair<FileID, unsigned> locInfo = SM.getDecomposedLoc(loc);

  // Try to load the file buffer.
  bool invalidTemp = false;
  StringRef file = SM.getBufferData(locInfo.first, &invalidTemp);
  if (invalidTemp) {
    return SourceLocation();
  }
  const char* tokenBegin = file.data() + locInfo.second;

  // Lex from the start of the given location.
  Lexer lexer(SM.getLocForStartOfFile(locInfo.first), Ctx.getLangOpts(), file.begin(), tokenBegin, file.end());
  Token tok;
  lexer.LexFromRawLexer(tok);
  if (tok.isNot(tok::semi)) {
    if (!IsDecl) {
      return SourceLocation();
    }
    // Declaration may be followed with other tokens; such as an __attribute,
    // before ending with a semicolon.
    return findSemiAfterLocation(tok.getLocation(), Ctx, /*IsDecl*/ true);
  }

  return tok.getLocation();
}

class TypeDeducer final : public clang::RecursiveASTVisitor<TypeDeducer> {
 private:
  bool subtree_has_type;
  std::string type;
  bool is_builtin;

 public:
  explicit TypeDeducer(const std::string& type)
      : subtree_has_type(false), type(type), is_builtin(is_builtin_type(type)) {
  }

  template <typename NODE>
  bool hasType(NODE node) {
    this->subtree_has_type = false;
    this->TraverseStmt(node);

    return subtree_has_type;
  }

  bool TraverseStmt(clang::Stmt* S) {
    clang::Expr* expr = clang::dyn_cast<clang::Expr>(S);
    if (expr != nullptr) {
      subtree_has_type = type_found(expr);
      const bool terminate_recursion = terminate(expr);
      if (subtree_has_type || terminate_recursion) {
        return false;
      }
    }

    return RecursiveASTVisitor<TypeDeducer>::TraverseStmt(S);
  }

 private:
  inline static bool is_builtin_type(const std::string& type) {
    return type == "double" || type == "float";
  }

  inline bool type_found(clang::Expr* expr) {
    // we cont. if binary/parens returns double/float, happens even with typedef
    // types
    // TODO: possibly extend to unary ops too!
    // clang-format off
    return typeOf(expr) == type
              && !(is_builtin
                    && (
                          clang::isa<clang::BinaryOperator>(expr)
                          || clang::isa<clang::ImplicitCastExpr>(expr)
                          || clang::isa<clang::ParenExpr>(expr)
                       )
                  );
    // clang-format on
  }

  inline bool terminate(clang::Expr* expr) {
    // TODO should we terminate on binary expr?
    const std::string typeOfE = typeOf(expr);
    // clang-format off
    const bool expr_returns_bool =
        typeOfE == "_Bool"
          && (
                clang::isa<clang::UnaryOperator>(expr)
                || clang::isa<clang::BinaryOperator>(expr)
                || clang::isa<clang::CallExpr>(expr)
             );
    const bool type_is_swallowed =
        typeOfE != type
          && (
                clang::isa<clang::ExplicitCastExpr>(expr)
                || clang::isa<clang::CallExpr>(expr)
             );
    // clang-format on
    return expr_returns_bool || type_is_swallowed;
  }
};

} /* namespace clutil */
} /* namespace opov */

#endif  // CORE_UTILITY_CLANGUTIL_H
