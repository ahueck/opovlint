/*
 * UnionMatcher.h
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef MODULES_UNIONMATCHER_H
#define MODULES_UNIONMATCHER_H

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class UnionMatcher : public opov::ASTMatcherModule {
 public:
  UnionMatcher();
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~UnionMatcher() override;
};

} /* namespace module */
} /* namespace opov */

#endif  // MODULES_UNIONMATCHER_H
