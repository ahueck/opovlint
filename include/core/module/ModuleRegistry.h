/*
 * ModuleRegistry.h
 *
 *  Created on: May 18, 2016
 *      Author: ahueck
 */

#ifndef CORE_MODULE_MODULEREGISTRY_H_
#define CORE_MODULE_MODULEREGISTRY_H_

#include <core/utility/Registry.h>

namespace opov {
  class Module;
  using ModuleRegistry = Registry<Module>;

#define REGISTER_MODULE(NAME) \
  namespace { \
	ModuleRegistry::Add<NAME> _##NAME##_(#NAME); \
  }

} /* namespace opov */

#endif // CORE_MODULE_MODULEREGISTRY_H_
