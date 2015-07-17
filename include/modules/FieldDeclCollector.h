/*
 * FieldDeclCollector.h
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef FIELDDECLCOLLECTOR_H_
#define FIELDDECLCOLLECTOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

#include <string>
#include <vector>

namespace opov {
namespace module {

class FieldDeclCollector : public clang::RecursiveASTVisitor<FieldDeclCollector> {
 private:
  std::vector<clang::FieldDecl*> violations;
  const std::string& type;

 public:
  FieldDeclCollector(const std::string& type = "");
  std::vector<clang::FieldDecl*> extractDecl(clang::CXXRecordDecl* unionDecl);
  bool VisitFieldDecl(clang::FieldDecl* decl);
  virtual ~FieldDeclCollector();
};

} /* namespace module */
} /* namespace opov */

#endif /* FIELDDECLCOLLECTOR_H_ */
