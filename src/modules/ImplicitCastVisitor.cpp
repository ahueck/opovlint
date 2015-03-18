/*
 * ImplicitCastVisitorExt.cpp
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#include <core/Logger.h>
#include <core/ClangUtil.h>

#include <modules/ImplicitCastVisitor.h>

namespace opov {
namespace module {

using namespace clang;

/*
 * This code has some "optimizations" that might not hold true for all cases? There needs to be more testing to be done.
 * 	1. If a node of type is found, then the global variable is set to true and the recursion is terminated completely
 * 	2. (Not implemented) the recursion could also be terminated at the TraverseStmt level with a check for !subtreeHasType
 *
 * 	In either case, the type is supposed to be propagated until the "root", which is probably either a
 * 		- 'FloatToBoolean' implicit cast
 * 		- binary/unary expression
 *
 * The above assumption must hold true for correct identification. Furthermore, extractExpr will only ever return one Expr*?
 *
 * The visitor is supposed to be executed only on relevant condition statements (If, While, Do-While, For)
 */

ImplicitCastVisitor::ImplicitCastVisitor(clang::ASTContext& context,
		const std::string& type) :
		violations(), context(context), type(type), subtreeHasType(false), depth(
				0), depth_implicit(0) {

}

std::vector<clang::Expr*> ImplicitCastVisitor::extractExpr(
		clang::Stmt* statement) {
	violations.clear();
	depth = 0;
	depth_implicit = 0;
	subtreeHasType = false;
	this->TraverseStmt(statement);
	return violations;
}

bool ImplicitCastVisitor::isTopLevelImplicitCast() {
	return depth_implicit == depth && depth_implicit == 1;
}

bool ImplicitCastVisitor::isWrappedAroundUnary(clang::Stmt* S) {
	return depth < depth_implicit && !isa<clang::ImplicitCastExpr>(S);
}

void ImplicitCastVisitor::afterStmt(clang::Stmt* S) {
	// SOLVED: also detects stuff like if(a && ...)
	// for a type float this is done with an implicit cast to bool
	// for a type complex class this is apparently solved with the overloaded operator
	clang::Expr* expr = clang::dyn_cast<clang::Expr>(S);
	if (expr) {
		if (subtreeHasType
				&& (isTopLevelImplicitCast() || isWrappedAroundUnary(S))) {
			if (!isa<BinaryOperator>(S) && !isa<ParenExpr>(S)) {
				violations.push_back(expr->IgnoreImpCasts());
				depth_implicit = 0;
			}
		}
	}
}

bool ImplicitCastVisitor::continueSearch(clang::Stmt* S) {
	const bool stop = (isa<clang::CallExpr>(S)
			|| (isa<clang::CastExpr>(S) && !isa<clang::ImplicitCastExpr>(S)))
			&& clutil::typeOf(dyn_cast<clang::Expr>(S)) != type;
	return !stop;
}

bool ImplicitCastVisitor::TraverseStmt(clang::Stmt* S) {
	++depth;
	bool ret_val = true;
	if (continueSearch(S)) {
		ret_val = RecursiveASTVisitor<ImplicitCastVisitor>::TraverseStmt(S);
	}
	afterStmt(S);
	--depth;
	return ret_val;
}

bool ImplicitCastVisitor::VisitImplicitCastExpr(clang::ImplicitCastExpr* expr) {
	if (clang::CK_FloatingToBoolean == expr->getCastKind()) {
		depth_implicit = depth;
	}
	return true;
}

bool ImplicitCastVisitor::handle(clang::Expr* expr) {
	if (clutil::typeOf(expr) == type) {
		subtreeHasType = true;
		return false;
	}

	return true;
}

bool ImplicitCastVisitor::VisitDeclRefExpr(clang::DeclRefExpr* expr) {
	return handle(expr);
}

bool ImplicitCastVisitor::VisitCallExpr(clang::CallExpr* expr) {
	return handle(expr);
}

bool ImplicitCastVisitor::VisitExplicitCastExpr(clang::ExplicitCastExpr* expr) {
	return handle(expr);
}

ImplicitCastVisitor::~ImplicitCastVisitor() {
}

}
}
