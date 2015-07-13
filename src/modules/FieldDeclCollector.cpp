/*
 * FieldDeclCollector.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#include <modules/FieldDeclCollector.h>

#include <core/Logger.h>
#include <core/utility/ClangUtil.h>

namespace opov {
namespace module {

FieldDeclCollector::FieldDeclCollector(const std::string& type) :
		violations(), type(type) {

}

std::vector<clang::FieldDecl*> FieldDeclCollector::extractDecl(
		clang::CXXRecordDecl* unionDecl) {
	violations.clear();
	TraverseDecl(unionDecl);
	return violations;
}

bool FieldDeclCollector::VisitFieldDecl(clang::FieldDecl* decl) {
	if (clutil::typeOf(decl) == type) {
		violations.push_back(decl);
	}
	return true;
}

FieldDeclCollector::~FieldDeclCollector() {
}

} /* namespace module */
} /* namespace opov */
