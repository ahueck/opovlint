/*
 * Registry.h
 *
 *  Created on: May 17, 2016
 *      Author: ahueck
 */

#ifndef INCLUDE_CORE_UTILITY_REGISTRY_H_
#define INCLUDE_CORE_UTILITY_REGISTRY_H_

#include <core/utility/Util.h>

#include <map>
#include <memory>

namespace opov {
namespace registry {

template <typename T>
class RegistryEntry;

template <typename T>
using entry = RegistryEntry<T>;

template <typename T>
class Registry final {
  // TODO ability to iterate over entries and list all
  using registry = std::map<std::string, const entry*>;

 public:
  Registry() = delete;

  static void registrate(const std::string& name, const entry* e) {
    auto& reg = entry_map();
    if (reg.find(name) == std::end(reg)) {
      reg[name] = e;
    }
  }

  static std::unique_ptr<T> instanceOf(const std::string& name) {
    auto& reg = entry_map();
    if (reg.find(name) == std::end(reg)) {
      return nullptr;
    }

    return reg[name]->instantiate();
  }

  template <typename U>
  class Add final {
    entry e;

   public:
    explicit Add(const char* name, const char* description = "") : e(name, description, make_ctor) {
      Registry::registrate(std::string(name), &e);
    }

    Add(const Add&) = delete;
    Add& operator=(const Add&) = delete;

   private:
    static std::unique_ptr<T> make_ctor() {
      return util::make_unique<U>();
    }
  };

 private:
  static registry& entry_map() {
    static registry impl;
    return impl;
  }
};

template <typename T>
class RegistryEntry final {
  const char* name;
  const char* description;
  std::unique_ptr<T> (*ctor)();

 public:
  RegistryEntry(const char* name, const char* description, std::unique_ptr<T> (*ctor)())
      : name(name), description(description), ctor(ctor) {
  }

  const char* get_name() const {
    return name;
  }

  const char* get_description() const {
    return description;
  }

  std::unique_ptr<T> instantiate() const {
    return ctor();
  }
};

} /* namespace registry */
} /* namespace opov */

#endif /* INCLUDE_CORE_UTILITY_REGISTRY_H_ */
