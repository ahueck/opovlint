#ifndef CORE_ISSUE_FILTER_UNIQUEFILTER_H
#define CORE_ISSUE_FILTER_UNIQUEFILTER_H

#include "IFilter.h"

namespace opov {
namespace filter {

class UniqueFilter: public IFilter {
public:
  UniqueFilter();
  IssueSet apply(const TUIssuesMap &map) override;
  ~UniqueFilter() override;
};

} /* namespace filter */
} /* namespace opov */

#endif
