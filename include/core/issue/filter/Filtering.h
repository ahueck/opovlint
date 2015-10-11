#ifndef FILTERING_H
#define FILTERING_H

#include "../IssueHandlerStruct.h"

namespace opov {
namespace filter {

class IFilter;

class Filtering {
public:
	Filtering(IFilter* mainFilter);
	~Filtering();

	TUIssuesMap filter(const TUIssuesMap& unfilteredMap);
private:
	IFilter* mainFilter;
};

}
}

#endif
