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
std::tuple<FormattedReporter::TokenType, Iter, Iter> FormattedReporter::format_range(Iter iter_s, Iter end) {
  // iter_s: expected to be at "%"
  Iter iter = std::next(iter_s);
  auto dist_to_end = std::distance(iter, end);

  if (dist_to_end != 0) {
    auto& map_f = map_format();
    // parse 1 or 2 chars ahead and extract from map
    // (greedy: try 2 first)
    for (decltype(dist_to_end) i = lookahead; i >= 1; --i) {
      if (dist_to_end >= i) {
        std::string fmt(iter, iter + i);
        if (map_f.find(fmt) != std::end(map_f)) {
          std::advance(iter, i);
          return std::make_tuple(TokenType::Var, iter_s, iter);
        }
      }
    }
  }

  return filler_range(iter_s, end);
}

template <typename Iter, char format_c>
std::tuple<FormattedReporter::TokenType, Iter, Iter> FormattedReporter::filler_range(Iter iter_s, Iter end) {
  // std::next as we know current iter is filler
  auto filler = std::find(std::next(iter_s), end, format_c);
  return std::make_tuple(TokenType::Filler, iter_s, filler);
}

template <typename Iterator>
std::vector<std::tuple<FormattedReporter::TokenType, Iterator, Iterator>> FormattedReporter::build_tokens(
    Iterator begin, Iterator iter_end) {
  using Token = std::tuple<TokenType, Iterator, Iterator>;
  std::vector<Token> tokenized_format;

  auto inserter = [&tokenized_format](const Token& token) {
    if (TokenType::Var == std::get<0>(token)) {
      tokenized_format.push_back(token);
    } else {
      TokenType tok_t;
      Iterator begin;
      std::tie(tok_t, begin, std::ignore) = tokenized_format.back();
      if (TokenType::Filler == tok_t) {
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

  std::vector<format_fn> formatter;

  for (auto& token : tokenized_format) {
    TokenType tok;
    Iterator beg, end;
    std::tie(tok, beg, end) = token;
    if (TokenType::Var == tok) {
      std::string fmt(std::next(beg), end);
      format_fn func = map_f[fmt];
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
