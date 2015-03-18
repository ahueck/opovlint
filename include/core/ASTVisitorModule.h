/*
 * ASTVisitorModule.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef ASTVISITORMODULE_H_
#define ASTVISITORMODULE_H_

#include "AbstractModule.h"
#include "ModuleContext.h"

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace opov {

template<typename T>
class ASTVisitorModule: public AbstractModule,
		public clang::RecursiveASTVisitor<T> {

public:
	virtual void execute(ModuleContext* context) override;
	virtual ~ASTVisitorModule();
};

} /* namespace opov */

#include "ASTVisitorModule.hpp"

#endif /* ASTVISITORMODULE_H_ */
