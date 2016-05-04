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


#define _CONF_DOUBLE "test/data/test_double_conf.json"
#define _CONF "test/data/test_conf.json"
const static std::string conf_double = _CONF_DOUBLE;
const static std::string conf = _CONF;

namespace opov {
namespace test {

class TestApp: public Application {
public:
	std::string conf_file;

protected:
	void loadConfig() {
		config = opov::util::make_unique<JSONConfiguration>();
		bool success = config->load(conf_file);
		if (!success) {
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
	TestApp(std::string conf_file=conf) : conf_file(conf_file) {

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
