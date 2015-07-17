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
  virtual void addIssue(const TranslationUnitIssues& issue) override;
  virtual void addIssues(const TUIssuesMap& issues) override;
  virtual ~ConsoleReporter();

 private:
  void print(const TranslationUnitIssues& issue);
};

}  // namespace opov

#endif /* CONSOLEREPORTER_H_ */
