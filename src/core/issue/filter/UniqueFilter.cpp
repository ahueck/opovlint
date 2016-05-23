#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/filter/FilterIssueStruct.h>
#include <core/issue/IssueHandlerStruct.h>

#include <unordered_map>
#include <vector>

namespace opov {
namespace filter {

UniqueFilter::UniqueFilter() {
}

std::vector<SingleIssue> UniqueFilter::apply(const TUIssuesMap& map) {
  auto to_string = [] (const std::shared_ptr<Issue> & i) -> std::string {
    std::ostringstream sstream;
    sstream << i->getLineStart() << i->getColumnStart() << i->getLineEnd() << i->getColumnEnd();
    sstream << i->getFile() << i->getModuleName() << i->getCode();
    return sstream.str();
  };

  std::unordered_map<std::string, SingleIssue> unique_issues;
  for (auto& tu_issues : map) {
    for (auto& issue : tu_issues.second.Issues) {
      std::string source_file = tu_issues.second.MainSourceFile;
      auto key = to_string(issue);
      auto search_res = unique_issues.find(key);
      if(search_res != std::end(unique_issues)) {
        search_res->second.tunit_occurences.push_back(source_file);
      } else {
        unique_issues[key] = SingleIssue{issue, {source_file}};
      }
    }
  }

  std::vector<SingleIssue> issue_vec;
  issue_vec.reserve(unique_issues.size());
  std::transform(unique_issues.begin(), unique_issues.end()
                , std::back_inserter(issue_vec)
                , [] (std::pair<const std::string, SingleIssue>& entry) { return std::move(entry.second); });
  return issue_vec;
}

UniqueFilter::~UniqueFilter() = default;

} /* namespace filter */
} /* namespace opov */
