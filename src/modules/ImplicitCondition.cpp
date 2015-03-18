/*
 * ImplicitCondition.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitCondition.h>

#include <core/ModuleContext.h>
#include <core/Util.h>
#include <core/ClangUtil.h>
#include <core/Issue.h>
#include <core/ClangMatcherExt.h>
#include <core/Logger.h>
#include <core/IssueHandler.h>
#include <core/Configuration.h>

#include <modules/ImplicitCastVisitor.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ImplicitCondition::ImplicitCondition() {

}

void ImplicitCondition::setupOnce(const Configuration* config) {
	config->getValue("global:type", type_s);
}

void ImplicitCondition::setupMatcher() {
	StatementMatcher type_use = expr(
			anyOf(declRefExpr(isTypedef(type_s)), callExpr(isTypedef(type_s)),
					explicitCastExpr(isTypedef(type_s))));

	StatementMatcher impl = implicitCastExpr(isFloatingToBoolean(),
			hasDescendant(type_use));
	auto typedef_condition = hasCondition(
			expr(anyOf(impl, expr(hasDescendant(impl)))).bind("condition"));

	StatementMatcher all_cond = stmt(
			anyOf(ifStmt(typedef_condition), forStmt(typedef_condition),
					doStmt(typedef_condition), whileStmt(typedef_condition),
					conditionalOperator(typedef_condition))).bind("stmt");
	addMatcher(all_cond);
}

void ImplicitCondition::execute(opov::ModuleContext* context) {
	visitor = opov::util::make_unique<ImplicitCastVisitor>(
			context->getASTContext(), type_s);
	opov::ASTMatcherModule::execute(context);
}

void ImplicitCondition::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	/*
	 const IfStmt* t1 = result.Nodes.getStmtAs<IfStmt>("stmt");
	 if(!t1) {
	 LOG_DEBUG("Stmt is null!");
	 return;
	 }
	 */
	const Expr* t2 = result.Nodes.getStmtAs<Expr>("condition");
	if (!t2) {
		LOG_DEBUG("Condition is null!");
		return;
	}
	//LOG_DEBUG("Stmt: " << stmt2str(t1, *result.SourceManager));
	//LOG_DEBUG("Cond: " << stmt2str(t2, *result.SourceManager));
	//IfStmt* st = const_cast<IfStmt*>(t1);
	auto& ihandle = context->getIssueHandler();
	auto& sm = context->getSourceManager();
	const auto& invalid_expr = visitor->extractExpr(const_cast<Expr*>(t2));
	for (auto e : invalid_expr) {
		ihandle.addIssue(sm, e, moduleName(), moduleDescription());
	}
}

std::string ImplicitCondition::moduleName() {
	return "ImplicitCondition";
}

std::string ImplicitCondition::moduleDescription() {
	return "Implicit conditions (implicit conversion to a bool) is not possible with a complex object.";
}

ImplicitCondition::~ImplicitCondition() {
}

}
}
