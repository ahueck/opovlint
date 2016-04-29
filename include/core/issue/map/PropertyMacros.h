/*
 * Property.h
 *
 *  Created on: May 15, 2014
 *      Author:
 */

#ifndef CORE_ISSUE_MAP_PROPERTYMACROS_H
#define CORE_ISSUE_MAP_PROPERTYMACROS_H

namespace opov {

/**
 * \brief A macro that stringifies a macro token.
 *
 *  Stringify is boxed, because in particular cases just using the stringifiy
 *operator # alone will not work correctly
 *
 * \param A The void to process.
 */
#define DS_STRINGIFY_(A) #A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)

/**
 * \brief A macro for concatenating two Preprocessor Tokens
 *        this is used when A ## B does not work
 *
 * \param A.
 * \param B.
 */
#define DS_CONCAT(A, B) DS_CONCAT_(A, B)
#define DS_CONCAT_(A, B) A##B
#define DS_CONCAT__(A, B) DS_CONCAT_(A, B)

// helper for getting preceding type
#define DS_PRECEEDING_TYPE_TYPEDEF_HELPER_NAME(NAME) DS_CONCAT(__hiddenHelper_, NAME)

// inner macro for preceding type typedef
#define DS_PRECEEDING_TYPE_TYPEDEF_(NAME)                 \
  static DS_PRECEEDING_TYPE_TYPEDEF_HELPER_NAME(NAME)() { \
    return {};                                            \
  };                                                      \
  typedef decltype(DS_PRECEEDING_TYPE_TYPEDEF_HELPER_NAME(NAME)())

// macro for declaring a typedef on the preceding type inside a class instead of
// starting with the keyword typedef
// usage:
// class A{
//   std::string as mystring;
//}
// is equivalent to
// class A{
// typedef std::string mystring;
//
#define _as DS_PRECEEDING_TYPE_TYPEDEF_(DS_CONCAT(__, __LINE__))

} /* namespace opov */

#endif // CORE_ISSUE_MAP_PROPERTYMACROS_H
