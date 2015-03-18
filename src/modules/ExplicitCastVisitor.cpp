/*
 * ExplicitCastVisitor.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitCastVisitor.h>

#include <core/ClangUtil.h>

namespace opov {
namespace module {

ExplicitCastVisitor::ExplicitCastVisitor(const std::string& type) :
		type(type), subtreeHasType(false) {

}

bool ExplicitCastVisitor::hasType(clang::ExplicitCastExpr* expr) {
	subtreeHasType = false;
	this->TraverseStmt(expr->getSubExpr()->IgnoreImpCasts());
	return subtreeHasType;
}

bool ExplicitCastVisitor::TraverseStmt(clang::Stmt* S) {
	clang::Expr* expr = clang::dyn_cast<clang::Expr>(S);
	if (expr != nullptr && clutil::typeOf(expr) == type) {
		subtreeHasType = true;
		return false;
	}
	return RecursiveASTVisitor<ExplicitCastVisitor>::TraverseStmt(S);
}

bool ExplicitCastVisitor::VisitExplicitCastExpr(clang::ExplicitCastExpr* expr) {
	return clutil::typeOf(expr) == type;
}

ExplicitCastVisitor::~ExplicitCastVisitor() {
}

} /* namespace module */
} /* namespace opov */
