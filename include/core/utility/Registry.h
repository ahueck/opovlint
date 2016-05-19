/*
 * Registry.h
 *
 *  Created on: May 17, 2016
 *      Author: ahueck
 */

#ifndef CORE_UTILITY_REGISTRY_H_
#define CORE_UTILITY_REGISTRY_H_

#include <core/utility/Util.h>

#include <map>
#include <memory>

namespace opov {

template <typename T>
class RegistryEntry final {
  using Factory = std::unique_ptr<T> (*)();
  const char* name;
  const char* description;
  Factory ctor;

 public:
  RegistryEntry(const char* name, const char* description, Factory ctor)
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

template <typename T>
class Registry final {
  using entry = RegistryEntry<T>;
  // TODO ability to iterate over entries and list all
  using registry = std::map<std::string, const entry*>;
  using const_iterator = typename registry::const_iterator;

 public:
  Registry() = delete;

  /*
    static const_iterator cbegin() {
      auto& reg = entry_map();
      return reg.cbegin();
    }

    static const_iterator cend() {
      auto& reg = entry_map();
      return reg.cend();
    }
  */

  static void registrate(const std::string& name, const entry* e) {
    auto& reg = entry_map();
    if (reg.find(name) == std::end(reg)) {
      reg[name] = e;
    }
  }

  static const entry* entry_of(const std::string& name) {
    auto& reg = entry_map();
    if (reg.find(name) == std::end(reg)) {
      return nullptr;
    }
    auto map_entry = reg[name];
    return map_entry;
  }

  static std::unique_ptr<T> instance_of(const std::string& name) {
    auto map_entry = entry_of(name);
    return map_entry != nullptr ? map_entry->instantiate() : nullptr;
  }

  static bool contains(const std::string& name) {
    auto& reg = entry_map();
    return reg.find(name) != std::end(reg);
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
      static_assert(std::is_base_of<T, U>::value, "Registry<T>::Add<U> requires U to be derived from T.");
      return util::make_unique<U>();
    }
  };

  static registry& entry_map() {
    static registry impl;
    return impl;
  }
};

} /* namespace opov */

#endif  // CORE_UTILITY_REGISTRY_H_
