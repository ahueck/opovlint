/*
 * IssueHandler.h
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_ISSUEHANDLER_H
#define CORE_ISSUE_ISSUEHANDLER_H

#include "IssueHandlerStruct.h"

#include <llvm/ADT/StringMap.h>

#include <string>

namespace clang {
class SourceManager;
class ASTContext;
} /* namespace clang */

namespace opov {

class IssueHandler {
 private:
  std::string source;
  TUIssuesMap issues;
  clang::ASTContext* ac;

 public:
  IssueHandler();
  void setSource(const std::string& current);
  void init(clang::ASTContext* ac);
  template <typename T>
  void addIssue(T node, const std::string& module, const std::string& module_descr, std::string message = "");
  TUIssuesMap& getAllIssues();
  void clear();
  virtual ~IssueHandler();
};

} /* namespace opov */

#include "IssueHandler.hpp"

#endif // CORE_ISSUE_ISSUEHANDLER_H
