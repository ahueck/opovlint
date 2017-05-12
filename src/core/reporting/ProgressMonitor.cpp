/*
 * ProgressMonitor.cpp
 *
 *  Created on: May 11, 2017
 *      Author: ahueck
 */

#include <core/reporting/ProgressMonitor.h>

#include <core/utility/Util.h>

#include <iomanip>

namespace opov {

ProgressMonitor::ProgressMonitor(size_t expected_count, std::ostream& os)
    : expected_count{expected_count}, count{0}, t_start{}, chars_flushed{0}, output{os} {
  restart(expected_count);
}

void ProgressMonitor::restart(size_t expected_count_) {
  count = 0;
  this->expected_count = expected_count_;

  rm_line();
  output << "Progress Monitor:\n";

  if (!expected_count) {
    expected_count = {1};
  }
  t_start = {};
  chars_flushed = {0};
}

size_t ProgressMonitor::update(std::string module, std::string file, size_t u_count) {
  count += u_count;

  unsigned duration{0u};
  if (t_start == time_point{}) {
    t_start = p_clock::now();
  } else {
    auto t_now = p_clock::now();
    auto accum_s = std::chrono::duration_cast<std::chrono::seconds>(t_now - t_start);
    duration = static_cast<unsigned>((static_cast<double>(accum_s.count()) / count) * (expected_count - count));
  }

  const double perc = (static_cast<double>(count) / expected_count) * 100.0;
  const std::string job_str = module + ": " + file;

  rm_line();
  output << "[" << std::setw(5) << std::setprecision(1) << std::fixed << perc << "%]"
         << "[" << std::setw(11) << std::right << util::format_duration(duration) << "]" << job_str << "\r"
         << std::flush;
  chars_flushed = job_str.length() + 16 + 5;

  if (expected_count == count) {
    output << std::endl;
  }

  return count;
}

size_t ProgressMonitor::get_count() const {
  return count;
}

size_t ProgressMonitor::get_expected_count() const {
  return expected_count;
}

void ProgressMonitor::rm_line() {
  if (!chars_flushed) {
    return;
  }
  std::string empty_s(chars_flushed, ' ');
  output << empty_s << "\r" << std::flush;
}

} /* namespace opov */
