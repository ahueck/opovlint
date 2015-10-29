/*
 * CSVReporter.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ahueck
 */

#include <core/reporting/CSVReporter.h>
#include <core/issue/Issue.h>
#include <core/logging/Logger.h>
#include <core/utility/Util.h>

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

void CSVReporter::addIssues(const filter::IssueSet& set) {
  std::stringstream csv;
  csv << "Module Name;File Path;Code;Line Start;Line End;Column Start;Column End;Files\n";
  for (auto& ifiltered : set) {
    auto i = ifiltered.second.issue;
    csv << i->getModuleName() << ";";
    csv << i->getFile() << ";";
    csv << util::trim_rep(util::remove_nl(i->getCode())) << ";";
    csv << i->getLineStart() << ";" << i->getLineEnd() << ";" << i->getColumnStart() << ";" << i->getColumnEnd() << ";";
    csv << "+";
    for (auto& tunit : ifiltered.second.tunits) {
      csv << tunit << "+";
    }
    LOG_MSG(csv.str());
    csv.str("");
    csv.clear();
  }
}

void CSVReporter::print(const TranslationUnitIssues& issue) {
  std::stringstream csv;
  csv << "Main source;Module Name;File Path;Code;Line Start;Line End;Column Start;Column End\n";
  for (auto& i : issue.Issues) {
    csv << issue.MainSourceFile << ";";
    csv << i->getModuleName() << ";";
    csv << i->getFile() << ";";
    csv << util::trim_rep(util::remove_nl(i->getCode())) << ";";
    csv << i->getLineStart() << ";" << i->getLineEnd() << ";" << i->getColumnStart() << ";" << i->getColumnEnd();
    LOG_MSG(csv.str());
    csv.str("");
    csv.clear();
  }
}

CSVReporter::~CSVReporter() {
}

} /* namespace opov */
