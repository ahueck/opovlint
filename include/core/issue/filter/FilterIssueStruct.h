#ifndef FILTER_ISSUE_STRUCT_H
#define FILTER_ISSUE_STRUCT_H

#include "../Issue.h"

#include <memory>
#include <map>

namespace opov {
namespace filter {

struct FilterIssue {
	int id;
	std::shared_ptr<Issue> issue;

	/*bool operator==(const FilterIssue& rhs) const {
		return id == rhs.id && issue == rhs.issue;
	}*/
};

typedef std::map<int, FilterIssue> FilterIssueMap;

}
}

#endif
