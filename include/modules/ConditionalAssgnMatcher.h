/*
 * ConditionalAssgnMatcher.h
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#ifndef MODULES_CONDITIONALASSGNMATCHER_H
#define MODULES_CONDITIONALASSGNMATCHER_H

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

// class ConditionalAssgnVisitor;

class ConditionalAssgnMatcher : public opov::ASTMatcherModule {
 private:
  bool apply_transform;
  typedef struct {
    std::string type, variable, lhs, rhs, replacement;
  } conditional_data;

 public:
  ConditionalAssgnMatcher();
  void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~ConditionalAssgnMatcher() override;

 private:
  void toString(clang::ASTContext& ac, const clang::Expr* e, conditional_data& d);
  conditional_data buildReplacement(clang::ASTContext& ac, const clang::ConditionalOperator* e);
};

} /* namespace module */
} /* namespace opov */

#endif // MODULES_CONDITIONALASSGNMATCHER_H
