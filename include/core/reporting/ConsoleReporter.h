/*
 * ConsoleReporter.h
 *
 *  Created on: May 18, 2014
 *      Author: zeitgeist
 */

#ifndef CONSOLEREPORTER_H_
#define CONSOLEREPORTER_H_

#include "IssueReporter.h"

//#include <string>

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

#endif /* CONSOLEREPORTER_H_ */
