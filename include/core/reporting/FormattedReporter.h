/*
 * FormattedReporter.h
 *
 *  Created on: Oct 12, 2016
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_FORMATTEDREPORTER_H_
#define CORE_REPORTING_FORMATTEDREPORTER_H_

#include "IssueReporter.h"
#include <core/issue/Issue.h>
#include <core/utility/Util.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>


namespace opov {

class Configuration;

class FormattedReporter : public IssueReporter {
 protected:
  using format_fn = std::function<std::string(const IssueInstance&)>;

  std::vector<format_fn> formatter;

  enum class TokenType { Var, Filler };

  static std::map<std::string, format_fn>& mapper() {
    static std::map<std::string, format_fn> fmap;
    return fmap;
  }

  static void init_map() {
    using util::num2str;
    auto& fmap = mapper();
    fmap["ls"] = [](const IssueInstance& i) { return num2str(i.issue->getLineStart()); };
    fmap["le"] = [](const IssueInstance& i) { return num2str(i.issue->getLineEnd()); };
    fmap["cs"] = [](const IssueInstance& i) { return num2str(i.issue->getColumnStart()); };
    fmap["ce"] = [](const IssueInstance& i) { return num2str(i.issue->getColumnEnd()); };
    fmap["f"] = [](const IssueInstance& i) { return i.issue->getFile(); };
    fmap["s"] = [](const IssueInstance& i) { return i.issue->getCode(); };
    fmap["m"] = [](const IssueInstance& i) { return i.issue->getModuleName(); };
    fmap["d"] = [](const IssueInstance& i) { return i.issue->getDescription(); };
    fmap["o"] = [](const IssueInstance& i) {
      std::ostringstream out_ss;
      const auto& tu_vec = i.tunit_occurences;
      if (!tu_vec.empty()) {
        std::copy(std::begin(tu_vec), std::end(tu_vec) - 1,
                  std::ostream_iterator<decltype(i.tunit_occurences)::value_type>(out_ss, ","));
        out_ss << *(std::end(tu_vec) - 1);
      }
      return out_ss.str();
    };
  }

  template <typename Iter, std::ptrdiff_t lookahead = 2>
  std::tuple<TokenType, Iter, Iter> format_range(Iter iter_s, Iter end);

  template <typename Iter, char format_c = '%'>
  std::tuple<TokenType, Iter, Iter> filler_range(Iter iter_s, Iter end);

  template <typename Iterator>
  std::vector<std::tuple<TokenType, Iterator, Iterator>> build_tokens(Iterator begin, Iterator iter_end);

  template <typename Iterator>
  std::vector<format_fn> build_formatter(Iterator begin, Iterator end);

 public:
  explicit FormattedReporter(const Configuration* config);
  virtual void addIssues(const IssueVector& issues) override;
  virtual ~FormattedReporter() = default;
};

} /* namespace opov */

#include "FormattedReporter.hpp"

#endif /* CORE_REPORTING_FORMATTEDREPORTER_H_ */
