/*
 * test_implicitcond.cpp
 *
 *  Created on: May 29, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConditionMatcher.h>

#include "ImplicitConditionDefinition.h"

KICKOFF_TEST(opov::module::ImplicitConditionMatcher, IF("a"), "a")

#define _TYPE_ "scalar"
#define _NTYPE_ "double"
SCENARIO("Implicit conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ImplicitConditionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ImplicitConditionMatcher>();
#include "tests/ImplicitConditionMatchSet.inl"
	}
}

SCENARIO("Implicit conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ImplicitConditionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ImplicitConditionMatcher>();
#include "tests/ImplicitConditionNoMatchSet.inl"
	}
}

#undef _TYPE_
#undef _NTYPE_
#undef VARS
#define VARS "double a = 1; double f = 10; scalar b = 0.5; scalar bb = 1.0;"
#define _TYPE_ "double"
#define _NTYPE_ "scalar"
SCENARIO("Implicit conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ImplicitConditionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ImplicitConditionMatcher>();
#include "tests/ImplicitConditionMatchSet.inl"
	}
}

SCENARIO("Implicit conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ImplicitConditionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ImplicitConditionMatcher>();
#include "tests/ImplicitConditionNoMatchSet.inl"
	}
}
