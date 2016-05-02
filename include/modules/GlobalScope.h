/*
 * GlobalScope.h
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#ifndef MODULES_GLOBALSCOPE_H
#define MODULES_GLOBALSCOPE_H

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

class GlobalScope : public opov::ASTMatcherModule {
 public:
  GlobalScope();
  // virtual void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~GlobalScope() override;
};

} /* namespace module */
} /* namespace opov */

#endif  // MODULES_GLOBALSCOPE_H
