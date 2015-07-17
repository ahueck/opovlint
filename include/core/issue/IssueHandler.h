/*
 * IssueHandler.h
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#ifndef ISSUEHANDLER_H_
#define ISSUEHANDLER_H_

#include "IssueHandlerStruct.h"

#include <llvm/ADT/StringMap.h>

#include <string>

namespace clang {
class SourceManager;
class ASTContext;
}

namespace opov {

class IssueHandler {
 private:
  std::string source;
  TUIssuesMap issues;

 public:
  IssueHandler();
  void setSource(const std::string& source);
  template <typename T>
  void addIssue(const clang::SourceManager& sm, const clang::ASTContext& ac, T node, const std::string& module,
                const std::string& module_descr, std::string message = "");
  TUIssuesMap& getAllIssues();
  void clear();
  virtual ~IssueHandler();
};

} /* namespace opov */

#include "IssueHandler.hpp"

#endif /* ISSUEHANDLER_H_ */
