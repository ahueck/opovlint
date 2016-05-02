/*
 * Value.h
 *
 *  Created on: Jul 15, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_MAP_VALUE_H
#define CORE_ISSUE_MAP_VALUE_H

#include "ValueTraits.h"

#include <memory>

namespace opov {

/*
 * Caveat: copy-constructor has share semantic w.r.t. data behind shared_ptr
 */
class Value {
 private:
  std::string type;
  std::shared_ptr<void> value;

 public:
  Value() : type("unknown"), value(nullptr) {
  }

  template <typename T>
  explicit Value(const T& val) : type(PropertyType<T>::name()), value(std::make_shared<T>(val)) {
  }

  template <typename T>
  const T& get() const {
    return *((T*)value.get());
  }
};

} /* namespace opov */

#endif  // CORE_ISSUE_MAP_VALUE_H
