/*
 * IssueReporter.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_ISSUEREPORTER_H
#define CORE_REPORTING_ISSUEREPORTER_H

#include "../issue/IssueHandlerStruct.h"
#include "../issue/filter/FilterIssueStruct.h"

#include <vector>
#include <string>

namespace opov {

class IssueReporter {
 public:
  virtual void addIssue(const TranslationUnitIssues& issue) = 0;
  virtual void addIssues(const TUIssuesMap& issues) = 0;
  virtual void addIssues(const filter::IssueSet& issues) = 0;
  virtual ~IssueReporter() = default;
};

} /* namespace opov */

#endif // CORE_REPORTING_ISSUEREPORTER_H
