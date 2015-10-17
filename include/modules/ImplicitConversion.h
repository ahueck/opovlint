/*
 * ImplicitConversion.h
 *
 *  Created on: Jun 25, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONVERSION_H_
#define IMPLICITCONVERSION_H_

#include <core/module/ASTMatcherModule.h>

#include <string>
//#include <memory>

namespace opov {
namespace module {

class ImplicitConversion : public opov::ASTMatcherModule {
 public:
  ImplicitConversion();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~ImplicitConversion();
};

} /* namespace module */
} /* namespace opov */

#endif /* IMPLICITCONVERSION_H_ */
