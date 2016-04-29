/*
 * LocalScope.h
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#ifndef MODULES_LOCALSCOPE_H
#define MODULES_LOCALSCOPE_H

#include <core/module/ASTMatcherModule.h>

#include <string>
#include <vector>

namespace opov {
namespace module {

class LocalScope : public opov::ASTMatcherModule {
private:
  std::string ns_s;
  bool keep_global;
  std::vector<std::string> functions_wl;
 public:
  LocalScope();
  void setupOnce(const Configuration *config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~LocalScope() override;
};

} /* namespace module */
} /* namespace opov */

#endif // MODULES_LOCALSCOPE_H
