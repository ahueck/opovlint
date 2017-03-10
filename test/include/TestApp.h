/*
 * TestApp.h
 *
 *  Created on: May 28, 2014
 *      Author: ahueck
 */

#ifndef OPOVAPP_H_
#define OPOVAPP_H_

#include <core/Application.h>
#include <core/utility/Util.h>
#include <core/IFactory.h>
#include <core/configuration/JSONConfiguration.h>
#include <AnalyzerFactory.h>
#include <core/issue/IssueHandler.h>
#include <core/transformation/TransformationHandler.h>
#include "MockReporter.h"

#include <sstream>


const static std::string conf_double = R"({
  "global" : {
    "filter" : false,
    "type" : "double"    
  }
}
)";
const static std::string conf = R"({
  "global" : {
    "filter" : false,
    "type" : "scalar"    
  }
}
)";

namespace opov {
namespace test {

class TestApp : public Application {
public:
	std::string config_data;
	bool is_file;

protected:
	void loadConfig() {
		config = opov::util::make_unique<JSONConfiguration>();
		bool success = false;
		if(!is_file) {
		  std::stringstream stream(config_data);
		  success = config->load(stream);
		} else {
		  success = config->load(config_data);
		}
		if (!success) {
		  std::cerr << "Config not loaded. Terminating." << std::endl;
		  std::exit(EXIT_FAILURE);
		}
	}

	void createReporter() {
		reporter = opov::util::make_unique<MockReporter>();
	}

	void createFactory() {
		executor = opov::util::make_unique<AnalyzerFactory>(config.get(), ihandler.get(), thandler.get());
		executor->init();
	}

public:
	TestApp(std::string conf_file=conf, bool is_file = false) : config_data(conf_file), is_file(is_file) {

	}

	MockReporter* getReporter()  {
		return reinterpret_cast<MockReporter* >(reporter.get());
	}

	TransformationHandler* getHandler() {
		return reinterpret_cast<TransformationHandler* >(thandler.get());
	}

	virtual void initModules() {};
/*
	virtual void addModule(Module* module) {
		executor->setModule(module);
	}
*/
	virtual ~TestApp() {

	}
};

}
}

#endif /* OPOVAPP_H_ */
