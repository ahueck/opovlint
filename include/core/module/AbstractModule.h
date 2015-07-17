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

namespace clang {
class Stmt;
}

namespace opov {

class ModuleContext;
class Configuration;

class AbstractModule : public Module {
 protected:
  ModuleContext* context;

 public:
  AbstractModule();
  virtual void init(const Configuration* config);
  virtual void setupOnce(const Configuration* config) = 0;
  virtual void execute(ModuleContext* context) override;
  virtual ~AbstractModule();
};

} /* namespace opov */

//#include "AbstractModule.hpp"

#endif /* ABSTRACTMODULE_H_ */
