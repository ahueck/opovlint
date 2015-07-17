/*
 * ExplicitCastVisitor.h
 *
 *  Created on: Jun 23, 2014
 *      Author: ahueck
 */

#ifndef EXPLICITCASTVISITOR_H_
#define EXPLICITCASTVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

namespace opov {
namespace module {

class ExplicitCastVisitor : public clang::RecursiveASTVisitor<ExplicitCastVisitor> {
 protected:
  const std::string& type;
  bool subtreeHasType;

 public:
  ExplicitCastVisitor(const std::string& type = "");
  bool hasType(clang::ExplicitCastExpr* expr);
  bool TraverseStmt(clang::Stmt* S);
  bool VisitExplicitCastExpr(clang::ExplicitCastExpr* expr);
  virtual ~ExplicitCastVisitor();
};

} /* namespace module */
} /* namespace opov */

#endif /* EXPLICITCASTVISITOR_H_ */
