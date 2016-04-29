/*
 * AllImplicitConversion.h
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#ifndef ALLIMPLICITCONVERSION_H_
#define ALLIMPLICITCONVERSION_H_

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class AllImplicitConversion : public opov::ASTMatcherModule {
 public:
  AllImplicitConversion();
  //virtual void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~AllImplicitConversion() override;
};

} /* namespace module */
} /* namespace opov */

#endif /* ALLIMPLICITCONVERSION_H_ */
