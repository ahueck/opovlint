/*
 * IssueHandlerStruct.h
 *
 *  Created on: Aug 14, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_ISSUEHANDLERSTRUCT_H
#define CORE_ISSUE_ISSUEHANDLERSTRUCT_H

#include <llvm/ADT/StringMap.h>

#include <vector>

namespace opov {

class Issue;

using IssueInstance = struct {
  std::shared_ptr<Issue> issue;
  std::vector<std::string> tunit_occurences;
};

using IssueVector = std::vector<IssueInstance>;

} /* namespace opov */

#endif  // CORE_ISSUE_ISSUEHANDLERSTRUCT_H
