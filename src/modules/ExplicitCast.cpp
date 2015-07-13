/*
 * ExplicitCast.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitCast.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/transformation/TransformationHandler.h>
#include <modules/ExplicitCastVisitor.h>
#include <core/issue/IssueHandler.h>
#include <core/configuration/Configuration.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ExplicitCast::ExplicitCast() {

}

void ExplicitCast::setupOnce(const Configuration* config) {
	config->getValue("global:type", type_s);
	config->getValue("ExplicitCast:header", header_cast);
	config->getValue("ExplicitCast:cast", cast_stmt);
	//this->visitor = opov::util::make_unique<ExplicitCastVisitor>(type_s);
}

void ExplicitCast::setupMatcher() {
	// TODO here we ignore constructor conversions. This case is handled in ImplicitConversion module
	StatementMatcher invalid_expl_cast = explicitCastExpr(
			unless(anyOf(isTypedef(type_s), isConstructorConversion())),
			hasSourceExpression(ofType(type_s))).bind("cast");

	this->addMatcher(invalid_expl_cast);
}

void ExplicitCast::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	const ExplicitCastExpr* e = result.Nodes.getStmtAs<ExplicitCastExpr>(
			"cast");
	auto ecast = const_cast<ExplicitCastExpr*>(e);

	auto& sm = context->getSourceManager();
	auto& ihandle = context->getIssueHandler();
	auto& ac = context->getASTContext();
	ihandle.addIssue(sm, ac, ecast, moduleName(), moduleDescription());
}

std::string ExplicitCast::moduleName() {
	return "ExplicitCast";
}

std::string ExplicitCast::moduleDescription() {
	return "C++ explicit casts of a complex object are not possible.";
}

ExplicitCast::~ExplicitCast() {
}

} // namespace module
} /* namespace opov */

