/*
 * ImplicitConversion.h
 *
 *  Created on: Jun 25, 2014
 *      Author: ahueck
 */

#ifndef MODULES_IMPLICITCONVERSION_H
#define MODULES_IMPLICITCONVERSION_H

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

class ImplicitConversion : public opov::ASTMatcherModule {
 public:
  ImplicitConversion();
  // virtual void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~ImplicitConversion() override;
};

} /* namespace module */
} /* namespace opov */

#endif  // MODULES_IMPLICITCONVERSION_H
