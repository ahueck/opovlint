/*
 * test_globaltype.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: ahueck
 */

#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>
#include <modules/GlobalScope.h>

#include <core/logging/Logger.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#define PRAGMAS "#pragma clang diagnostic ignored \"-Wunused-value\"\n\n"
#define HEADER "typedef double scalar;\n"
#define GLOBAL \
"class X;\n\
int a = 1;\n\
scalar b = 1.0;\n\
double c = 2.0;\n\
void f(const X& x);\n\
class X {\n\
public:\n\
	friend void f(const X& x) {  }\n\
};\n\
void g(scalar a);\
void h(double b);\n"

#define NS \
"namespace ns {\n\
	void f(const X& x);\n\
  void f();\n\
	void call() {\n\
	::f(X());\n\
    ns::f(X());\n\
    f();\n\
    ::a;\n\
    ::b;\n"

#define NS_END \
  "}\n\
}"

#define MAKE_CODE(stmt) PRAGMAS HEADER GLOBAL NS stmt NS_END

#define CALL(ARG)  MAKE_CODE("::g(" ARG ");\n")
#define CALLR(ARG) "::g(" ARG ")"
#define CALLH(ARG)  MAKE_CODE("::h(" ARG ");\n")
#define CALLHR(ARG) "::h(" ARG ")"

KICKOFF_TEST(opov::module::GlobalScope, CALL("b"), CALLR("b"))


SCENARIO("Global scope function calls with scalars. Module looks for type scalar and one match is produced.", "[scalar_match]") {
	GIVEN("The 'GlobalScope' module with type: scalar") {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule(new opov::module::GlobalScope());

		SIMPLE_TEST1("A call with scalar argument."
				, CALL("b"), CALLR("b"));
		SIMPLE_TEST1("A call with binary expression."
				, CALL("b*b"), CALLR("b*b"));
		SIMPLE_TEST1("A simple call with int argument."
				, CALL("a"), CALLR("a"));
		SIMPLE_TEST1("A simple call with double argument."
				, CALL("c"), CALLR("c"));
    SIMPLE_TEST1("A simple call with a (cast) scalar argument."
        , CALL("scalar(1)"), CALLR("scalar(1)"));
    SIMPLE_TEST1("A call with scalar argument using namespace qualifier."
            , CALL("::b"), CALLR("::b"));
    SIMPLE_TEST1("A call with double argument using namespace qualifier."
            , CALL("::a"), CALLR("::a"));
    SIMPLE_TEST1("A simple call with scalar argument."
        , CALLH("b"), CALLHR("b"));
	}
}

SCENARIO("Global scope function calls with scalars. Module looks for type scalar and no match is produced.", "[scalar_nmatch]") {
	GIVEN("The 'GlobalScope' module with type: scalar") {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule(new opov::module::GlobalScope());

		SIMPLE_TEST0("A simple call with int argument."
				, CALLH("a"));
		SIMPLE_TEST0("A simple call with double argument."
				, CALLH("c"));
	}
}

