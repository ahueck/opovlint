/*
 * UnionMatcher.h
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef UNIONMATCHER_H_
#define UNIONMATCHER_H_

#include <core/ASTMatcherModule.h>

#include <string>
#include <memory>

namespace opov {
namespace module {

class FieldDeclCollector;

class UnionMatcher: public opov::ASTMatcherModule {
private:
	std::string type_s;
	std::unique_ptr<FieldDeclCollector> visitor;

public:
	UnionMatcher();
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	virtual std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~UnionMatcher();
};

} // namespace module
} /* namespace opov */

#endif /* UNIONMATCHER_H_ */
