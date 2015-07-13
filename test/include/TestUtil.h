/*
 * TestUtil.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ahueck
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <string>
#include <locale>

#define DS_STRINGIFY_(A) # A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)

#define REMOVE_WS(_CODE_)\
        _CODE_.erase(\
            std::remove_if(_CODE_.begin(), _CODE_.end(),\
                    [](char c) -> bool\
                    {\
                        return std::isspace<char>(c, std::locale::classic());\
                    })\
            , _CODE_.end());

static inline std::string trim_str(std::string code) {
    REMOVE_WS(code)
    return code;
}

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
                    std::string code = the_issue->getCode();\
					REQUIRE(trim_str(the_issue->getCode()) == trim_str(_CODE_MACRO_RESULT_));\
				}\
				AND_WHEN("The code again.") {\
					app.executeOnCode(code);\
					auto reporter = app.getReporter();\
					THEN("The same, single issue is raised.") {\
						REQUIRE(reporter->issues.size() == 1);\
						AND_THEN("The issue resolved to the same code again.") {\
							auto the_issue = reporter->issues[0];\
							REQUIRE(trim_str(the_issue->getCode()) == trim_str(_CODE_MACRO_RESULT_));\
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
			REQUIRE(trim_str(the_issue->getCode()) == trim_str(_RESULT_));\
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
