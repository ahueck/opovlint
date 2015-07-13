# Detect LLVM and set various variable to link against the different component of LLVM
#
# NOTE: This is a modified version of the module originally found in the OpenGTL project
# at www.opengtl.org
#
# LLVM_BIN_DIR : directory with LLVM binaries
# LLVM_LIB_DIR : directory with LLVM library
# LLVM_INCLUDE_DIR : directory with LLVM include
#
# LLVM_COMPILE_FLAGS : compile flags needed to build a program using LLVM headers
# LLVM_LDFLAGS : ldflags needed to link
# LLVM_LIBS_CORE : ldflags needed to link against a LLVM core library
# LLVM_LIBS_JIT : ldflags needed to link against a LLVM JIT
# LLVM_LIBS_JIT_OBJECTS : objects you need to add to your source when using LLVM JIT

if(LLVM_INCLUDE_DIR)
  set(LLVM_FOUND TRUE)
else()
	find_program(LLVM_CONFIG_EXECUTABLE
	  NAMES llvm-config-3.5 llvm-config 
	  PATHS /usr/local/bin /opt/local/bin
	)

	if(NOT LLVM_CONFIG_EXECUTABLE)
		message(FATAL_ERROR "Could not find program llvm-config.")
	endif()

	macro(find_llvm_libs LLVM_CONFIG_EXECUTABLE _libname_ LIB_VAR OBJECT_VAR)
	  exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --libs ${_libname_}  OUTPUT_VARIABLE ${LIB_VAR} )
	  string(REGEX MATCHALL "[^ ]*[.]o[ $]"  ${OBJECT_VAR} ${${LIB_VAR}})
	  separate_arguments(${OBJECT_VAR})
	  string(REGEX REPLACE "[^ ]*[.]o[ $]" ""  ${LIB_VAR} ${${LIB_VAR}})
	endmacro()

	exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --bindir OUTPUT_VARIABLE LLVM_BIN_DIR )
	exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --libdir OUTPUT_VARIABLE LLVM_LIB_DIR )
	#MESSAGE(STATUS "LLVM lib dir: " ${LLVM_LIB_DIR})
	exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --includedir OUTPUT_VARIABLE LLVM_INCLUDE_DIR )
	exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --cxxflags  OUTPUT_VARIABLE LLVM_COMPILE_FLAGS )
	execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --ldflags  OUTPUT_VARIABLE LLVM_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
	#--system-libs is new in llvm 3.5
	execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --system-libs  OUTPUT_VARIABLE LLVM_LDFLAGS2 OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
	string(REPLACE "\n" " " LLVM_LDFLAGS ${LLVM_LDFLAGS} " " ${LLVM_LDFLAGS2})
	string(REGEX REPLACE "(\n|\r\n)$" "" LLVM_LDFLAGS "${LLVM_LDFLAGS}")
	exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --libs      OUTPUT_VARIABLE LLVM_LIBS_CORE )
	find_llvm_libs(${LLVM_CONFIG_EXECUTABLE} "jit native" LLVM_LIBS_JIT LLVM_LIBS_JIT_OBJECTS )
	#STRING(REPLACE " -lLLVMCore -lLLVMSupport -lLLVMSystem" "" LLVM_LIBS_JIT ${LLVM_LIBS_JIT_RAW})

	if(LLVM_INCLUDE_DIR)
	  set(LLVM_FOUND TRUE)
	else()
		set(LLVM_FOUND FALSE)
	endif()
endif()
