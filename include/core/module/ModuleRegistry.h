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
using ModuleEntry = RegistryEntry<Module>;

#define REGISTER_MODULE(NAME)                  \
  namespace {                                  \
  ModuleRegistry::Add<NAME> _##NAME##_(#NAME); \
  }                                            \
  MODULE_ANCHOR(NAME) = 0;

#define MODULE_ANCHOR(NAME) volatile int Anchor_##NAME##_

#define LINK_MODULE(NAME)                                            \
  extern MODULE_ANCHOR(NAME);                                        \
  namespace {                                                        \
  int __attribute__((__unused__)) Sink_##NAME##_ = Anchor_##NAME##_; \
  }

} /* namespace opov */

#endif  // CORE_MODULE_MODULEREGISTRY_H_
