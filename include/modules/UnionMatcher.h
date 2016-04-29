/*
 * UnionMatcher.h
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef UNIONMATCHER_H_
#define UNIONMATCHER_H_

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

class UnionMatcher : public opov::ASTMatcherModule {
 public:
  UnionMatcher();
  //virtual void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~UnionMatcher() override;
};

} /* namespace module */
} /* namespace opov */

#endif /* UNIONMATCHER_H_ */
