#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/IssueHandlerStruct.h>

#include <map>

namespace opov {
namespace filter {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

IssueSet UniqueFilter::apply(const TUIssuesMap& unfilteredIssues) {
  IssueSet unique_issues;
  for(auto& tu_issues : unfilteredIssues) {
    for(auto& issue : tu_issues.second.Issues) {
      const int ihash =issue->hash();
      auto result = unique_issues.find(ihash);
      if(result != std::end(unique_issues)) {
        result->second.tunits.push_back(tu_issues.second.MainSourceFile);
      } else {
        IssuesFiltered ifiltered;
        ifiltered.issue = issue;
        ifiltered.tunits.push_back(tu_issues.second.MainSourceFile);
        unique_issues[ihash] = ifiltered;
      }
    }
  }
  return unique_issues;
}

}
}
