/*
 * IssueReporter.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef ISSUEREPORTER_H_
#define ISSUEREPORTER_H_

#include "../issue/IssueHandlerStruct.h"

#include <vector>
#include <string>

namespace opov {

class IssueReporter {
public:
	virtual void addIssue(const TranslationUnitIssues& issue) = 0;
	virtual void addIssues(const TUIssuesMap& issues) = 0;
	virtual ~IssueReporter() {
	}
};

} // namespace opov

#endif /* ISSUEREPORTER_H_ */
