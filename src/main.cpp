#include "OpOvApp.h"

#include <clang/Tooling/CommonOptionsParser.h>

static llvm::cl::OptionCategory OpOvLintCategory("opov options");

static llvm::cl::opt<std::string> Conf("config", llvm::cl::desc("Path to config file."), llvm::cl::init("conf.json"),
                                       llvm::cl::cat(OpOvLintCategory));
static llvm::cl::opt<std::string> Scalar("scalar-type", llvm::cl::desc("The scalar type to check."), llvm::cl::init(""),
                                         llvm::cl::cat(OpOvLintCategory));

int main(int argc, const char** argv) {
  int success = 0;
  if (argc > 1) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, OpOvLintCategory);
    Conf.hasArgStr();
    OpOvApp app(Conf.getValue());
    app.init();
    success = app.execute(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    app.cleanUp();
  }
  return success;
}
