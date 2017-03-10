/*
 * test_explicitcast.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitCast.h>
#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


#define HEADER "typedef double scalar;\n"
#define VARS "scalar a = 10.0; scalar aa = 10.5; scalar ab = 11.0; scalar* ptr = &a;\n"
#define START_CODE "void container() {\nint res = 0.0;\n"
#define END_CODE "\n};\n"
#define MAKE_CODE(stmt) HEADER VARS START_CODE stmt ";" END_CODE

#define SCAST_T(TYPE, CODE) "static_cast<" TYPE ">(" CODE ")"
#define SCAST(CODE) MAKE_CODE("res = " SCAST_T("int", CODE))
#define SCAST_SCALAR(CODE) MAKE_CODE("res = " SCAST_T("scalar", CODE))
#define SCAST_TYPE(TYPE, CODE) MAKE_CODE(TYPE " cres = " SCAST_T(TYPE, CODE))
#define SCAST_S(CODE) SCAST_T("int", CODE)

KICKOFF_TEST(opov::module::ExplicitCast, SCAST("a"), SCAST_S("a"))

#define _TYPE_ "scalar"
SCENARIO("Explicit casts. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ExplicitCast' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ExplicitCast>();
#include "tests/ExplicitCastMatchSet.inl"
	}
}
SCENARIO("Explicit casts. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ExplicitCast' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::ExplicitCast>();
#include "tests/ExplicitCastNoMatchSet.inl"
	}
}

SCENARIO("Explicit casts with scalars/integers. Module looks for type double and no match is produced.", "[double_nmatch]") {
	GIVEN("The 'ExplicitCast' module with type: double") {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ExplicitCast>();

		SIMPLE_TEST0("A static cast."
				, SCAST("a"));
		SIMPLE_TEST0("A static cast of a binary op."
				, SCAST("a*ab"));
		SIMPLE_TEST0("A static cast of a nested binary op."
				, SCAST("a*ab*aa"));
		SIMPLE_TEST0("A static cast of a casted variable."
				, SCAST(SCAST_T(_TYPE_, "res")));
		SIMPLE_TEST0("A static cast of a binary op. with a cast."
				, SCAST("res*" SCAST_T(_TYPE_, "res")));
		SIMPLE_TEST0("A static cast of a binary op. with constant."
				, SCAST("a*1"));
		SIMPLE_TEST0("A static cast of a binary op. with paren expression."
				, SCAST("a*(res*2)"));
		SIMPLE_TEST0("A static cast of a paren expression with binary op."
				, SCAST("(a*2)"));
		SIMPLE_TEST0("A static cast of a binary op with paren expression."
				, SCAST("res*(a*2)"));
		SIMPLE_TEST0("A static cast of a nested cast expression."
				, SCAST(SCAST_S("a")));
		SIMPLE_TEST0("A static cast of a nested cast expression of a binary op."
				, SCAST(SCAST_S("res*(a*2)")));
		SIMPLE_TEST0("A static cast with parens."
				, SCAST("((a))"));
		SIMPLE_TEST0("A static cast of a binary op. with a cast inside parens."
				, SCAST("res*((" SCAST_T(_TYPE_, "res") "))"));
		// mixed int/bool/scalar casts
		SIMPLE_TEST0("A static cast of an int."
				, SCAST("res"));
		SIMPLE_TEST0("A static cast to scalar."
				, SCAST_SCALAR("a"));
		SIMPLE_TEST0("A static cast of an int."
				, SCAST_SCALAR("res"));
		SIMPLE_TEST0("A static cast to scalar of a binary op."
				, SCAST_SCALAR("a*res"));
		SIMPLE_TEST0("A static cast of an unary."
				, SCAST("!a"));
		SIMPLE_TEST0("A static cast of a nested unary."
				, SCAST("!!a"));
		SIMPLE_TEST0("A static cast of a nested unary of a binary."
				, SCAST("!!(a*a)"));
	}
}

#undef _TYPE_
#undef VARS
#define _TYPE_ "double"
#define VARS "double a = 10.0; double aa = 10.5; double ab = 11.0; double* ptr = &a;\n"
SCENARIO("Explicit casts. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'ExplicitCast' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ExplicitCast>();
#include "tests/ExplicitCastMatchSet.inl"
	}
}
SCENARIO("Explicit casts. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'ExplicitCast' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::ExplicitCast>();
#include "tests/ExplicitCastNoMatchSet.inl"
	}
}
