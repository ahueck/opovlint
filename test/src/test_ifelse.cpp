/*
 * test_ifelse.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: ahueck
 */




#include <modules/IfElseAssign.h>
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
#define MAKE_CODE(stmt) HEADER VARS START_CODE stmt END_CODE

#define IF(A, B) "if(a == 0.) { " A " } else { " B " }"
#define IF_E(A, B) "if(a == 0.) { " A " } else { " B " }"


KICKOFF_TEST(opov::module::IfElseAssign(), MAKE_CODE(IF("a = b;", "a = c;")), IF("a = b;", "a = c;"))

#define _TYPE_ "scalar"
SCENARIO("Conditional assign op. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
  GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
    opov::test::TestApp app(conf);
    app.init();
    app.addModule(new opov::module::IfElseAssign());
#include "tests/IfElseMatchSet.inl"
  }
}

SCENARIO("Conditional assign op. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
  GIVEN("The 'ConditionalAssgnMatcher' module with type: " _TYPE_) {
    opov::test::TestApp app(conf);
    app.init();
    app.addModule(new opov::module::IfElseAssign());
#include "tests/IfElseNoMatchSet.inl"
  }
}
