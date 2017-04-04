/*
 * FormattedReporter.hpp
 *
 *  Created on: Oct 12, 2016
 *      Author: ahueck
 */

#ifndef CORE_REPORTING_FORMATTEDREPORTER_HPP_
#define CORE_REPORTING_FORMATTEDREPORTER_HPP_

namespace opov {

template <typename Iter, std::ptrdiff_t lookahead>
std::tuple<FormattedReporter::TokenType, Iter, Iter> FormattedReporter::format_range(Iter iter_start, Iter iter_end) {
  // iter_start: expected to be at "%"
  Iter iter_current = std::next(iter_start);
  auto dist_to_end = std::distance(iter_current, iter_end);

  if (dist_to_end != 0) {
    auto& map_f = map_format();
    // parse 1 or 2 chars ahead and extract from map
    // (greedy: try 2 first)
    for (decltype(dist_to_end) i = lookahead; i >= 1; --i) {
      if (dist_to_end >= i) {
        std::string fmt(iter_current, iter_current + i);
        if (map_f.find(fmt) != std::end(map_f)) {
          std::advance(iter_current, i);
          return std::make_tuple(TokenType::Var, iter_start, iter_current);
        } else if ("tu" == fmt) {
          std::advance(iter_current, i);
          // ignore "tu"
          auto special_start = iter_current;
          // look for potential [%num] access after:
          if(*iter_current == '[') {
            auto bracket_pos = std::find(iter_current, iter_end, ']');
            if(bracket_pos != iter_end) {
              iter_current = std::next(bracket_pos);
            }
          }
          return std::make_tuple(TokenType::TU_Access, special_start, iter_current);
        }
      }
    }
  }

  return filler_range(iter_start, iter_end);
}

template <typename Iter, char format_c>
std::tuple<FormattedReporter::TokenType, Iter, Iter> FormattedReporter::filler_range(Iter iter_start, Iter iter_end) {
  // std::next as we know current iter is filler
  auto filler = std::find(std::next(iter_start), iter_end, format_c);
  return std::make_tuple(TokenType::Filler, iter_start, filler);
}

template <typename Iterator>
std::vector<std::tuple<FormattedReporter::TokenType, Iterator, Iterator>> FormattedReporter::build_tokens(
    Iterator begin, Iterator iter_end) {
  using Token = std::tuple<TokenType, Iterator, Iterator>;
  std::vector<Token> tokenized_format;

  auto inserter = [&tokenized_format](const Token& token) {
    if (TokenType::Var == std::get<0>(token)) {
      tokenized_format.push_back(token);
    } else if(TokenType::TU_Access == std::get<0>(token)) {
      tokenized_format.push_back(token);
    } else {
      TokenType tok_t;
      Iterator begin;
      // Look at the previous token, possibly merge 2 filler tokens:
      std::tie(tok_t, begin, std::ignore) = tokenized_format.back();
      if (TokenType::Filler == tok_t) {
        // extend the range of fillers (merging two regions)
        tokenized_format.pop_back();
        tokenized_format.push_back(std::make_tuple(tok_t, begin, std::get<2>(token)));
      } else {
        tokenized_format.push_back(token);
      }
    }
  };

  Iterator current = begin;
  while (current != iter_end) {
    Token token;
    switch (*current) {
      case '%': {
        token = format_range(current, iter_end);
        break;
      }
      default: { token = filler_range(current, iter_end); }
    }
    inserter(token);
    current = std::get<2>(token);
  }
  return tokenized_format;
}

template <typename Iterator>
std::vector<FormattedReporter::format_fn> FormattedReporter::build_formatter(Iterator begin, Iterator end) {
  map_init();
  auto& map_f = map_format();
  auto tokenized_format = build_tokens(begin, end);

  auto build_tu_access = [&](Iterator begin, Iterator end) -> format_fn {
    // we get begin='[' and end=']', between is a number
    if(begin == end) {
      return map_f["o"];
    }
    auto num_iter_start = std::next(begin);
    std::advance(end, -1);
    std::string num(num_iter_start, end);
    if(num.find_first_not_of("0123456789") == std::string::npos) {
      const auto index = util::str2num<size_t>(num);
      format_fn f = [index](const IssueInstance& i) -> std::string {
        const auto& tu_vec = i.tunit_occurences;
        if(index < tu_vec.size() && index >= 0) {
          return tu_vec[index];
        }
        return "";
      };

      return f;
    }
    const format_fn fallback =[] (const IssueInstance&) { return ""; };
    return fallback;
  };

  std::vector<format_fn> formatter;

  for (auto& token : tokenized_format) {
    TokenType tok;
    Iterator beg, end;
    std::tie(tok, beg, end) = token;
    if (TokenType::Var == tok) {
      std::string fmt(std::next(beg), end);
      format_fn func = map_f[fmt];
      formatter.push_back(func);
    } else if(TokenType::TU_Access == tok) {
      format_fn func = build_tu_access(beg, end);
      formatter.push_back(func);
    } else {
      std::string fmt(beg, end);
      formatter.push_back([fmt](const IssueInstance& i) { return fmt; });
    }
  }

  return formatter;
}

} /* namespace opov */

#endif /* CORE_REPORTING_FORMATTEDREPORTER_HPP_ */
