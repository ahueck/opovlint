#ifndef CORE_ISSUE_FILTER_IFILTER_H
#define CORE_ISSUE_FILTER_IFILTER_H

#include "../IssueHandlerStruct.h"
#include "FilterIssueStruct.h"
#include "../Issue.h"

namespace opov {
namespace filter {

class IFilter {
public:
    virtual IssueSet apply(const TUIssuesMap& map) = 0;
    virtual ~IFilter() = default;
};

} /* namespace filter */
} /* namespace opov */

#endif
