/*
 * ExplicitCast.h
 *
 *  Created on: Jun 19, 2014
 *      Author: ahueck
 */

#ifndef EXPLICITCAST_H_
#define EXPLICITCAST_H_

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

#endif /* EXPLICITCAST_H_ */
