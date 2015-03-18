/*
 * IssueHandler.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#include <core/IssueHandler.h>

namespace opov {

IssueHandler::IssueHandler() : source(""), issues() {
}

void IssueHandler::setSource(const std::string& current) {
	source = current;
}

TUIssuesMap& IssueHandler::getAllIssues() {
	return issues;
}

void IssueHandler::clear() {
	source = "";
	/*
	for(auto& issue_m : issues) {
		for(auto i : issue_m.second.Issues) {
			delete i;
		}
	}
	*/
	issues.clear();
}

IssueHandler::~IssueHandler() {
}

} /* namespace opov */
