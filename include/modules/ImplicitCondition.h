/*
 * ImplicitCondition.h
 *
 *  Created on: May 14, 2014
 *      Author: ahueck
 */

#ifndef IMPLICITCONDITION_H_
#define IMPLICITCONDITION_H_

#include <core/ASTMatcherModule.h>

#include <memory>
#include <vector>

namespace opov {

namespace module {

class ImplicitCastVisitor;

class ImplicitCondition: public ASTMatcherModule {
private:
	std::string type_s;
	std::unique_ptr<ImplicitCastVisitor> visitor;
	//void report(const std::vector<clang::Expr*>& issues);

public:
	ImplicitCondition();
	void execute(ModuleContext* context) override;
	virtual void setupOnce(const Configuration* config) override;
	virtual void setupMatcher() override;
	virtual void run(
			const clang::ast_matchers::MatchFinder::MatchResult& result)
					override;
	std::string moduleName() override;
	virtual std::string moduleDescription() override;
	virtual ~ImplicitCondition();
};

} // namespace module
} // namespace opov

#endif /* IMPLICITCONDITION_H_ */
