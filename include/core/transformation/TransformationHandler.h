/*
 * TransformationHandler.h
 *
 *  Created on: Jul 29, 2014
 *      Author: ahueck
 */

#ifndef TRANSFORMATIONHANDLER_H_
#define TRANSFORMATIONHANDLER_H_

#include <external/IncludeDirectives.h>

#include <llvm/ADT/StringMap.h>

#include <string>

namespace clang {
namespace tooling {
class Replacement;
class TranslationUnitReplacements;
}
}

namespace opov {

typedef llvm::StringMap<clang::tooling::TranslationUnitReplacements> TUReplacementsMap;

class TransformationHandler {
 private:
  TUReplacementsMap replacements;
  std::string source;
  std::unique_ptr<IncludeDirectives> includes;

 public:
  TransformationHandler();
  void setSource(const std::string& current);
  void addReplacements(const clang::tooling::Replacement& replacement);
  void addReplacements(const std::vector<clang::tooling::Replacement>& replacements);
  TUReplacementsMap& getAllReplacements();
  void setIncludeDirectives(IncludeDirectives* include);
  IncludeDirectives* getIncludeDirectives();
  virtual ~TransformationHandler();
};

} /* namespace opov */

#endif /* TRANSFORMATIONHANDLER_H_ */
