/*
 * AllImplicitConversion.h
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#ifndef MODULES_ALLIMPLICITCONVERSION_H
#define MODULES_ALLIMPLICITCONVERSION_H

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class AllImplicitConversion : public opov::ASTMatcherModule {
 public:
  AllImplicitConversion();
  // virtual void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~AllImplicitConversion() override;
};

} /* namespace module */
} /* namespace opov */

#endif  // MODULES_ALLIMPLICITCONVERSION_H
