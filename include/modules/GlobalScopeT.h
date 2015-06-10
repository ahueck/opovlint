/*
 * GlobalScopeT.h
 *
 *  Created on: June 09, 2015
 *      Author: ahueck
 */

#ifndef GLOBALSCOPET_H_
#define GLOBALSCOPET_H_

#include <core/ASTMatcherModule.h>

#include <string>

namespace opov {
namespace module {
class GlobalScopeT: public opov::ASTMatcherModule {
private:
	std::string type_s;

public:
	GlobalScopeT();
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	virtual std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~GlobalScopeT();
};

} // namespace module
} /* namespace opov */

#endif /* GLOBALSCOPET_H_ */
