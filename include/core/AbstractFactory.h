/*
 * AbstractFactory.h
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

#include "IFactory.h"

#include <memory>
#include <vector>
#include <string>

namespace clang {
class CompilerInstance;
}
namespace llvm {
class StringRef;
}

namespace opov {

class Module;
class ModuleContext;
class Configuration;
//class IssueReporter;
class IssueHandler;
class TransformationHandler;

class AbstractFactory: public IFactory {
protected:
	Module* module;
	std::unique_ptr<ModuleContext> context;
	Configuration* config;
	std::string currentSource;
	//IssueReporter* reporter;
	IssueHandler* ihandler;
	TransformationHandler* thandler;

public:
	AbstractFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
	virtual bool handleBeginSource(clang::CompilerInstance &CI,
			llvm::StringRef Filename) override;
	virtual void handleEndSource() override;
	virtual void init() override;
	virtual void setModule(Module* m) override;
	virtual ~AbstractFactory();
};

} // namespace opov

#endif /* ABSTRACTFACTORY_H_ */
