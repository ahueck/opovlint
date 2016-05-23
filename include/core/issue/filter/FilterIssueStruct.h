#ifndef CORE_ISSUE_FILTER_FILTERISSUESTRUCT_H
#define CORE_ISSUE_FILTER_FILTERISSUESTRUCT_H

#include "../Issue.h"

#include <map>
#include <memory>
#include <vector>

namespace opov {
namespace filter {

struct IssuesFiltered {
  std::shared_ptr<Issue> issue;
  std::vector<std::string> tunits;
};

struct issue_compare {
  bool operator()(const IssuesFiltered& a, const IssuesFiltered& b) {
    return a.issue->hash() != b.issue->hash();
  }
};

using IssueSet = std::map<int, IssuesFiltered>;

} /* namespace filter */
} /* namespace opov */

#endif
