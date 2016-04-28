/*
 * IssueHandler.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#include <core/issue/IssueHandler.h>

namespace opov {

IssueHandler::IssueHandler()
    : source("")
    , issues()
    , ac(nullptr) {
}

void IssueHandler::setSource(const std::string& current) {
  source = current;
}

void IssueHandler::init(clang::ASTContext* ac) {
  this->ac = ac;
}

TUIssuesMap& IssueHandler::getAllIssues() {
  return issues;
}

void IssueHandler::clear() {
  source = "";
  issues.clear();
}

IssueHandler::~IssueHandler() = default;

} /* namespace opov */
