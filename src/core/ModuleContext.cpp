/*
 * ModuleContext.cpp
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#include <core/ModuleContext.h>

#include <core/IssueHandler.h>
#include <core/TransformationHandler.h>
#include <core/Issue.h>
#include <core/IssueReporter.h>

#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Tooling/Refactoring.h>
//#include <clang/AST/AST.h>

namespace opov {
ModuleContext::ModuleContext(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler) :
		config(config), issues(), context(nullptr), ihandler(ihandler), thandler(thandler) {
	issues.reserve(100);
}

void ModuleContext::setASTContext(clang::ASTContext* context) {
	this->context = context;
}

clang::ASTContext& ModuleContext::getASTContext() {
	return *context;
}

clang::SourceManager& ModuleContext::getSourceManager() {
	return context->getSourceManager();
}

TransformationHandler& ModuleContext::getTransformationHandler() {
	return *thandler;
}

IssueHandler& ModuleContext::getIssueHandler() {
	return *ihandler;
}
/*
std::vector<Issue*>& ModuleContext::getIssues() {
	return issues;
}
*/
/*
 void ModuleContext::addIssue(Issue* report) {
 issues.push_back(report);
 }
 */

/*
 IssueReporter& ModuleContext::getIssues() {
 return issues;
 }
 */
ModuleContext::~ModuleContext() {
}
}

