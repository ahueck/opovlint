/*
 * ExplicitConstructor.h
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#ifndef EXPLICITCONSTRUCTOR_H_
#define EXPLICITCONSTRUCTOR_H_

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class ExplicitConstructor : public opov::ASTMatcherModule {
 private:
  bool warnOnTemplates;

 public:
  ExplicitConstructor();
  void setupOnce(const Configuration *config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~ExplicitConstructor() override;
};

} /* namespace module */
} /* namespace opov */

#endif /* EXPLICITCONSTRUCTOR_H_ */
