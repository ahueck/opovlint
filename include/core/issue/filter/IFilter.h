#ifndef IFILTER_H
#define IFILTER_H

#include "FilterIssueStruct.h"
#include "../Issue.h"

namespace opov {
namespace filter {

class IFilter {
public:
    virtual FilterIssueMap apply(const FilterIssueMap& map) = 0;
    virtual ~IFilter() {

    }
};

}
}

#endif
