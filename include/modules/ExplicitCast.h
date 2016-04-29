/*
 * ExplicitCast.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ahueck
 */

#ifndef MODULES_EXPLICITCAST_H
#define MODULES_EXPLICITCAST_H

#include <core/module/ASTMatcherModule.h>

#include <string>
//#include <memory>

namespace opov {
namespace module {

class ExplicitCastVisitor;

class ExplicitCast : public opov::ASTMatcherModule {
 private:
  std::string header_cast;
  std::string stmt_cast;
  // std::unique_ptr<ExplicitCastVisitor> visitor;

 public:
  ExplicitCast();
  void setupOnce(const Configuration *config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult &result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~ExplicitCast() override;
};

} /* namespace module */
} /* namespace opov */

#endif // MODULES_EXPLICITCAST_H
