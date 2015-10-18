#ifndef FILTER_ISSUE_STRUCT_H
#define FILTER_ISSUE_STRUCT_H

#include "../Issue.h"

#include <memory>
#include <map>
#include <vector>

namespace opov {
namespace filter {

struct IssuesFiltered {
	std::shared_ptr<Issue> issue;
	std::vector<std::string> tunits;
};

struct issue_compare {
  bool operator() (const IssuesFiltered& a, const IssuesFiltered& b) {
    return a.issue->hash() != b.issue->hash();
  }
};

typedef std::map<int, IssuesFiltered> IssueSet;

}
}

#endif
