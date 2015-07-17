/*
 * IssueReport.h
 *
 *  Created on: May 14, 2014
 *      Author: ahueck
 */

#ifndef ISSUE_H_
#define ISSUE_H_

#include "map/PropertyMap.h"

namespace opov {

class Issue {
 private:
  property_map _properties;

 public:
  Issue() {
  }
  const property_map& properties() {
    return _properties;
  }
  int IssueProperty(LineStart);
  int IssueProperty(LineEnd);
  int IssueProperty(ColumnStart);
  int IssueProperty(ColumnEnd);
  std::string IssueProperty(File);
  std::string IssueProperty(Description);
  std::string IssueProperty(Code);
  std::string IssueProperty(ModuleName);
  std::string IssueProperty(ModuleDescription);
};

}  // namespace opov

#endif /* ISSUE_H_ */
