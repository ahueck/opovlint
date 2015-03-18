/*
 * MockReporter.h
 *
 *  Created on: May 28, 2014
 *      Author: ahueck
 */

#ifndef MOCKREPORTER_H_
#define MOCKREPORTER_H_

#include <core/IssueReporter.h>
#include <core/Logger.h>
#include <core/IssueHandlerStruct.h>

#include <memory>

namespace opov {
namespace test {

class MockReporter: public opov::IssueReporter {
public:
	std::vector<std::shared_ptr<Issue>> issues;
	std::string file;

	MockReporter() {

	}

	void addIssue(const TranslationUnitIssues& issue) {
		LOG_DEBUG("Not supposed to be called!");
	}

	void addIssues(const TUIssuesMap& issues) {
		//FIXME assert that only one issue is produced for the code snippets
		//auto& i = (*issues.find("input.cc")).getValue();
		//this->issues = std::move(i.Issues);
		//this->file = i.MainSourceFile;
		this->issues.clear();
		for(auto& unit : issues) {
			file = unit.second.MainSourceFile;
			for(auto i : unit.second.Issues) {
                //Issue* leak = new Issue();
                //leak->setCode(i->getCode());
				this->issues.push_back(i);
			}
		}
	}

	virtual ~MockReporter() {

	}
};

}
}
#endif /* MOCKREPORTER_H_ */
