/*
 * IssueReport.h
 *
 *  Created on: May 14, 2014
 *      Author: ahueck
 */

#ifndef ISSUE_H_
#define ISSUE_H_

#include <map>
#include "PropertyMacros.h"
#include "Value.h"

namespace opov {
//creates a getter and setter using a std::map<std::string, Value> called _properties as the property store
#define IssueProperty(NAME)\
  _as DS_CONCAT(NAME,PropertyType);\
  void DS_CONCAT(set,NAME)(DS_CONCAT(NAME,PropertyType) value){\
  _properties[DS_STRINGIFY(NAME)] = Value(value);\
    }\
    DS_CONCAT(NAME, PropertyType) DS_CONCAT(get, NAME)(){\
    auto it = _properties.find(DS_STRINGIFY(NAME));\
    if(it == std::end(_properties))return PropertyType<DS_CONCAT(NAME,PropertyType)>::DefaultValue();\
    return it->second.get<DS_CONCAT(NAME,PropertyType)>();\
    }

class Issue {
private:
	std::map<std::string, Value> _properties;
public:
	Issue() {

	}
	const std::map<std::string, Value>& properties() {
		return _properties;
	}

	int IssueProperty(LineStart);
	int IssueProperty(LineEnd);
	int IssueProperty(ColumnStart);
	int IssueProperty(ColumnEnd);
	std::string IssueProperty(File);
	std::string IssueProperty(Description);
	std::string IssueProperty(Code);
	std::string IssueProperty(ModuleName);
	// FIXME redundant since it is a static string. store somewhere else for reporting...
	std::string IssueProperty(ModuleDescription);
};

} // namespace opov

#endif /* ISSUE_H_ */
