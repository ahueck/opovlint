/*
 * Util.h
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#ifndef CORE_UTILITY_UTIL_H
#define CORE_UTILITY_UTIL_H

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/Regex.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace opov {
namespace util {

namespace detail {

template <typename T>
using is_number_t =
    typename std::integral_constant<bool, std::is_integral<T>::value || std::is_floating_point<T>::value>::type;

template <typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

template <typename T>
inline std::string num2str(std::true_type, T val) {
  return std::to_string(val);
}

template <typename T>
inline std::string num2str(std::false_type, T val) {
  std::ostringstream sstream;
  sstream << val;
  return sstream.str();
}

} /* namespace detail */

template <typename T>
inline std::string num2str(T&& val) {
  using namespace detail;
  return num2str(is_number_t<remove_ref_t<T>>(), std::forward<T>(val));
}

template <typename T>
inline T str2num(const std::string& val) {
  return static_cast<T>(stoll(val));
}

inline std::vector<std::string> split(const std::string& input, char delimiter = ':') {
  std::vector<std::string> tokens;
  /*
  auto lastPos = input.find_first_not_of(delimiter, 0);
  auto pos = input.find_first_of(delimiter, lastPos);
  while(std::string::npos != pos || std::string::npos != lastPos) {
    tokens.push_back(input.substr(lastPos, pos - lastPos));
    lastPos = input.find_first_not_of(delimiter, pos);
    pos = input.find_first_of(delimiter, lastPos);
  }
  */
  std::stringstream sstream(input);
  std::string token;
  while (std::getline(sstream, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

inline bool startsWith(const std::string& str, const std::string prefix) {
  return std::equal(prefix.begin(), prefix.end(), str.begin());
}

inline std::string remove_nl(std::string multi_line) {
  auto end = std::remove(multi_line.begin(), multi_line.end(), '\n');
  multi_line.erase(end, multi_line.end());
  return multi_line;
}

inline std::string trim_rep(std::string str, char rep = ' ') {
  auto end = std::unique(str.begin(), str.end(), [&](char a, char b) -> bool { return a == rep && (a == b); });
  str.erase(end, str.end());
  return str;
}

inline std::string glob2regex(const std::string& glob) {
  // Handles glob with no error checking:
  // Choice: '{a,b,c}' eq. (a|b|c)
  // Any char in bracket: '[abc]' eq. [abc]
  // Any char: '?' eq. .
  // Any string: '*' eq. .*
  std::ostringstream glob_reg;
  int in_curly{0};
  /*
   * TODO: handle "\\" in glob:
        case '\\':
          if(escape) {
            return "\\\\";
            escape = false;
          } else {
            escape = true;
          }
  */
  const auto glob2reg = [&in_curly] (char c) -> std::string {
      switch(c) {
      case '?':
        return ".";
      case '*':
        return ".*";
      case '{':
        ++in_curly;
        return "(";
      case '}':
        --in_curly;
        return ")";
      case ',':
        return in_curly > 0 ? "|" : ",";
      default:
        std::string ret{""};
        if(strchr("()^$|*+.\\", c)) {
          ret += '\\';
        }
        ret += c;
        return ret;
      }
    };

  glob_reg << "^";
  for(char c : glob) {
    glob_reg << glob2reg(c);
  }
  glob_reg << "$";
  return glob_reg.str();
}

inline bool regex_matches(std::string regex, const std::string& in, bool case_sensitive = false) {
  using namespace llvm;
  Regex r(regex, !case_sensitive ? Regex::IgnoreCase : Regex::NoFlags);
  return r.match(in);
}

/*
 inline std::vector<std::string> split_str(const std::string& input, const
 std::string& regex_match) {
 std::regex reg(regex_match);
 std::sregex_token_iterator last;
 std::sregex_token_iterator first(input.begin(), input.end(), reg, -1);
 return {first, last};
 }
 */
/*
 * Not part of the standard right now.
 * Copied from the proposal for the std (N3656)
 * see: https://isocpp.org/files/papers/N3656.txt
 */
template <class T>
struct _Unique_if {
  typedef std::unique_ptr<T> _Single_object;
};

template <class T>
struct _Unique_if<T[]> {
  typedef std::unique_ptr<T[]> _Unknown_bound;
};

template <class T, size_t N>
struct _Unique_if<T[N]> {
  typedef void _Known_bound;
};

template <class T, class... Args>
typename _Unique_if<T>::_Single_object make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename _Unique_if<T>::_Unknown_bound make_unique(size_t n) {
  typedef typename std::remove_extent<T>::type U;
  return std::unique_ptr<T>(new U[n]());
}

template <class T, class... Args>
typename _Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

} /* namespace util */
} /* namespace opov */

#endif  // CORE_UTILITY_UTIL_H
