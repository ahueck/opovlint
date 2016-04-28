/*
 * OpOvApp.h
 *
 *  Created on: May 8, 2014
 *      Author: ahueck
 */

#ifndef OPOVAPP_H_
#define OPOVAPP_H_

#include <core/Application.h>

#include <string>

class OpOvApp : public opov::Application {
 private:
  std::string config_path;

 protected:
  void loadConfig() override;
  void createReporter() override;
  void createFactory() override;
  void initModules() override;

 public:
  OpOvApp(const std::string& config_path);

  virtual ~OpOvApp() = default;
};

#endif /* OPOVAPP_H_ */
