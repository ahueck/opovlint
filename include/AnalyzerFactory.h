/*
 * AnalyzerFactory.h
 *
 *  Created on: May 7, 2014
 *      Author: ahueck
 */

#ifndef ANALYZERFACTORY_H_
#define ANALYZERFACTORY_H_

#include <core/AbstractFactory.h>
#include <core/AbstractModuleConsumer.h>

namespace opov {

class AnalyzerFactory : public AbstractFactory {
 private:
 public:
  AnalyzerFactory(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
  virtual bool handleBeginSource(clang::CompilerInstance& CI, llvm::StringRef Filename) override;
  virtual void handleEndSource() override;
  virtual clang::ASTConsumer* newASTConsumer() override;
  virtual ~AnalyzerFactory();
};

} /* namespace opov */

#endif /* ANALYZERFACTORY_H_ */
