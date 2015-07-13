/*
 * Module.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <string>
#include <memory>

namespace opov {

class Configuration;
class ModuleContext;

class Module {
public:
	virtual void init(const Configuration* config) = 0;
	virtual void execute(ModuleContext* context) = 0;
	virtual std::string moduleName() = 0;
	virtual std::string moduleDescription() = 0;
	virtual ~Module() {
	}
};
} // namespace opov
#endif /* MODULE_H_ */
