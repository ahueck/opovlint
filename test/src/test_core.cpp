/*
 * test_core.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: ahueck
 */



#include <core/configuration/JSONConfiguration.h>
#include <core/issue/IssueHandlerStruct.h>
#include <core/module/ASTMatcherModule.h>
#include <core/reporting/FormattedReporter.h>
#include <core/reporting/ProgressMonitor.h>
#include <core/utility/Util.h>

#include <string>
#include <memory>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Util", "[util]") {
  using namespace opov::util;

  SECTION("Glob2Regex - No Change") {
    std::string in = "abc";
    auto out = glob2regex(in);
    REQUIRE("^abc$" == out);
  }

  SECTION("Glob2Regex - ?") {
    std::string in = "abc?";
    const auto out = glob2regex(in);
    REQUIRE("^abc.$" == out);
    REQUIRE(regex_matches(out, "abcd"));
    REQUIRE_FALSE(regex_matches(out, "abcdd"));
  }

  SECTION("Glob2Regex - {}") {
    std::string in = "abc.{txt,pdf}";
    const auto out = glob2regex(in);
    REQUIRE("^abc\\.(txt|pdf)$" == out);
    REQUIRE(regex_matches(out, "abc.txt"));
    REQUIRE(regex_matches(out, "abc.pdf"));
    REQUIRE_FALSE(regex_matches(out, "abc"));
    REQUIRE_FALSE(regex_matches(out, "abc."));
  }

  SECTION("Glob2Regex - *") {
    std::string in = "abc.*";
    const auto out = glob2regex(in);
    REQUIRE("^abc\\..*$" == out);
    REQUIRE(regex_matches(out, "abc.txt"));
    REQUIRE(regex_matches(out, "abc.pdf"));
    REQUIRE_FALSE(regex_matches(out, "abc"));
    REQUIRE(regex_matches(out, "abc."));
  }

  SECTION("Glob2Regex - []") {
    std::string in = "ab[cd]";
    const auto out = glob2regex(in);
    REQUIRE("^ab[cd]$" == out);
    REQUIRE(regex_matches(out, "abc"));
    REQUIRE(regex_matches(out, "abd"));
    REQUIRE_FALSE(regex_matches(out, "abe"));
    REQUIRE_FALSE(regex_matches(out, "abcd"));
  }

  SECTION("Glob2Regex - close } only") {
    std::string in = "ab}cd";
    const auto out = glob2regex(in);
    REQUIRE("^ab}cd$" == out);
    REQUIRE(regex_matches(out, "ab}cd"));
  }

  SECTION("format_duration 5s") {
    auto formatted = format_duration(5);
    REQUIRE("05s" == formatted);
  }

  SECTION("format_duration - 10s") {
    auto formatted = format_duration(10);
    REQUIRE("10s" == formatted);
  }

  SECTION("format_duration - 10m") {
    auto formatted = format_duration(10 * 60);
    REQUIRE("10m:00s" == formatted);
  }

  SECTION("format_duration - almost 1h") {
    auto formatted = format_duration(50 * 70 + 99);
    REQUIRE("59m:59s" == formatted);
  }

  SECTION("format_duration - 1h") {
    auto formatted = format_duration(60 * 60);
    REQUIRE("01h:00m:00s" == formatted);
  }

  SECTION("format_duration - almost 4h") {
    auto formatted = format_duration(60 * 60 * 3 + 50 * 70 + 99);
    REQUIRE("03h:59m:59s" == formatted);
  }

  SECTION("format_duration - 4h") {
    auto formatted = format_duration(60 * 60 * 4);
    REQUIRE("~4h" == formatted);
  }
}

TEST_CASE("ProgressMonitor", "[progressmonitor]") {
  using namespace opov;

  SECTION("100") {
    std::ostringstream out;
    ProgressMonitor mon(100, out);
    mon.update("t1", "f1");

    REQUIRE(mon.get_count() == 1);
    REQUIRE(mon.get_expected_count() == 100);
  }

  SECTION("restart") {
      std::ostringstream out;
      ProgressMonitor mon(100, out);
      mon.update("t1", "f1");
      mon.restart(10);
      REQUIRE(mon.get_count() == 0);
      REQUIRE(mon.get_expected_count() == 10);
    }

}

TEST_CASE("FormattedReporter", "[fmtreporter]") {
  using namespace opov;

  auto i = std::make_shared<Issue>();
  i->setFile("TestFile.h");
  i->setCode("test++;");
  i->setColumnStart(0); i->setColumnEnd(0);
  i->setLineStart(0); i->setLineEnd(0);
  IssueInstance inst{i, {"File1.cpp", "File2.cpp"}};
  IssueVector issues{inst};

  std::unique_ptr<Configuration> config = util::make_unique<JSONConfiguration>();
  std::ostringstream out;
  out.clear();

  SECTION("Default Output") {
    //Default is: "%f:%ls:%cs: %m @ %s"
    const std::string file_content = R"(
      {
          "global": { } 
      })";

    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + ":0:0:  @ test++;\n";
    REQUIRE(out.str() == expected);
  }

  SECTION("Simple Output") {
    const std::string file_content = R"(
      {
          "global": {
            "format" : "%f : %tu" 
          } 
      })";
    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + " : " + "File1.cpp,File2.cpp\n";
    REQUIRE(out.str() == expected);
  }

  SECTION("Array Access") {
    const std::string file_content = R"(
      {
          "global": {
            "format" : "%f : %tu[0]" 
          } 
      })";
    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + " : " + "File1.cpp\n";
    REQUIRE(out.str() == expected);
  }

  SECTION("Array Access Last Element") {
    const std::string file_content = R"(
      {
          "global": {
            "format" : "%f : %tu[1]" 
          } 
      })";
    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + " : " + "File2.cpp\n";
    REQUIRE(out.str() == expected);
  }

  SECTION("Array Access Out of Bounds") {
    const std::string file_content = R"(
      {
          "global": {
            "format" : "%f : %tu[2]" 
          } 
      })";
    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + " : " + "\n";
    REQUIRE(out.str() == expected);
  }

  SECTION("Array Access Negative Out of Bounds") {
    const std::string file_content = R"(
      {
          "global": {
            "format" : "%f : %tu[-1]" 
          } 
      })";
    std::stringstream file(file_content);
    config->load(file);
    FormattedReporter reporter(config.get(), out);
    reporter.addIssues(issues);
    const std::string expected = i->getFile() + " : " + "\n";
    REQUIRE(out.str() == expected);
  }
}


TEST_CASE("Configuration", "[config]") {
    const std::string file_content = R"(
    {
        "geo": {
              "coordinates": [
                37.871609,
                -122.25831
              ],
              "type": "Point"
        },
        "vectors": {
              "a": [
                37.871609,
                -122.25831
              ],
              "b": [
                10,
                20
              ],
              "c": [
                "c_aa",
                "c_bb"
              ],
        },
         "test" : "data",
    })";
    std::stringstream file(file_content);
    std::unique_ptr<opov::Configuration> config = opov::util::make_unique<opov::JSONConfiguration>();
    SECTION("Simple Parsing") {
        std::string tmp;
        REQUIRE_NOTHROW(config->load(file));
        config->getValue("test", tmp);
        REQUIRE(tmp == "data");
        config->getValue("geo", tmp);
        REQUIRE(tmp == "");
        config->getValue("geo:type", tmp);
        REQUIRE(tmp == "Point");
        std::vector<double> tmpv;
        config->getVector("geo:coordinates", tmpv);
        REQUIRE(tmpv.size() == 2);
        REQUIRE(tmpv[0] == 37.871609);
    }

    SECTION("Parsing Twice") {
        REQUIRE_NOTHROW(config->load(file));
        std::string tmp;
        std::vector<double> tmpv;
        for (int var = 0; var < 2; ++var) {
            REQUIRE_NOTHROW(config->load(file));
            config->getValue("test", tmp);
            REQUIRE(tmp == "data");
            config->getValue("geo", tmp);
            REQUIRE(tmp == "");
            config->getValue("geo:type", tmp);
            REQUIRE(tmp == "Point");
            tmpv.clear();
            config->getVector("geo:coordinates", tmpv);
            REQUIRE(tmpv.size() == 2);
            REQUIRE(tmpv[0] == 37.871609);
        }
    }

    SECTION("Parsing All") {
        REQUIRE_NOTHROW(config->load(file));
        std::vector<double> tmpvd;
        config->getVector("vectors:a", tmpvd);
        REQUIRE(tmpvd.size() == 2);
        REQUIRE(tmpvd[0] == 37.871609);
        REQUIRE(tmpvd[1] == -122.25831);
        std::vector<int> tmpvi;
        config->getVector("vectors:b", tmpvi);
        REQUIRE(tmpvi.size() == 2);
        REQUIRE(tmpvi[0] == 10);
        REQUIRE(tmpvi[1] == 20);
        std::vector<std::string> tmpvs;
        config->getVector("vectors:c", tmpvs);
        REQUIRE(tmpvs.size() == 2);
        REQUIRE(tmpvs[0] == "c_aa");
        REQUIRE(tmpvs[1] == "c_bb");
    }

    SECTION("Parsing Default Value") {
        REQUIRE_NOTHROW(config->load(file));
        std::vector<double> tmpvd;
        config->getVector("vectors:aaa", tmpvd);
        REQUIRE(tmpvd.size() == 0);

        std::string tmp;
        config->getValue("test_ne", tmp, "la");
        REQUIRE(tmp == "la");
        config->getValue("geo_ne", tmp);
        REQUIRE(tmp == "");
        config->getValue("geo:type:ne", tmp, "bla");
        REQUIRE(tmp == "bla");
    }

    SECTION("Parsing Default Lvalue") {
        REQUIRE_NOTHROW(config->load(file));
        std::string tmp;
        std::string def = "lvalue";
        config->getValue("test_ne", tmp, def);
        REQUIRE(tmp == "lvalue");
        config->getValue("geo_ne", tmp, def);
        REQUIRE(tmp == "lvalue");
        config->getValue("geo:type:ne", tmp, def);
        REQUIRE(tmp == "lvalue");
    }
}
