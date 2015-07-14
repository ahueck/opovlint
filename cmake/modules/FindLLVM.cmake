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





##
## Setup for llvm-config executable, and important llvm vars
##
## Out:
##  Vars: ${LLVM_ROOT_DIR}
##  Exe: ${LLVM_CONFIG}
function(setup_llvm)
  set(llvm_config_names llvm-config-3.7
                        llvm-config-3.6
                        llvm-config-3.5
                        llvm-config)

  find_program(LLVM_CONFIG
      NAMES ${llvm_config_names}
      PATHS /usr/local/bin /opt/local/bin ${LLVM_ROOT_DIR}/bin NO_DEFAULT_PATH
      DOC "llvm-config executable.")

  if(LLVM_CONFIG)
    message(STATUS "llvm-config found: ${LLVM_CONFIG}")
  else()
    message(FATAL_ERROR "llvm-config NOT found. Search failed: ${llvm_config_names}")
  endif()

  execute_process(
    COMMAND ${LLVM_CONFIG} --prefix
    OUTPUT_VARIABLE LLVM_ROOT_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  set(LLVM_ROOT_DIR ${LLVM_ROOT_DIR} PARENT_SCOPE)
  set(LLVM_CONFIG ${LLVM_CONFIG} PARENT_SCOPE)
endfunction()

function(set_llvm_cppflags)
  execute_process(
    COMMAND ${LLVM_CONFIG} --cxxflags
    OUTPUT_VARIABLE llvm_cxxflags
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  string(REGEX REPLACE "(-D[^ ]*)|(-U[^ ]*)|(-I[^ ]*)" "" llvm_cxxflags ${llvm_cxxflags})
  set(LLVM_COMPILE_FLAGS ${llvm_cxxflags} PARENT_SCOPE)
endfunction()

function(set_llvm_lib_path)
  execute_process(
    COMMAND ${LLVM_CONFIG} --ldflags
    OUTPUT_VARIABLE llvm_ldflags
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(LLVM_LD_FLAGS ${llvm_ldflags} PARENT_SCOPE)
endfunction()

function(set_llvm_system_libs)
  execute_process(
    COMMAND ${LLVM_CONFIG} --system-libs
    OUTPUT_VARIABLE llvm_system_libs
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(LLVM_SYSTEM_LIBS ${llvm_system_libs} PARENT_SCOPE)
endfunction()


setup_llvm()

## Use existing CMake feature provided by LLVM
##  Vars (partial): ${LLVM_INCLUDE_DIRS}, ${LLVM_LIBRARY_DIRS}, ${LLVM_DEFINITIONS}
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT_DIR}/share/llvm/cmake")
include(LLVMConfig)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} ${LLVM_LIBRARY_DIRS}")

# FIXME does not work on this plattform (CLang 3.5.0)
#llvm_map_components_to_libnames(LLVM_LIBS support core)
set(LLVM_LIBS LLVMCore;LLVMSupport;LLVMOption;LLVMAsmParser;LLVMBitReader;LLVMIRReader;LLVMObject;LLVMMC;LLVMMCParser;LLVMCodeGen;LLVMExecutionEngine;LLVMInterpreter)
set_llvm_cppflags()
#set_llvm_lib_path()
set_llvm_system_libs()

return()



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
