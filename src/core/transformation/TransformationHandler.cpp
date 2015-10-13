/*
 * TransformationHandler.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: ahueck
 */

#include <core/transformation/TransformationHandler.h>
#include <core/logging/Logger.h>

#include <clang/Tooling/Refactoring.h>
#include <clang/Rewrite/Core/Rewriter.h>

namespace opov {

using namespace clang::tooling;

TransformationHandler::TransformationHandler()
    : replacements()
    , source("")
    , includes(nullptr) {
}

void TransformationHandler::setSource(const std::string& current) {
  source = current;
}

void TransformationHandler::initRewriter(clang::SourceManager& sm, const clang::LangOptions& langOpts) {
  rewriter.setSourceMgr(sm, langOpts);
}

void TransformationHandler::addReplacements(const clang::tooling::Replacement& replacement) {
  replacement.apply(rewriter);
  /*
  TranslationUnitReplacements& tunit = replacements[source];
  if (tunit.MainSourceFile.empty()) {
    tunit.MainSourceFile = source;
  }
  tunit.Replacements.push_back(replacement);
  */
}

void TransformationHandler::addHeader(const std::string& header, clang::SourceLocation loc) {
  addReplacements(includes->addAngledInclude(loc, header));
}

void TransformationHandler::addReplacements(const std::vector<clang::tooling::Replacement>& replacements) {
  for (auto& r : replacements) {
    addReplacements(r);
  }
}

void TransformationHandler::setIncludeDirectives(IncludeDirectives* include) {
  includes.reset(include);
}

IncludeDirectives* TransformationHandler::getIncludeDirectives() {
  return includes.get();
}

clang::Rewriter& TransformationHandler::getRewriter() {
  return rewriter;
}

TUReplacementsMap& TransformationHandler::getAllReplacements() {
  return replacements;
}

TransformationHandler::~TransformationHandler() {
}

} /* namespace opov */
