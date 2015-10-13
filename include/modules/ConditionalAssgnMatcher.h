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
//#include <memory>

namespace opov {
namespace module {

// class ConditionalAssgnVisitor;

class ConditionalAssgnMatcher : public opov::ASTMatcherModule {
public:
  ConditionalAssgnMatcher();
  virtual void setupOnce(const Configuration* config) override;
  virtual void setupMatcher() override;
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
  virtual std::string moduleName() override;
  virtual std::string moduleDescription() override;
  virtual ~ConditionalAssgnMatcher();
};

} /* namespace module */
} /* namespace opov */

#endif /* CONDITIONALASSGNMATCHER_H_ */
