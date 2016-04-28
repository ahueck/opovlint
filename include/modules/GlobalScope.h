/*
 * GlobalScope.h
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#ifndef GLOBALSCOPE_H_
#define GLOBALSCOPE_H_

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

class GlobalScope : public opov::ASTMatcherModule {
 public:
  GlobalScope();
  //virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~GlobalScope();
};

} /* namespace module */
} /* namespace opov */

#endif /* GLOBALSCOPE_H_ */
