/*
 * ConditionalAssgnMatcher.h
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#ifndef CONDITIONALASSGNMATCHER_H_
#define CONDITIONALASSGNMATCHER_H_

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

// class ConditionalAssgnVisitor;

class ConditionalAssgnMatcher : public opov::ASTMatcherModule {
 private:
  unsigned var_counter;
  typedef struct { std::string type, variable, lhs, rhs, replacement; } conditional_data;

 public:
  ConditionalAssgnMatcher();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~ConditionalAssgnMatcher();

 private:
  void toString(clang::ASTContext& ac, const clang::Expr* e, conditional_data& d, int counter = 0);
  conditional_data buildReplacement(clang::ASTContext& ac, const clang::ConditionalOperator* e);
};

} /* namespace module */
} /* namespace opov */

#endif /* CONDITIONALASSGNMATCHER_H_ */
