/*
 * ModuleContext.h
 *
 *  Created on: May 12, 2014
 *      Author: ahueck
 */

#ifndef CORE_MODULE_MODULECONTEXT_H
#define CORE_MODULE_MODULECONTEXT_H

#include <memory>
#include <vector>

namespace clang {
class ASTContext;
class SourceManager;
namespace tooling {
class Replacement;
} /* namespace tooling */
} /* namespace clang */

namespace opov {

class Configuration;
class Issue;
class IssueHandler;
class TransformationHandler;

class ModuleContext {
 protected:
  Configuration* config;
  std::vector<Issue*> issues;
  // std::vector<clang::tooling::Replacement> replacements;
  clang::ASTContext* context;
  IssueHandler* ihandler;
  TransformationHandler* thandler;
  std::string current_src;

 public:
  ModuleContext(Configuration* config, IssueHandler* ihandler, TransformationHandler* thandler);
  void initContext(clang::ASTContext* context);
  void setCurrentSource(const std::string& source);
  clang::ASTContext& getASTContext();
  clang::SourceManager& getSourceManager();
  IssueHandler& getIssueHandler();
  TransformationHandler& getTransformationHandler();
  virtual ~ModuleContext();
};

} /* namespace opov */

#endif  // CORE_MODULE_MODULECONTEXT_H
