#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/IssueHandlerStruct.h>

#include <map>

namespace opov {
namespace filter {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

FilterIssueMap UniqueFilter::apply(const FilterIssueMap& map) {
	std::map<int, int> duplicates;

	FilterIssueMap filteredMap;

	for (auto& filterIssue : map) {
		int hash = filterIssue.second.issue->hash();
		if (duplicates.find(hash) == duplicates.end()) {
			filteredMap[filterIssue.first] = filterIssue.second;
			duplicates[hash] = 0;
		} else {
			duplicates[hash]++;
		}
	}

	// TODO: What happens to the meta data?
	return filteredMap;

}

}
}
