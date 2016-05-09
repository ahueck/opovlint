/*
 * test_explicitconstructor.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#include <modules/ExplicitConstructor.h>
#include <core/issue/Issue.h>

#include <MockReporter.h>
#include <TestApp.h>
#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


#define CTOR "\
versionNumber(const scalar num)\n\
: versionNumber_(num)\n\
{}"

#define CTOR_T "\
versionNumber<T>(const T num)\n\
: versionNumber_(num)\n\
{}"

#define CLASS_CODE "typedef double scalar;\n\
class versionNumber {\n\
	scalar versionNumber_;\n\
public:\n"

#define CLASS_CODE_T "typedef double scalar;\n\
template<typename T>\
class versionNumber {\n\
	T versionNumber_;\n\
public:\n"

#define END_CLASS "\n};\n"

#define CODE CLASS_CODE CTOR END_CLASS
#define CODET CLASS_CODE_T CTOR_T END_CLASS


KICKOFF_TEST(opov::module::ExplicitConstructor, CODE, CTOR)

SCENARIO("Test with various constructor configurations, resulting in a single match each time", "[mixed_match]") {
	GIVEN("The static analyzer with the 'ExplicitConstructor' module") {
		// Config file sets the search for templates to true
		opov::test::TestApp app;
		app.init();
		app.addModule<opov::module::ExplicitConstructor>();
#include "tests/ExplicitConstructorMatchSet.inl"
	}
}

SCENARIO("Test with various template constructor configurations, resulting in no match each time", "[template_no_match]") {
	GIVEN("The static analyzer with the 'ExplicitCast' module") {
		opov::test::TestApp app("test/data/explctor_conf.json");
		app.init();
		app.addModule<opov::module::ExplicitConstructor>();
#include "tests/ExplicitConstructorNoMatchSet.inl"
	}
}
