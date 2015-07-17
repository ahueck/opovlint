/*
 * IssueHandler.hpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#ifndef ISSUEHANDLER_HPP_
#define ISSUEHANDLER_HPP_

#include <core/issue/Issue.h>
#include <core/utility/ClangUtil.h>

#include <clang/Basic/SourceManager.h>
#include <clang/AST/ASTContext.h>

#include <memory>

namespace opov {

template <typename T>
void IssueHandler::addIssue(const clang::SourceManager& sm, const clang::ASTContext& ac, T node,
                            const std::string& module, const std::string& module_descr, std::string message) {
  std::shared_ptr<Issue> issue = std::make_shared<Issue>();
  std::string issue_file = clutil::fileOriginOf(sm, node);
  auto pos = clutil::posOf(sm, node);
  std::string node_source = clutil::node2str(ac, node);
  issue->setModuleName(module);
  issue->setModuleDescription(module_descr);
  issue->setDescription(message);
  issue->setCode(node_source);
  issue->setLineStart(std::get<0>(pos));
  issue->setLineEnd(std::get<1>(pos));
  issue->setColumnStart(std::get<2>(pos));
  issue->setColumnEnd(std::get<3>(pos));
  issue->setFile(issue_file);

  TranslationUnitIssues& tunit = issues[source];
  if (tunit.MainSourceFile.empty()) {
    tunit.MainSourceFile = source;
  }
  tunit.Issues.push_back(issue);
}
}

#endif /* ISSUEHANDLER_HPP_ */
