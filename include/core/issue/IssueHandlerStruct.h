/*
 * IssueHandlerStruct.h
 *
 *  Created on: Aug 14, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_ISSUEHANDLERSTRUCT_H
#define CORE_ISSUE_ISSUEHANDLERSTRUCT_H

#include <memory>
#include <string>
#include <vector>

namespace opov {

class Issue;

struct IssueInstance {
  std::shared_ptr<Issue> issue;
  std::vector<std::string> tunit_occurences;
};

using IssueVector = std::vector<IssueInstance>;

} /* namespace opov */

#endif  // CORE_ISSUE_ISSUEHANDLERSTRUCT_H
