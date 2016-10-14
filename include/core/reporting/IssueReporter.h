/*
 * IssueReporter.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_ISSUEREPORTER_H
#define CORE_REPORTING_ISSUEREPORTER_H

#include "../issue/IssueHandlerStruct.h"

namespace opov {

class IssueReporter {
 public:
  virtual void addIssues(const IssueVector&) = 0;
  virtual ~IssueReporter() = default;
};

} /* namespace opov */

#endif  // CORE_REPORTING_ISSUEREPORTER_H
