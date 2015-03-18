# Detect CLANG
IF (NOT LLVM_INCLUDE_DIR OR NOT LLVM_LIB_DIR)
	message(FATAL_ERROR "No LLVM and Clang support requires LLVM")
else (NOT LLVM_INCLUDE_DIR OR NOT LLVM_LIB_DIR)
	MACRO(FIND_AND_ADD_CLANG_LIB _libname_)
		find_library(CLANG_${_libname_}_LIB ${_libname_} ${LLVM_LIB_DIR} ${CLANG_LIB_DIR})
		IF (CLANG_${_libname_}_LIB)
		   set(CLANG_LIBS ${CLANG_LIBS} ${CLANG_${_libname_}_LIB})
		ENDIF(CLANG_${_libname_}_LIB)
	ENDMACRO(FIND_AND_ADD_CLANG_LIB)

	set(CLANG_INCLUDE_DIRS ${CLANG_INCLUDE_DIRS} ${LLVM_INCLUDE_DIR})
	set(CLANG_INCLUDE_DIRS ${CLANG_INCLUDE_DIRS} ${CLANG_INCLUDE_DIR})

	FIND_AND_ADD_CLANG_LIB(clangFrontend)
	FIND_AND_ADD_CLANG_LIB(clangDriver)
	FIND_AND_ADD_CLANG_LIB(clangCodeGen)
	FIND_AND_ADD_CLANG_LIB(clangSema)
	FIND_AND_ADD_CLANG_LIB(clangChecker)
	FIND_AND_ADD_CLANG_LIB(clangAnalysis)
	FIND_AND_ADD_CLANG_LIB(clangRewrite)
	FIND_AND_ADD_CLANG_LIB(clangAST)
	FIND_AND_ADD_CLANG_LIB(clangParse)
	FIND_AND_ADD_CLANG_LIB(clangLex)
	FIND_AND_ADD_CLANG_LIB(clangBasic)
	FIND_AND_ADD_CLANG_LIB(clangARCMigrate)
	FIND_AND_ADD_CLANG_LIB(clangEdit)
	FIND_AND_ADD_CLANG_LIB(clangFrontendTool)
	FIND_AND_ADD_CLANG_LIB(clangRewrite)
	FIND_AND_ADD_CLANG_LIB(clangSerialization)
	FIND_AND_ADD_CLANG_LIB(clangTooling)
  	FIND_AND_ADD_CLANG_LIB(clangASTMatchers) #new
	FIND_AND_ADD_CLANG_LIB(clangStaticAnalyzerCheckers)
	FIND_AND_ADD_CLANG_LIB(clangStaticAnalyzerCore)
	FIND_AND_ADD_CLANG_LIB(clangStaticAnalyzerFrontend)
	FIND_AND_ADD_CLANG_LIB(clangSema)
	FIND_AND_ADD_CLANG_LIB(clangRewriteCore)

	# Note that I'm using -Wl,--{start|end}-group around the Clang libs; this is
	# because there are circular dependencies that make the correct order difficult
	# to specify and maintain. 
	#CLANG_LIBS := \
	#-Wl,--start-group \
	#-lclangAST \
	#-lclangAnalysis \
	#-lclangBasic \
	#-lclangDriver \
	#-lclangEdit \
	#-lclangFrontend \
	#-lclangFrontendTool \
	#-lclangLex \
	#-lclangParse \
	#-lclangSema \
	#-lclangEdit \
	#-lclangASTMatchers \
	#-lclangRewriteCore \
	#-lclangRewriteFrontend \
	#-lclangStaticAnalyzerFrontend \
	#-lclangStaticAnalyzerCheckers \
	#-lclangStaticAnalyzerCore \
	#-lclangSerialization \
	#-lclangTooling \
	#-Wl,--end-group

	IF (CLANG_LIBS)
	  set(CLANG_FOUND TRUE)
	ENDIF (CLANG_LIBS)

	IF (NOT CLANG_FOUND)
	  IF (CLANG_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find Clang.")
	  ENDIF (CLANG_FIND_REQUIRED)
	ENDIF (NOT CLANG_FOUND)
ENDIF (NOT LLVM_INCLUDE_DIR OR NOT LLVM_LIB_DIR)
