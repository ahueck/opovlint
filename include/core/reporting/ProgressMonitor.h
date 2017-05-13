/*
 * ProgressMonitor.h
 *
 *  Created on: May 11, 2017
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_PROGRESSMONITOR_H_
#define CORE_REPORTING_PROGRESSMONITOR_H_

#include <chrono>
#include <iostream>

namespace opov {

class ProgressMonitor {
  using p_clock = std::chrono::high_resolution_clock;
  using time_point = std::chrono::time_point<p_clock>;

 protected:
  size_t expected_count;
  size_t count;
  time_point t_start;
  size_t chars_flushed;
  std::ostream& output;

 public:
  explicit ProgressMonitor(size_t expected_count, std::ostream& os = std::cout);

  void restart(size_t expected_count_);

  size_t update(std::string description, size_t u_count = 1);

  size_t get_count() const;

  size_t get_expected_count() const;

  virtual ~ProgressMonitor() = default;
};

} /* namespace opov */

#endif /* CORE_REPORTING_PROGRESSMONITOR_H_ */
