/*
 * JSONConfiguration.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: ahueck
 */

#include <core/configuration/JSONConfiguration.h>
#include <core/logging/Logger.h>

#include <fstream>

namespace opov {

JSONConfiguration::JSONConfiguration() {

}

bool JSONConfiguration::load(const std::string& file) {
  std::ifstream in(file);
  if (!in.is_open()) {
    LOG_INFO("Configuration file not found: " << file << ". Exiting...");
    return false;
  }
  json::parse(in, data);
  return true;
}

void JSONConfiguration::getValue(const std::string& id, std::string& val, std::string def) const {
  val = get<std::string>(id, std::move(def));
}

void JSONConfiguration::getValue(const std::string& id, double& val, double def) const {
  val = get<double>(id, std::move(def));
}

void JSONConfiguration::getValue(const std::string& id, int& val, int def) const {
  val = get<int>(id, std::move(def));
}

void JSONConfiguration::getValue(const std::string& id, bool& val, bool def) const {
  val = get<bool>(id, std::move(def));
}

void JSONConfiguration::getVector(const std::string& id, std::vector<std::string>& vec) const {
  vec = getVec<std::string>(id);
}

void JSONConfiguration::getVector(const std::string& id, std::vector<double>& vec) const {
  vec = getVec<double>(id);
}

void JSONConfiguration::getVector(const std::string& id, std::vector<int>& vec) const {
  vec = getVec<int>(id);
}

void JSONConfiguration::getVector(const std::string& id, std::vector<bool>& vec) const {
  vec = getVec<bool>(id);
}

JSONConfiguration::~JSONConfiguration() = default;

} /* namespace opov */
