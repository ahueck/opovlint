/*
 * LocalScope.h
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#ifndef LocalScope_H_
#define LocalScope_H_

#include <core/module/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {

class LocalScope : public opov::ASTMatcherModule {
private:
  std::string ns_s;
  bool keep_global;
 public:
  LocalScope();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~LocalScope();
};

} /* namespace module */
} /* namespace opov */

#endif /* LocalScope_H_ */
