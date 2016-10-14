/*
 * IssueHandler.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#include <core/issue/IssueHandler.h>

namespace opov {

IssueHandler::IssueHandler() : source(""), detected_issues(), ac(nullptr) {
}

void IssueHandler::setSource(const std::string& current) {
  source = current;
}

void IssueHandler::init(clang::ASTContext* ac) {
  this->ac = ac;
}

IssueVector IssueHandler::getAllIssues() {
  IssueVector issues;
  issues.reserve(detected_issues.size());
  std::transform(std::begin(detected_issues), std::end(detected_issues), std::back_inserter(issues),
                 [](std::pair<const std::string, IssueInstance>& entry) { return entry.second; });
  return issues;
}

void IssueHandler::clear() {
  source = "";
  detected_issues.clear();
}

IssueHandler::~IssueHandler() = default;

} /* namespace opov */
