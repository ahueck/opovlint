/*
 * AbstractModule.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef CORE_MODULE_ABSTRACTMODULE_H
#define CORE_MODULE_ABSTRACTMODULE_H

#include "Module.h"

#include <string>

namespace opov {

class ModuleContext;
class Configuration;

class AbstractModule : public Module {
 protected:
  ModuleContext* context;
  std::string type_s;
  bool transform;

 public:
  AbstractModule();
  void init(const Configuration* config) override;
  virtual void setupOnce(const Configuration* config);
  void execute(ModuleContext* context) override;
  ~AbstractModule() override;
};

} /* namespace opov */

#endif // CORE_MODULE_ABSTRACTMODULE_H
