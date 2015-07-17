/*
 * ImplicitConditionDefinition.h
 *
 *  Created on: Jul 23, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONDITIONDEFINITION_H_
#define IMPLICITCONDITIONDEFINITION_H_

#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


#define HEADER "typedef double scalar;\n"
#define VARS "scalar a = 1; scalar f = 10; double b = 0.5; double bb = 1.0;\n"
#define START_CODE "void simple_test() {\n"
#define END_CODE "\n}\n"

#define MAKE_CODE(stmt) HEADER VARS START_CODE stmt END_CODE

#define IF(STR) MAKE_CODE("if(" STR ") {}")
#define FOR(STR) MAKE_CODE("for(;" STR ";) {}")
#define WHILE(STR) MAKE_CODE("while(" STR ") {}")
#define DO(STR) MAKE_CODE("do { } while(" STR ");")
#define COND(STR) MAKE_CODE("bb = " STR " ? b : bb;")


#endif /* IMPLICITCONDITIONDEFINITION_H_ */
