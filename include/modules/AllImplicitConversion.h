/*
 * AllImplicitConversion.h
 *
 *  Created on: Jul 18, 2014
 *      Author: ahueck
 */

#ifndef ALLIMPLICITCONVERSION_H_
#define ALLIMPLICITCONVERSION_H_

#include <core/module/ASTMatcherModule.h>

namespace opov {
namespace module {

class AllImplicitConversion: public opov::ASTMatcherModule {
public:
	AllImplicitConversion();
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	virtual std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~AllImplicitConversion();
};

} /* namespace module */
} /* namespace opov */

#endif /* ALLIMPLICITCONVERSION_H_ */
