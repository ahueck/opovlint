/*
 * IfElseAssign.h
 *
 *  Created on: Oct 15, 2015
 *      Author: ahueck
 */

#ifndef MODULES_IFELSEASSIGN_H
#define MODULES_IFELSEASSIGN_H

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class IfElseAssign : public opov::ASTMatcherModule {
private:
  bool apply_transform;
 public:
  IfElseAssign();
  void setupOnce(const Configuration* config) override;
  void setupMatcher() override;
  void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  std::string moduleName() override;
  std::string moduleDescription() override;
  ~IfElseAssign() override;

 private:
  std::string toString(clang::ASTContext& ac, const clang::IfStmt* stmt, const clang::BinaryOperator* then,
                       const clang::BinaryOperator* else_e);
};

} /* namespace module */
} /* namespace opov */

#endif // MODULES_IFELSEASSIGN_H
