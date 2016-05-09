#ifndef ASTVISITORMODULE_HPP_
#define ASTVISITORMODULE_HPP_

namespace opov {

template <typename T>
void ASTVisitorModule<T>::execute(const std::shared_ptr<ModuleContext>& context) {
  AbstractModule::execute(context);
  clang::RecursiveASTVisitor<T>::TraverseDecl(context->getASTContext().getTranslationUnitDecl());
}

template <typename T>
ASTVisitorModule<T>::~ASTVisitorModule() {
}

} /* namespace opov */

#endif
