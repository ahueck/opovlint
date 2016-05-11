/*
 * IssueReport.h
 *
 *  Created on: May 14, 2014
 *      Author: ahueck
 */

#ifndef CORE_ISSUE_ISSUE_H
#define CORE_ISSUE_ISSUE_H

#include "map/PropertyMap.h"

#include <functional>
#include <sstream>

namespace opov {

class Issue final {
 private:
  property_map _properties;

 public:
  const property_map& properties() {
    return _properties;
  }

  size_t hash() const {
    std::ostringstream sstream;
    std::hash<std::string> hash_str_fn;

    sstream << getLineStart() << getColumnStart() << getLineEnd() << getColumnEnd();
    sstream << getFile() << getModuleName() << getCode();
    std::string hash_str(sstream.str());

    return hash_str_fn(hash_str);
    /*
    size_t hash = 7;
    size_t pos_hash = getLineStart() ^ (getColumnStart() << 4) ^ (getLineEnd() << 8) ^ (getColumnEnd() << 16);
    hash += std::hash<std::string>()(getFile());
    hash = 17 * hash + std::hash<std::string>()(getModuleName());
    return hash ^ pos_hash;
    */
  }

  int IssueProperty(LineStart);
  int IssueProperty(LineEnd);
  int IssueProperty(ColumnStart);
  int IssueProperty(ColumnEnd);
  std::string IssueProperty(File);
  std::string IssueProperty(Description);
  std::string IssueProperty(Code);
  std::string IssueProperty(ModuleName);
  std::string IssueProperty(ModuleDescription);
};

} /* namespace opov */

#endif  // CORE_ISSUE_ISSUE_H
