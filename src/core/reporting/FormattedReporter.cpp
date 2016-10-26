/*
 * FormattedReporter.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: ahueck
 */

#include <core/reporting/FormattedReporter.h>
#include <core/configuration/Configuration.h>

namespace opov {

FormattedReporter::FormattedReporter(const Configuration* config) : FormattedReporter(config, std::cout) {
}

FormattedReporter::FormattedReporter(const Configuration* config, std::ostream& output) : IssueReporter(output) {
  std::string format_string;
  config->getValue("global:format", format_string, "%f:%ls:%cs: %m @ %s");
  formatter = build_formatter(std::begin(format_string), std::end(format_string));
}

void FormattedReporter::addIssues(const IssueVector& issues) {
  std::ostringstream out_ss;
  for (auto& issue : issues) {
    for (auto& format_fn : formatter) {
      out_ss << format_fn(issue);
    }
    out_ss << "\n";
  }
  output << out_ss.str();
}

} /* namespace opov */
