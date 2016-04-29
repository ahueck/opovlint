#ifndef UNIQUE_FILTER_H
#define UNIQUE_FILTER_H

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
