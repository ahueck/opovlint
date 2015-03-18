/*
 * ImplicitConditionMatcher.cpp
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConditionMatcher.h>
#include <core/ClangMatcherExt.h>
#include <core/ModuleContext.h>
#include <core/Logger.h>
#include <core/ClangUtil.h>
#include <core/IssueHandler.h>
#include <core/IssueHandler.h>
#include <core/TransformationHandler.h>
#include <core/TransformationUtil.h>
#include <core/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ImplicitConditionMatcher::ImplicitConditionMatcher() {

}

void ImplicitConditionMatcher::setupOnce(const Configuration* config) {
	config->getValue("global:type", type_s);
}

void ImplicitConditionMatcher::setupMatcher() {
	auto impl = implicitCastExpr(isFloatingToBoolean(),
			unless(hasParent(binaryOperator())),
			hasSourceExpression(ofType(type_s))).bind("implicit");
	auto unaryMatch = unaryOperator(
			hasUnaryOperand(
					implicitCastExpr(isFloatingToBoolean(),
							hasSourceExpression(ofType(type_s))))).bind(
			"unary");
	auto typedef_condition = hasCondition(
			anyOf(unaryMatch, expr(hasDescendant(unaryMatch)), impl,
					expr(hasDescendant(impl))));

	StatementMatcher all_cond = stmt(
			anyOf(ifStmt(typedef_condition), forStmt(typedef_condition),
					doStmt(typedef_condition), whileStmt(typedef_condition),
					conditionalOperator(typedef_condition))).bind("stmt");

	this->addMatcher(all_cond);
}

void ImplicitConditionMatcher::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	const Expr* implicit_cast = result.Nodes.getStmtAs<Expr>("implicit");
	const Expr* unary_op = result.Nodes.getStmtAs<Expr>("unary");
	const Expr* invalid = !implicit_cast ? unary_op : implicit_cast;
	auto& ihandle = context->getIssueHandler();
	auto& thandle = context->getTransformationHandler();
	auto& sm = context->getSourceManager();
	ihandle.addIssue(sm, invalid, moduleName(), moduleDescription());
	thandle.addReplacements(trutil::addExplicitCompare(sm, invalid , type_s));
	/*
	if(implicit_cast) {
		thandle.addReplacements(trutil::addExplicitCompare(sm, implicit_cast , type_s));
	} else {
		thandle.addReplacements(trutil::addExplicitCompare(sm, llvm::dyn_cast<UnaryOperator>(unary_op) , type_s));
	}
	*/
}

std::string ImplicitConditionMatcher::moduleName() {
	return "ImplicitConditionMatcher";
}

std::string ImplicitConditionMatcher::moduleDescription() {
	return "Implicit conditions (implicit conversion to a bool) is not possible with a complex object.";
}

ImplicitConditionMatcher::~ImplicitConditionMatcher() {
}

} // namespace module
} /* namespace opov */
