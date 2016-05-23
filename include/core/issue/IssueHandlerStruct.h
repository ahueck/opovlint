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

struct TranslationUnitIssues {
  std::string MainSourceFile;
  std::vector<std::shared_ptr<Issue>> Issues;
};

typedef llvm::StringMap<TranslationUnitIssues> TUIssuesMap;

} /* namespace opov */

#endif  // CORE_ISSUE_ISSUEHANDLERSTRUCT_H
