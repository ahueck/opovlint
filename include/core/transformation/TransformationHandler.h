/*
 * TransformationHandler.h
 *
 *  Created on: Jul 29, 2014
 *      Author: ahueck
 */

#ifndef TRANSFORMATIONHANDLER_H_
#define TRANSFORMATIONHANDLER_H_

#include <clang/Rewrite/Core/Rewriter.h>

#include <external/IncludeDirectives.h>

#include <llvm/ADT/StringMap.h>

#include <string>

namespace clang {
class SourceManager;
class LangOptions;
namespace tooling {
class Replacement;
struct TranslationUnitReplacements;
} /* namespace tooling */
} /* namespace clang */

namespace opov {

typedef llvm::StringMap<clang::tooling::TranslationUnitReplacements> TUReplacementsMap;

class TransformationHandler {
 private:
  TUReplacementsMap replacements;
  std::string source;
  std::unique_ptr<IncludeDirectives> includes;
  clang::Rewriter rewriter;

 public:
  TransformationHandler();
  void setSource(const std::string& current);
  void initRewriter(clang::SourceManager& sm, const clang::LangOptions& langOpts);
  void setIncludeDirectives(IncludeDirectives* include);

  void addHeader(const std::string& header, clang::SourceLocation loc);
  void addReplacements(const clang::tooling::Replacement& replacement);
  void addReplacements(const std::vector<clang::tooling::Replacement>& replacements);
  void addReplacements(const clang::FixItHint& Hint);
  TUReplacementsMap& getAllReplacements();

  IncludeDirectives* getIncludeDirectives();
  clang::Rewriter& getRewriter();
  virtual ~TransformationHandler();
};

} /* namespace opov */

#endif /* TRANSFORMATIONHANDLER_H_ */
