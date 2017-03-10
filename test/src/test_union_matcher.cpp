/*
 * test_union_matcher.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#include <modules/UnionMatcher.h>
#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


#define HEADER "typedef double scalar;\n"
#define VARS ""
#define START_CODE "class container {\n"
#define END_CODE "\n};\n"

#define MAKE_CODE(stmt) HEADER VARS START_CODE stmt ";" END_CODE

#define NUNION_S(STR) "union named_union {\n" STR "\n}"
#define UNION_S(STR) "union standard_union {\n" STR "\n}"
#define AUNION_S(STR) "union {\n" STR "\n}"
#define AUNION(STR) MAKE_CODE(AUNION_S(STR))
#define UNION(STR) MAKE_CODE(UNION_S(STR))
#define NUNION(STR) MAKE_CODE(NUNION_S(STR) " nunion")

KICKOFF_TEST(opov::module::UnionMatcher, UNION("scalar a;"), UNION_S("scalar a;"))

#define _TYPE_ "scalar"
#define _NTYPE_ "double"
SCENARIO("Unions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'UnionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::UnionMatcher>();
#include "tests/UnionMatchSet.inl"
	}
}

SCENARIO("Unions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'UnionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::UnionMatcher>();
#include "tests/UnionNoMatchSet.inl"
	}
}

#undef _TYPE_
#undef _NTYPE_
#define _TYPE_ "double"
#define _NTYPE_ "scalar"
SCENARIO("Unions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'UnionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::UnionMatcher>();
#include "tests/UnionMatchSet.inl"
	}
}
SCENARIO("Unions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'UnionMatcher' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::UnionMatcher>();
#include "tests/UnionNoMatchSet.inl"
	}
}
