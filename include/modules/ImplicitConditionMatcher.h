/*
 * ImplicitConditionMatcher.h
 *
 *  Created on: May 26, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONDITIONMATCHER_H_
#define IMPLICITCONDITIONMATCHER_H_

#include <core/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {
class ImplicitConditionMatcher: public opov::ASTMatcherModule {
private:
	std::string type_s;

public:
	ImplicitConditionMatcher();
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	virtual std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~ImplicitConditionMatcher();
};

} // namespace module
} /* namespace opov */

#endif /* IMPLICITCONDITIONMATCHER_H_ */
