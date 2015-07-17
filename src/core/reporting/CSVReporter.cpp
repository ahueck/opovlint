/*
 * CSVReporter.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ahueck
 */

#include <core/reporting/CSVReporter.h>
#include <core/issue/Issue.h>
#include <core/logging/Logger.h>

#include <sstream>

namespace opov {

CSVReporter::CSVReporter() {
}

void CSVReporter::addIssue(const TranslationUnitIssues& issue) {
  print(issue);
}
void CSVReporter::addIssues(const TUIssuesMap& issues) {
  for (auto& unit : issues) {
    print(unit.second);
  }
}

void CSVReporter::print(const TranslationUnitIssues& issue) {
  std::stringstream csv;
  for (auto& i : issue.Issues) {
    csv << issue.MainSourceFile << ";";
    csv << i->getModuleName() << ";";
    csv << i->getFile() << ";";
    csv << i->getCode() << ";";
    csv << i->getLineStart() << ";" << i->getLineEnd() << ";" << i->getColumnStart() << ";" << i->getColumnEnd();
    LOG_MSG(csv.str());
    csv.str("");
    csv.clear();
  }
}

CSVReporter::~CSVReporter() {
}

} /* namespace opov */
