#ifndef CORE_ISSUE_FILTER_FILTERISSUESTRUCT_H
#define CORE_ISSUE_FILTER_FILTERISSUESTRUCT_H

#include "../Issue.h"
#include <core/utility/Util.h>

#include <map>
#include <memory>
#include <vector>

namespace opov {
namespace filter {

using SingleIssue =  struct { std::shared_ptr<Issue> issue; std::vector<std::string> tunit_occurences; };

} /* namespace filter */
} /* namespace opov */

#endif
