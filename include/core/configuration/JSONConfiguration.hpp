/*
 * JSONProperty.hpp
 *
 *  Created on: Jul 14, 2014
 *      Author: ahueck
 */

#ifndef JSONPROPERTY_HPP_
#define JSONPROPERTY_HPP_

#include <core/utility/Util.h>

namespace opov {

template <typename T>
T JSONConfiguration::get(const std::string& id, T&& def) const {
  const auto split_id = util::split(id);
  auto&& current = data.as<json::object>();

  auto it = split_id.begin();
  for (; it != (split_id.end() - 1); ++it) {
    if (!current[*it].is<json::object>()) {
      return std::forward<T>(def);
    }
    current = current[*it].as<json::object>();
  }

  return current[*it].as<T>(std::forward<T>(def));
}

template <typename T>
std::vector<T> JSONConfiguration::getVec(const std::string& id) const {
  const auto values = get<json::array>(id, json::array());
  std::vector<T> items;
  items.reserve(values.size());

  for (auto& val : values) {
    items.push_back(val.as<T>(T()));
  }

  return items;
}

} /* namespace opov */

#endif /* JSONPROPERTY_HPP_ */
