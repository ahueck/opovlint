/*
 * TestUtil.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ahueck
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#define DS_STRINGIFY_(A) # A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)

#define KICKOFF_TEST(_MODULE_, _CODE_MACRO_, _CODE_MACRO_RESULT_)\
SCENARIO("Test the system (state) with " DS_STRINGIFY(_MODULE_) " executed 2 times against the same code.", "[kickoff]") {\
	GIVEN("The static analyzer with the '" DS_STRINGIFY(_MODULE_) "' module.") {\
		opov::test::TestApp app;\
		app.init();\
		app.addModule(new _MODULE_);\
		WHEN("A simple code example.") {\
			std::string code =_CODE_MACRO_;\
			app.executeOnCode(code);\
			auto reporter = app.getReporter();\
			THEN("One issue is raised.") {\
				REQUIRE(reporter->issues.size() == 1);\
				AND_THEN("The issues code matches as expected.") {\
					auto the_issue = reporter->issues[0];\
					REQUIRE(the_issue->getCode() == _CODE_MACRO_RESULT_);\
				}\
				AND_WHEN("The code again.") {\
					app.executeOnCode(code);\
					auto reporter = app.getReporter();\
					THEN("The same, single issue is raised.") {\
						REQUIRE(reporter->issues.size() == 1);\
						AND_THEN("The issue resolved to the same code again.") {\
							auto the_issue = reporter->issues[0];\
							REQUIRE(the_issue->getCode() == _CODE_MACRO_RESULT_);\
						}\
					}\
				}\
			}\
		}\
	}\
}


#define SIMPLE_TEST1(_WHEN_, _CODE_, _RESULT_)\
WHEN(_WHEN_) {\
	app.executeOnCode(_CODE_);\
	auto reporter = app.getReporter();\
	THEN("One issue is raised.") {\
		REQUIRE(reporter->issues.size() == 1);\
		AND_THEN("The issues code is the string: " DS_STRINGIFY(_RESULT_)) {\
			auto the_issue = reporter->issues[0];\
			REQUIRE(the_issue->getCode() == _RESULT_);\
		}\
	}\
}

#define SIMPLE_TEST0(_WHEN_, _CODE_)\
WHEN(_WHEN_) {\
	app.executeOnCode(_CODE_);\
	auto reporter = app.getReporter();\
	THEN("Zero issues are raised.") {\
		if(reporter->issues.size() != 0) {\
			auto the_issue = reporter->issues[0];\
			REQUIRE(the_issue->getCode() == "");\
		}\
		REQUIRE(reporter->issues.size() == 0);\
	}\
}



#endif /* TESTUTIL_H_ */
