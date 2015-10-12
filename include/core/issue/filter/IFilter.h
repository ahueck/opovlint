#ifndef IFILTER_H
#define IFILTER_H

#include "../IssueHandlerStruct.h"
#include "FilterIssueStruct.h"
#include "../Issue.h"

namespace opov {
namespace filter {

class IFilter {
public:
    virtual IssueSet apply(const TUIssuesMap& map) = 0;
    virtual ~IFilter() {

    }
};

}
}

#endif
