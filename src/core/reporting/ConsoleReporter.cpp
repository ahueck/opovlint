/*
 * ConsoleReporter.cpp
 *
 *  Created on: May 18, 2014
 *      Author: ahueck
 */

#include <core/reporting/ConsoleReporter.h>
#include <core/issue/Issue.h>
#include <core/logging/Logger.h>
#include <core/utility/Util.h>

namespace opov {

ConsoleReporter::ConsoleReporter() {
}

void ConsoleReporter::addIssue(const TranslationUnitIssues& issue) {
  print(issue);
}
void ConsoleReporter::addIssues(const TUIssuesMap& issues) {
  for (auto& unit : issues) {
    print(unit.second);
  }
}

void ConsoleReporter::addIssues(const filter::IssueSet& issues) {
  LOG_ERROR("Not yet implemented!");
}

void ConsoleReporter::print(const TranslationUnitIssues& issue) {
  std::string module = "";
  LOG_MSG(issue.MainSourceFile << ":");
  for (auto& i : issue.Issues) {
    if (module != i->getModuleName()) {
      module = i->getModuleName();
      LOG_MSG("\t" << module);  // indent
      LOG_MSG("\t\tModule description: " << i->getModuleDescription());
    }
    const std::string&& violating_file = i->getFile();
    LOG_MSG("\t\t\tFile path: '" << violating_file << "'");  // violating_file may be external header
    LOG_MSG("\t\t\tLocation: "
            << "Line (S/E): " << i->getLineStart() << "/" << i->getLineEnd()
            << ". Column (S/E): " << i->getColumnStart() << "/" << i->getColumnEnd());
    LOG_MSG("\t\t\tSource: '" << i->getCode() << "'");
    LOG_MSG("\t\t\tDescription: '" << i->getDescription() << "'");
    LOG_MSG("\t\t\t------------");
  }
}

ConsoleReporter::~ConsoleReporter() = default;

} /* namespace opov */
