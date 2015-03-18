/*
 * test_implicitconversion.cpp
 *
 *  Created on: Jun 25, 2014
 *      Author: ahueck
 */

#include <modules/ImplicitConversion.h>

#include "ImplicitConversionDefinition.h"


KICKOFF_TEST(opov::module::ImplicitConversion(), CMP("2.0"), "2.0")

#define _TYPE_ "scalar"
SCENARIO("Constructor Conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule(new opov::module::ImplicitConversion());
#include "tests/ConversionMatchSet.inl"
	}
}

SCENARIO("Constructor Conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule(new opov::module::ImplicitConversion());
#include "tests/ConversionNoMatchSet.inl"
	}
}

#undef _TYPE_
#undef VARS
#undef HEADER
#define HEADER "typedef double ascalar;\n#define scalar double\n"
#define VARS "\nascalar ad = 1.0; float af = 1.0f; double as = 10.0; double bs = 1.5;\n"
#define _TYPE_ "double"
SCENARIO("Constructor Conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule(new opov::module::ImplicitConversion());
#include "tests/ConversionMatchSet.inl"
	}
}

SCENARIO("Constructor Conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule(new opov::module::ImplicitConversion());
#include "tests/ConversionNoMatchSet.inl"
	}
}
