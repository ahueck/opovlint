/*
 * test_system.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: ahueck
 */

#include <TestApp.h>

#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/reporting/FormattedReporter.h>
#include <core/issue/IssueHandlerStruct.h>
#include <core/module/ASTMatcherModule.h>
#include <core/configuration/JSONConfiguration.h>
#include <modules/ExplicitCast.h>

#include <string>
#include <memory>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("TransformationHandle", "[thandle]") {
	opov::test::TestApp app(conf);
	app.init();
	app.addModule<opov::module::ExplicitCast>();
	const std::string code = "typedef double scalar; scalar a = 10.0; void container() { int res = 0.0; res = static_cast<double>(a); }";
    SECTION("No transformation state") {
		auto handle = app.getHandler();
		REQUIRE(handle->getIncludeDirectives() == nullptr);
		REQUIRE(handle->getAllReplacements().size() == 0);
    }
    SECTION("Transformation on empty code state") {
		auto handle = app.getHandler();
		app.executeOnCode("");
		REQUIRE(handle->getIncludeDirectives() != nullptr);
		REQUIRE(handle->getAllReplacements().size() == 0);
    }
    SECTION("Transformation on code state") {
		auto handle = app.getHandler();
		app.executeOnCode(code);
		REQUIRE(handle->getIncludeDirectives() != nullptr);
		//REQUIRE(handle->getAllReplacements().size() == 1);
    }
}

