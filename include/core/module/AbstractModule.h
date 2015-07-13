/*
 * AbstractModule.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef ABSTRACTMODULE_H_
#define ABSTRACTMODULE_H_

#include "Module.h"

#include <string>

/*
 #include <core/ModuleContext.h>
 #include <core/Configuration.h>
 #include <core/Issue.h>
 #include <core/ClangUtil.h>
 */

namespace clang {
class Stmt;
}

//TODO maybe add helper function to add issue
namespace opov {

class ModuleContext;
class Configuration;

class AbstractModule: public Module {
protected:
	ModuleContext* context;

public:
	AbstractModule();
	//template<typename NODE>
	//void addIssue(NODE statement, std::string description = "");
	virtual void init(const Configuration* config);
	virtual void setupOnce(const Configuration* config) = 0;
	virtual void execute(ModuleContext* context) override;
	virtual ~AbstractModule();
};

} /* namespace opov */

//#include "AbstractModule.hpp"

#endif /* ABSTRACTMODULE_H_ */
