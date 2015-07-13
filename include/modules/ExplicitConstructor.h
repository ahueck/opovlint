/*
 * ExplicitConstructor.h
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#ifndef EXPLICITCONSTRUCTOR_H_
#define EXPLICITCONSTRUCTOR_H_

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class ExplicitConstructor: public opov::ASTMatcherModule {
private:
	bool warnOnTemplates;

public:
	ExplicitConstructor();
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	virtual std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~ExplicitConstructor();
};

} /* namespace module */
} /* namespace opov */

#endif /* EXPLICITCONSTRUCTOR_H_ */
