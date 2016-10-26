/*
 * IssueHandler.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#include <core/issue/IssueHandler.h>

#include <algorithm>

namespace opov {

IssueHandler::IssueHandler() : source(""), detected_issues(), ac(nullptr) {
}

void IssueHandler::setSource(const std::string& current) {
  source = current;
}

void IssueHandler::init(clang::ASTContext* ac) {
  this->ac = ac;
}

IssueVector IssueHandler::getAllIssues(bool sorted) {
  IssueVector issues;
  issues.reserve(detected_issues.size());
  std::transform(std::begin(detected_issues), std::end(detected_issues), std::back_inserter(issues),
                 [](std::pair<const std::string, IssueInstance>& entry) { return entry.second; });
  if (sorted) {
    std::sort(std::begin(issues), std::end(issues), [](const IssueInstance& a, const IssueInstance& b) {
      const auto& tmp_a = a.issue;
      const auto& tmp_b = b.issue;
      const auto& module_a = tmp_a->getModuleName();
      const auto& module_b = tmp_b->getModuleName();
      return module_a < module_b || (module_a == module_b && tmp_a->getLineStart() < tmp_b->getLineStart());
    });
  }
  return issues;
}

void IssueHandler::clear() {
  source = "";
  detected_issues.clear();
}

IssueHandler::~IssueHandler() = default;

} /* namespace opov */
