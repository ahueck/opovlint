/*
 * IssueTraits.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_MAP_VALUETRAITS_H
#define CORE_ISSUE_MAP_VALUETRAITS_H

#include <string>

namespace opov {

// specializable Property type traits
template <typename T>
struct PropertyType {
  static const std::string& name() {
    static std::string _name = "unknown";
    return _name;
  }

  static T DefaultValue() {
    return T();
  }
};

template <>
struct PropertyType<std::string> {
  static const std::string& name() {
    static std::string _name = "string";
    return _name;
  }

  static std::string DefaultValue() {
    return "";
  }
};

template <>
struct PropertyType<int> {
  static const std::string& name() {
    static std::string _name = "int";
    return _name;
  }

  static int DefaultValue() {
    return 0;
  }
};

template <>
struct PropertyType<unsigned int> {
  static const std::string& name() {
    static std::string _name = "unsigned int";
    return _name;
  }

  static unsigned int DefaultValue() {
    return 0;
  }
};

} /* namespace opov */

#endif  // CORE_ISSUE_MAP_VALUETRAITS_H
