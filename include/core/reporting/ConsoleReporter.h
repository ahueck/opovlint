/*
 * ConsoleReporter.h
 *
 *  Created on: May 18, 2014
 *      Author: zeitgeist
 */

#ifndef CORE_REPORTING_CONSOLEREPORTER_H
#define CORE_REPORTING_CONSOLEREPORTER_H

#include "IssueReporter.h"

namespace opov {

class ConsoleReporter : public opov::IssueReporter {
 public:
  ConsoleReporter();
  void addIssue(const TranslationUnitIssues &issue) override;
  void addIssues(const TUIssuesMap &issues) override;
  void addIssues(const filter::IssueSet &issues) override;
  ~ConsoleReporter() override;

 private:
  void print(const TranslationUnitIssues& issue);
};

} /* namespace opov */

#endif // CORE_REPORTING_CONSOLEREPORTER_H
