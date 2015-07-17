/*
 * IssueTraits.h
 *
 *  Created on: May 15, 2014
 *      Author: ahueck
 */

#ifndef ISSUETRAITS_H_
#define ISSUETRAITS_H_

#include <string>

//#include <map>
//#include <ostream>

namespace opov {

// static std::map <std::string, std::function<void(std::ostream &, void *)> >
// formatters;

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
    // static int i = []() {formatters["string"] = [](std::ostream & out, void *
    // in) {out << (*(std::string*)in);}; return 0;}();
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
    // static int i = []() {formatters["int"] = [](std::ostream & out, void *
    // in) {out << (*(int*)in);}; return 0;}();
    return _name;
  }

  static int DefaultValue() {
    return -1;
  }
};

template <>
struct PropertyType<unsigned int> {
  static const std::string& name() {
    static std::string _name = "unsigned int";
    // static int i = []() {formatters["unsigned int"] = [](std::ostream & out,
    // void * in) {out << (*(unsigned int*)in);}; return 0;}();
    return _name;
  }

  static unsigned int DefaultValue() {
    return 0;
  }
};

}  // namespace opov

#endif /* ISSUETRAITS_H_ */
