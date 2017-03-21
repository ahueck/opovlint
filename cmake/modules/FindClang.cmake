# Detect Clang libraries
#
# IN: 
#  - ${LLVM_LIBRARY_DIRS}: Required path to detect clang libs
#  - Alternative: ${CLANG_LIB_DIR}
# OUT:
#  - ${CLANG_LIBS}: contains all found Clang libraries for linking
#  - ${CLANG_FOUND}: true if (all) clang libraries were found
#
if(NOT LLVM_LIBRARY_DIRS)
  message(FATAL_ERROR "No LLVM library directory set.")
else()  
  macro(find_and_add_clang_lib _libname_)
    find_library(CLANG_${_libname_}_LIB 
      ${_libname_} 
      PATHS ${LLVM_LIBRARY_DIRS} ${CLANG_LIB_DIR}
      NO_DEFAULT_PATH
    )
    if(CLANG_${_libname_}_LIB)
      set(CLANG_LIBS ${CLANG_LIBS} ${CLANG_${_libname_}_LIB})
    else()
      message(WARNING "Could not find Clang library: " ${_libname_})
    endif()
  endmacro()

  find_and_add_clang_lib(clangFrontend)
  find_and_add_clang_lib(clangDriver)
  find_and_add_clang_lib(clangCodeGen)
  find_and_add_clang_lib(clangSema)
  find_and_add_clang_lib(clangAnalysis)
  find_and_add_clang_lib(clangRewrite)
  find_and_add_clang_lib(clangAST)
  find_and_add_clang_lib(clangParse)
  find_and_add_clang_lib(clangLex)
  find_and_add_clang_lib(clangBasic)
  find_and_add_clang_lib(clangARCMigrate)
  find_and_add_clang_lib(clangEdit)
  find_and_add_clang_lib(clangFrontendTool)
  find_and_add_clang_lib(clangRewrite)
  find_and_add_clang_lib(clangSerialization)
  find_and_add_clang_lib(clangTooling)
  find_and_add_clang_lib(clangASTMatchers)
  find_and_add_clang_lib(clangSema)
  find_and_add_clang_lib(clangToolingCore)
  find_and_add_clang_lib(clangTooling)

  if(CLANG_LIBS)
    set(CLANG_FOUND TRUE)
  else()
    set(CLANG_FOUND FALSE)
  endif()
endif()
