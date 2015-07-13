/*
 * ImplicitConversion.cpp
 *
 *  Created on: Jun 25, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConversion.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/Logger.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
//#include <modules/ExplicitCastVisitor.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ImplicitConversion::ImplicitConversion() {
}

void ImplicitConversion::setupOnce(const Configuration* config) {
	config->getValue("global:type", type_s);
}

void ImplicitConversion::setupMatcher() {
	StatementMatcher impl_conversion = materializeTemporaryExpr(hasTemporary(ignoringImpCasts(
										constructExpr(hasImplicitConversion(type_s), unless(temporaryObjectExpr())).bind("conversion"))));
	/*constructExpr(
			unless(hasParent(varDecl())) // TODO remove varDecl req.?
					, hasImplicitConversion(type_s)).bind("conversion");
	*/
	this->addMatcher(impl_conversion);
}

void ImplicitConversion::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	const CXXConstructExpr* expr = result.Nodes.getStmtAs<CXXConstructExpr>(
			"conversion");
	//LOG_DEBUG("Found node: " << clutil::node2str(expr, context->getSourceManager()));
	std::stringstream message;
	//message << "A cast of the source excerpt to '" << type_s << "' is a potential solution.";
	auto& ihandle = context->getIssueHandler();
	auto& sm = context->getSourceManager();
	auto& ac = context->getASTContext();
	ihandle.addIssue(sm, ac, expr, moduleName(), moduleDescription());//, message.str());
}

std::string ImplicitConversion::moduleName() {
	return "ImplicitConversion";
}

std::string ImplicitConversion::moduleDescription() {
	return "Implicit conversions are problematic, since only one user-defined conversion is allowed on a single value. WIth the complex type, this can be easily violated.";
}

ImplicitConversion::~ImplicitConversion() {
}

} /* namespace module */
} /* namespace opov */
