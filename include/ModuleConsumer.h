/*
 * ModuleConsumer.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef MODULECONSUMER_H_
#define MODULECONSUMER_H_

#include <core/AbstractModuleConsumer.h>

namespace opov {

class Module;
class ModuleContext;

class ModuleConsumer: public AbstractModuleConsumer {
public:
	ModuleConsumer(Module* module,
			ModuleContext* mcontext);
	//virtual void HandleTranslationUnit(clang::ASTContext &Context) override;
	virtual ~ModuleConsumer();
};

} /* namespace opov */

#endif /* MODULECONSUMER_H_ */
