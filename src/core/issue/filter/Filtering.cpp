#include <core/issue/filter/Filtering.h>
#include <core/issue/filter/FilterIssueStruct.h>
#include <core/issue/filter/IFilter.h>

#include <iostream>

namespace opov {
namespace filter {

Filtering::Filtering(IFilter* mainFilter) : mainFilter(mainFilter) {
}

Filtering::~Filtering() {
}

TUIssuesMap Filtering::filter(const TUIssuesMap& unfilteredIssues) {

	//First give all issues a unique ID
	FilterIssueMap filterIssueMap;
	int id = 0;
    for (auto& unit : unfilteredIssues) {
        for (auto& issue : unit.second.Issues) {
        	FilterIssue fi;
        	fi.id = id;
        	fi.issue = issue;
        	filterIssueMap[id] = fi;
        	id++;
        }
    }

    if (mainFilter != nullptr) {
      // Filtering
      filterIssueMap = mainFilter->apply(filterIssueMap);
    }

	// Transform map back into previous format
	TUIssuesMap resultMap;

	for (auto& filterIssue : filterIssueMap) {
		auto issue = filterIssue.second.issue;
		std::string moduleName = issue->getModuleName();
		resultMap[moduleName].Issues.push_back(issue);
	}

	return resultMap;
}

}
}
