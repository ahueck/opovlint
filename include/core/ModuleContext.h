/*
 * ModuleContext.h
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#ifndef MODULECONTEXT_H_
#define MODULECONTEXT_H_

#include <memory>
#include <vector>

namespace clang {
class ASTContext;
class SourceManager;
namespace tooling {
class Replacement;
}
}

namespace opov {

class Configuration;
class Issue;
class IssueHandler;
class TransformationHandler;

class ModuleContext {
protected:
	Configuration* config;
	std::vector<Issue*> issues;
	//std::vector<clang::tooling::Replacement> replacements;
	clang::ASTContext* context;
	IssueHandler* ihandler;
	TransformationHandler* thandler;

public:
	ModuleContext(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
	void setASTContext(clang::ASTContext* context);
	clang::ASTContext& getASTContext();
	clang::SourceManager& getSourceManager();
	//IssueReporter& getIssues();
	//std::vector<Issue*>& getIssues();
	//std::vector<clang::tooling::Replacement>& getReplacements();
	IssueHandler& getIssueHandler();
	TransformationHandler& getTransformationHandler();
	virtual ~ModuleContext();
};
} // namespace opov

#endif /* MODULECONTEXT_H_ */
