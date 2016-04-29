/*
 * test_allimplicitconversion.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: ahueck
 */

#include <modules/AllImplicitConversion.h>

#include "ImplicitConversionDefinition.h"

KICKOFF_TEST(opov::module::AllImplicitConversion, CMP("2.0"), "2.")

SCENARIO("Constructor Conversions. Module produces one match each time.", "[scalar_match]") {
	GIVEN("The 'AllImplicitConversion' module.") {
		opov::test::TestApp app;
		app.init();
		app.addModule<opov::module::AllImplicitConversion>();

		SIMPLE_TEST1("A comparison with a constant casted to scalar."
					, CMP("scalar(2.)")
					, "scalar(2.)");
		SIMPLE_TEST1("A comparison with a float casted to scalar."
					, CMP("scalar(af)")
					, "scalar(af)");
		SIMPLE_TEST1("A comparison with a binary op. casted to scalar."
					, CMP("scalar(af*ad)")
					, "scalar(af*ad)");
		SIMPLE_TEST1("A comparison with a scalar."
					, CMP("as")
					, "as");
		SIMPLE_TEST1("A comparison with a binary op. of scalars."
					, CMP("as*bs")
					, "as*bs");
		SIMPLE_TEST1("A comparison with a nested binary op. of scalars."
					, CMP("as*as*as/as")
					, "as*as*as/as");
		SIMPLE_TEST1("A comparison with a nested binary op. of scalars inside parens."
					, CMP("((as*(as*as)/as))")
					, "((as*(as*as)/as))");
		SIMPLE_TEST1("A comparison with a nested binary op. of scalars and doubles inside parens."
					, CMP("((ad*(ad*as)/ad))")
					, "((ad*(ad*as)/ad))");
	}
}

#define _TYPE_ "scalar"
SCENARIO("Constructor Conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule<opov::module::AllImplicitConversion>();
#include "tests/ConversionMatchSet.inl"
	}
}
/*
SCENARIO("Constructor Conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf);
		app.init();
		app.addModule(new opov::module::AllImplicitConversion());
#include "tests/ConversionNoMatchSet.inl"
	}
}
*/
#undef _TYPE_
#define _TYPE_ "double"
SCENARIO("Constructor Conversions. Module produces one match for type " _TYPE_, "[" _TYPE_ "_match]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule<opov::module::AllImplicitConversion>();
#include "tests/ConversionMatchSet.inl"
	}
}
/*
SCENARIO("Constructor Conversions. Module produces no match for type " _TYPE_, "[" _TYPE_ "_nmatch]") {
	GIVEN("The 'AllImplicitConversion' module with type: " _TYPE_) {
		opov::test::TestApp app(conf_double);
		app.init();
		app.addModule(new opov::module::AllImplicitConversion());
#include "tests/ConversionNoMatchSet.inl"
	}
}
*/
