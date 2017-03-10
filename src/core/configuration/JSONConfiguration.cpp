/*
 * JSONConfiguration.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: ahueck
 */

#include <core/configuration/JSONConfiguration.h>

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
  return load(in);
}

bool JSONConfiguration::load(const std::istream& in) {
  try {
    json::parse(in, data);
  } catch (const json::parser_error& e) {
    LOG_INFO("Exception parsing json from istream: " << e.what() << ".");
    return false;
  }
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
