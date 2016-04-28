#ifndef UNIQUE_FILTER_H
#define UNIQUE_FILTER_H

#include "IFilter.h"

namespace opov {
namespace filter {

class UniqueFilter: public IFilter {
public:
  UniqueFilter();
  virtual IssueSet apply(const TUIssuesMap& map) override;
  virtual ~UniqueFilter();
};

} // namespace filter
} // namespace opov

#endif
