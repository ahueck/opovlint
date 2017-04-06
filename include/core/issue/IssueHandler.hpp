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

#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>

#include <memory>

namespace opov {

template <typename T>
void IssueHandler::addIssue(T node, const std::string& module, const std::string& module_descr, std::string message) {
  auto& sm = ac->getSourceManager();

  auto issue_file = clutil::fileOriginOf(sm, node);
  auto node_source = clutil::node2str(*ac, node);
  int line_s, line_e, col_s, col_e;
  std::tie(line_s, line_e, col_s, col_e) = clutil::posOf(sm, node);

  auto make_key = [&]() -> std::string {
    std::ostringstream sstream;
    sstream << line_s << line_e << col_s << col_e;
    sstream << issue_file << module << node_source;
    return sstream.str();
  };

  auto key = make_key();
  auto search_res = detected_issues.find(key);
  if (search_res != std::end(detected_issues)) {
    search_res->second.tunit_occurences.push_back(source);
  } else {
    auto issue = std::make_shared<Issue>();
    issue->setModuleName(module);
    issue->setModuleDescription(module_descr);
    issue->setDescription(message);
    issue->setCode(node_source);
    issue->setLineStart(line_s);
    issue->setLineEnd(line_e);
    issue->setColumnStart(col_s);
    issue->setColumnEnd(col_e);
    issue->setFile(issue_file);
    auto instance = source == issue_file ? IssueInstance{issue, {}} : IssueInstance{issue, {source}};
    detected_issues[key] = instance;
  }
}

} /* namespace opov */

#endif /* ISSUEHANDLER_HPP_ */
