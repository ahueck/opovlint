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
  std::string type_s;
  std::string header_cast;
  std::string cast_stmt;
  // std::unique_ptr<ExplicitCastVisitor> visitor;

 public:
  ExplicitCast();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~ExplicitCast();
};

} /* namespace module */
} /* namespace opov */

#endif /* EXPLICITCAST_H_ */
