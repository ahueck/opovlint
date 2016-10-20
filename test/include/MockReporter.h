/*
 * MockReporter.h
 *
 *  Created on: May 28, 2014
 *      Author: ahueck
 */

#ifndef MOCKREPORTER_H_
#define MOCKREPORTER_H_

#include <core/reporting/IssueReporter.h>
#include <core/logging/Logger.h>
#include <core/issue/IssueHandlerStruct.h>

#include <memory>

namespace opov {
namespace test {

class MockReporter: public opov::IssueReporter {
public:
	std::vector<std::shared_ptr<Issue>> issues;
	std::string file;

	MockReporter() = default;

	virtual void addIssues(const IssueVector& issues) override {
	  //FIXME assert that only one issue is produced for the code snippets
	  this->issues.clear();
	  for (auto& issue : issues) {
	    file = issue.tunit_occurences.front();
	    this->issues.push_back(issue.issue);
	  }
	}

	virtual ~MockReporter() = default;
};

}
}
#endif /* MOCKREPORTER_H_ */
