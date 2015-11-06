/*
 * IfElseAssign.h
 *
 *  Created on: Oct 15, 2015
 *      Author: ahueck
 */

#ifndef IFELSEASSIGN_H_
#define IFELSEASSIGN_H_

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class IfElseAssign : public opov::ASTMatcherModule {
private:
  bool apply_transform;
 public:
  IfElseAssign();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~IfElseAssign();

 private:
  std::string toString(clang::ASTContext& ac, const clang::IfStmt* stmt, const clang::BinaryOperator* then,
                       const clang::BinaryOperator* else_e);
};

} /* namespace module */
} /* namespace opov */

#endif /* IFELSEASSIGN_H_ */
