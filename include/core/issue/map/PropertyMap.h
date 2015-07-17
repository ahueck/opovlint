/*
 * PropertyMap.h
 *
 *  Created on: Jul 13, 2015
 *      Author: ahueck
 */

#ifndef PROPERTYMAP_H_
#define PROPERTYMAP_H_

#include "Value.h"
#include "PropertyMacros.h"

#include <map>

namespace opov {
typedef std::map<std::string, Value> property_map;

// creates a getter and setter using a std::map<std::string, Value> called
// _properties as the property store
#define IssueProperty(NAME)                                               \
  _as DS_CONCAT(NAME, PropertyType);                                      \
  void DS_CONCAT(set, NAME)(DS_CONCAT(NAME, PropertyType) value) {        \
    _properties[DS_STRINGIFY(NAME)] = Value(value);                       \
  }                                                                       \
  DS_CONCAT(NAME, PropertyType) DS_CONCAT(get, NAME)() {                  \
    auto it = _properties.find(DS_STRINGIFY(NAME));                       \
    if (it == std::end(_properties))                                      \
      return PropertyType<DS_CONCAT(NAME, PropertyType)>::DefaultValue(); \
    return it->second.get<DS_CONCAT(NAME, PropertyType)>();               \
  }
}

#endif /* PROPERTYMAP_H_ */
