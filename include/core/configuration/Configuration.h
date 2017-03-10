/*
 * COnfiguration.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef CORE_CONFIGURATION_CONFIGURATION_H
#define CORE_CONFIGURATION_CONFIGURATION_H

#include <string>
#include <vector>

namespace opov {

class Configuration {
 public:
  virtual bool load(const std::string& file) = 0;
  virtual bool load(const std::istream& in) = 0;
  virtual void getValue(const std::string& id, std::string& val, std::string def = "") const = 0;
  virtual void getValue(const std::string& id, double& val, double def = 0.0) const = 0;
  virtual void getValue(const std::string& id, int& val, int def = 0) const = 0;
  virtual void getValue(const std::string& id, bool& val, bool def = false) const = 0;
  virtual void getVector(const std::string& id, std::vector<std::string>& vec) const = 0;
  virtual void getVector(const std::string& id, std::vector<double>& vec) const = 0;
  virtual void getVector(const std::string& id, std::vector<int>& vec) const = 0;
  virtual void getVector(const std::string& id, std::vector<bool>& vec) const = 0;
  virtual ~Configuration() = default;
};

} /* namespace opov */

#endif  // CORE_CONFIGURATION_CONFIGURATION_H
