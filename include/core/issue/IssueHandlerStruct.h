/*
 * IssueHandlerStruct.h
 *
 *  Created on: Aug 14, 2014
 *      Author: ahueck
 */

#ifndef ISSUEHANDLERSTRUCT_H_
#define ISSUEHANDLERSTRUCT_H_

#include <llvm/ADT/StringMap.h>

#include <vector>
#include <memory>

namespace opov {

class Issue;

struct TranslationUnitIssues {
  std::string MainSourceFile;
  std::vector<std::shared_ptr<Issue> > Issues;
};

typedef llvm::StringMap<TranslationUnitIssues> TUIssuesMap;

}  // namespace opov

#endif /* ISSUEHANDLERSTRUCT_H_ */
