/*
 * ImplicitConversionDefinition.h
 *
 *  Created on: Jul 23, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONVERSIONDEFINITION_H_
#define IMPLICITCONVERSIONDEFINITION_H_

#include <core/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


#define PRAGMAS "#pragma clang diagnostic ignored \"-Wunused-comparison\"\n\n"
#define HEADER "typedef double scalar;\n"
#define VARS "\ndouble ad = 1.0; float af = 1.0f; scalar as = 10.0; scalar bs = 1.5;\n"
#define CLASS_CODE "\
class versionNumber {\n\
	scalar versionNumber_;\n\
    int index_;\n\
public:\n\
	versionNumber(const scalar num)\n\
	: versionNumber_(num),\n\
		index_(1)\n\
	{}\n\
	versionNumber(const char* a, const scalar num=10.0f)\n\
	: versionNumber_(num),\n\
		index_(1)\n\
	{}\n\
	bool operator==(const versionNumber& vn) {\n\
		return index_ == vn.index_;\n\
	}\n\
	versionNumber operator*(const versionNumber& vn) {\n\
		return versionNumber(versionNumber_*vn.versionNumber_);\n\
	}\n\
};\n"
#define START_CODE "void container() {\nversionNumber vn(1.0);\n"
#define END_CODE "\n};\n"
#define MAKE_CODE(stmt) PRAGMAS HEADER VARS CLASS_CODE START_CODE stmt ";" END_CODE

#define CMP(STR) MAKE_CODE("vn == " STR)

#endif /* IMPLICITCONVERSIONDEFINITION_H_ */
