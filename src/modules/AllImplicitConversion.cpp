/*
 * AllImplicitConversion.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/AllImplicitConversion.h>

#include <core/ClangMatcherExt.h>
#include <core/ClangUtil.h>
#include <core/Configuration.h>
#include <core/IssueHandler.h>
#include <core/ModuleContext.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

AllImplicitConversion::AllImplicitConversion() {
	// TODO Auto-generated constructor stub

}

void AllImplicitConversion::setupOnce(const Configuration* config) {
}

void AllImplicitConversion::setupMatcher() {
	StatementMatcher impl_conversion = materializeTemporaryExpr(hasTemporary(ignoringImpCasts(constructExpr().bind("conversion"))));

			/*constructExpr(unless(anyOf(
															hasDeclaration(constructorDecl(isCopyOrMoveCtor()))
															, hasParent(explicitCastExpr(isConstructorConversion()))
															, hasParent(varDecl())))
													).bind("conversion");*/
	this->addMatcher(impl_conversion);
}

void AllImplicitConversion::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	const CXXConstructExpr* expr = result.Nodes.getStmtAs<CXXConstructExpr>(
			"conversion");
	auto& sm = context->getSourceManager();
	auto& ihandle = context->getIssueHandler();
	ihandle.addIssue(sm, expr, moduleName(), moduleDescription());
}

std::string AllImplicitConversion::moduleName() {
	return "AllImplicitConversion";
}

std::string AllImplicitConversion::moduleDescription() {
	return "Detects *all* implicit conversions.";
}

AllImplicitConversion::~AllImplicitConversion() {
	// TODO Auto-generated destructor stub
}

} /* namespace module */
} /* namespace opov */
