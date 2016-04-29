/*
 * JSONConfiguration.h
 *
 *  Created on: Jul 10, 2014
 *      Author: ahueck
 */

#ifndef CORE_CONFIGURATION_JSONCONFIGURATION_H
#define CORE_CONFIGURATION_JSONCONFIGURATION_H

#include "Configuration.h"

#include <external/jsonpp.hpp>

#include <string>

namespace opov {

class JSONConfiguration : public opov::Configuration {
 private:
  json::value data;

  template <typename T>
  T get(const std::string& id, T&& def) const;
  template <typename T>
  std::vector<T> getVec(const std::string& id) const;

 public:
  JSONConfiguration();
  bool load(const std::string &file) override;
  void getValue(const std::string &id, std::string &val, std::string def = "") const override;
  void getValue(const std::string &id, double &val, double def = 0.0) const override;
  void getValue(const std::string &id, int &val, int def = 0) const override;
  void getValue(const std::string &id, bool &val, bool def = false) const override;
  void getVector(const std::string &id, std::vector<std::string> &vec) const override;
  void getVector(const std::string &id, std::vector<double> &vec) const override;
  void getVector(const std::string &id, std::vector<int> &vec) const override;
  void getVector(const std::string &id, std::vector<bool> &vec) const override;
  ~JSONConfiguration() override;
};

} /* namespace opov */

#include "JSONConfiguration.hpp"

#endif // CORE_CONFIGURATION_JSONCONFIGURATION_H
