/*
 * IssueReporter.cpp
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#include <core/IssueReporter.h>
#include <core/Issue.h>

namespace opov {

IssueReporter::IssueReporter() {
	// TODO Auto-generated constructor stub

}

IssueReporter::~IssueReporter() {
	/*
	if (issues.size() != 0) {
		std::for_each(issues.begin(), issues.end(), [] (Issue* i) { delete i; } );
		issues.clear();
	}
	*/
}

} // namespace opov
