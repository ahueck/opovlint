/*
 * test_conditionalassgn.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#include <modules/ConditionalAssgnMatcher.h>
#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


#define HEADER "typedef double scalar;"
#define VARS "scalar a = 10.0; scalar b = 10.5; scalar c = 11.0; scalar d = 11.0;int ai = 0.0;int bi = 0.0;int ci = 0.0;int di = 0.0;"
#define START_CODE "\nvoid container() {\n"
#define END_CODE "\n};\n"
#define MAKE_CODE(stmt) HEADER VARS START_CODE stmt ";" END_CODE

#define COND_S "b > 0 ? c : d"
#define COND MAKE_CODE("a = " COND_S)
#define COND_SI "bi > 0 ? ci : di"
#define CONDI MAKE_CODE("ai = " COND_SI)

KICKOFF_TEST(opov::module::ConditionalAssgnMatcher, COND, COND_S)

#define _TYPE_ "scalar"
SCENARIO("Conditional assign op. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ConditionalAssgnMatcher>();
#include "tests/ConditionalAssignMatchSet.inl"
	}
}

SCENARIO("Conditional assign op. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ConditionalAssgnMatcher>();
#include "tests/ConditionalAssignNoMatchSet.inl"
	}
}

#undef VARS
#undef _TYPE_
#define _TYPE_ "double"
#define VARS "double a = 10.0; double b = 10.5; double c = 11.0; double d = 11.0;int ai = 0.0;int bi = 0.0;int ci = 0.0;int di = 0.0;"
SCENARIO("Conditional assign op. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ConditionalAssgnMatcher>();
#include "tests/ConditionalAssignMatchSet.inl"
	}
}

SCENARIO("Conditional assign op. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ConditionalAssgnMatcher>();
#include "tests/ConditionalAssignNoMatchSet.inl"
	}
}
