/*
 * CSVReporter.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: ahueck
 */



#include <core/CSVReporter.h>
#include <core/Logger.h>
#include <core/Issue.h>
#include <sstream>

namespace opov {
CSVReporter::CSVReporter() {
	// TODO Auto-generated constructor stub

}

void CSVReporter::addIssue(const TranslationUnitIssues& issue) {
	print(issue);
}
void CSVReporter::addIssues(const TUIssuesMap& issues) {
	for(auto& unit : issues) {
		print(unit.second);
	}
}

void CSVReporter::print(const TranslationUnitIssues& issue) {
	std::stringstream csv;
	for(auto& i : issue.Issues) {
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
	// TODO Auto-generated destructor stub
}

} // namepace opov

