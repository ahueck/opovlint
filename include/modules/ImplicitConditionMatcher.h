/*
 * ImplicitConditionMatcher.h
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONDITIONMATCHER_H_
#define IMPLICITCONDITIONMATCHER_H_

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {
class ImplicitConditionMatcher : public opov::ASTMatcherModule {
 public:
  ImplicitConditionMatcher();
  void setupOnce(const Configuration *config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~ImplicitConditionMatcher() override;
};

} /* namespace module */
} /* namespace opov */

#endif /* IMPLICITCONDITIONMATCHER_H_ */
