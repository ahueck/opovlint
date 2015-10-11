#ifndef UNIQUE_FILTER_H
#define UNIQUE_FILTER_H

#include "IFilter.h"

namespace opov {
namespace filter {

class UniqueFilter: public IFilter {
public:
	UniqueFilter();
	virtual ~UniqueFilter();

    virtual FilterIssueMap apply(const FilterIssueMap& map) override;
};

}
}

#endif
