/*
 * IssueHandler.h
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#ifndef ISSUEHANDLER_H_
#define ISSUEHANDLER_H_

#include "IssueHandlerStruct.h"
#include <string>
#include <llvm/ADT/StringMap.h>

namespace clang {
class SourceManager;
}

namespace opov {

class IssueHandler {
private:
	std::string source;
	TUIssuesMap issues;

public:
	IssueHandler();
	void setSource(const std::string& source);
	template<typename T>
	void addIssue(const clang::SourceManager& sm, T node, const std::string& code, const std::string& module, const std::string& module_descr, std::string message="");
	TUIssuesMap& getAllIssues();
	void clear();
	virtual ~IssueHandler();
};

} /* namespace opov */

#include "IssueHandler.hpp"

#endif /* ISSUEHANDLER_H_ */
