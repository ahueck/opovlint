/*
 * ImplicitCastVisitorExt.h
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#ifndef ImplicitCastVisitorExt_H_
#define ImplicitCastVisitorExt_H_

#include <clang/AST/RecursiveASTVisitor.h>

#include <string>
#include <vector>

namespace opov {

namespace module {

class ImplicitCastVisitor: public clang::RecursiveASTVisitor<ImplicitCastVisitor> {
protected:
	std::vector<clang::Expr*> violations;
	clang::ASTContext& context;
	const std::string& type;
	bool subtreeHasType;
	int depth;
	int depth_implicit;

	inline bool isTopLevelImplicitCast();
	inline bool isWrappedAroundUnary(clang::Stmt* S);

protected:
	inline void afterStmt(clang::Stmt* s);
	inline bool continueSearch(clang::Stmt* s);
	inline bool handle(clang::Expr* expr);

public:
	ImplicitCastVisitor(clang::ASTContext& context,
			const std::string& type = "");
	std::vector<clang::Expr*> extractExpr(clang::Stmt* statement);bool TraverseStmt(
			clang::Stmt* S);bool VisitDeclRefExpr(clang::DeclRefExpr* expr);bool VisitImplicitCastExpr(
			clang::ImplicitCastExpr* expr);bool VisitCallExpr(
			clang::CallExpr* expr);bool VisitExplicitCastExpr(
			clang::ExplicitCastExpr* expr);
	virtual ~ImplicitCastVisitor();
};

}
}

#endif /* ImplicitCastVisitorExt_H_ */
