/*
 * ASTMatcherModule.h
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#ifndef ASTMATCHERMODULE_H_
#define ASTMATCHERMODULE_H_

#include "AbstractModule.h"

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace opov {

class ASTMatcherModule : public opov::AbstractModule, public clang::ast_matchers::MatchFinder::MatchCallback {
 protected:
  clang::ast_matchers::MatchFinder finder;

 public:
  ASTMatcherModule();
  template <typename T>
  void addMatcher(const T &matcher);
  void init(const Configuration *config) override;
  virtual void setupMatcher() = 0;
  void execute(ModuleContext *context) override;
  ~ASTMatcherModule() override;
};

} /* namespace opov */

#include "ASTMatcherModule.hpp"

#endif /* ASTMATCHERMODULE_H_ */
