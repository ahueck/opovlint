/*
 * IssueReporter.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_ISSUEREPORTER_H
#define CORE_REPORTING_ISSUEREPORTER_H

#include "../issue/IssueHandlerStruct.h"

#include <iostream>

namespace opov {

class IssueReporter {
 protected:
  std::ostream& output;

 public:
  explicit IssueReporter(std::ostream& output = std::cout) : output(output) {
  }

  virtual void addIssues(const IssueVector&) = 0;
  virtual ~IssueReporter() = default;
};

} /* namespace opov */

#endif  // CORE_REPORTING_ISSUEREPORTER_H
