/*
 * ExplicitConstructor.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitConstructor.h>

#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ExplicitConstructor::ExplicitConstructor() :
		warnOnTemplates(false) {

}

void ExplicitConstructor::setupOnce(const Configuration* config) {
	config->getValue("ExplicitConstructor:warnOnTemplates", warnOnTemplates,
			true);
	//LOG_DEBUG("warnOnTemplates: " << warnOnTemplates);
}

void ExplicitConstructor::setupMatcher() {
	auto isTemplSpecialization = hasParent(classTemplateSpecializationDecl());
	auto constructor =
			(warnOnTemplates ?
					constructorDecl(unless(isTemplSpecialization)) :
					constructorDecl(
							unless(
									anyOf(isTemplSpecialization,
											hasParent(
													recordDecl(
															hasParent(
																	classTemplateDecl()))))))).bind(
					"constructor");
	;
	addMatcher(constructor);
}

void ExplicitConstructor::run(
		const clang::ast_matchers::MatchFinder::MatchResult& result) {
	const CXXConstructorDecl* ctor = result.Nodes.getNodeAs<CXXConstructorDecl>(
			"constructor");

	if (ctor->isOutOfLine() || ctor->isExplicit() || ctor->isImplicit()
			|| ctor->isDeleted() || ctor->isCopyOrMoveConstructor()
			|| ctor->getNumParams() == 0
			|| ctor->getMinRequiredArguments() > 1) {
		return;
	}

	auto& ihandle = context->getIssueHandler();
	auto& sm = context->getSourceManager();
	auto& ac = context->getASTContext();
	ihandle.addIssue(sm, ac, ctor, moduleName(), moduleDescription());
}

std::string ExplicitConstructor::moduleName() {
	return "ExplicitConstructor";
}

std::string ExplicitConstructor::moduleDescription() {
	return "Finds (all) non-explicit constructors. Explicit constructors prevent implicit conversions.";
}

ExplicitConstructor::~ExplicitConstructor() {
}

} /* namespace module */
} /* namespace opov */
