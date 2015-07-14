##
## Setup for llvm-config executable, and important llvm vars
##
## Out:
##  Var: 
##  Exe: ${LLVM_CONFIG}
function(setup_llvm)
  set(llvm_config_names llvm-config-3.7
                        llvm-config-3.6
                        llvm-config-3.5
                        llvm-config)

  find_program(LLVM_CONFIG
      NAMES ${llvm_config_names}
      PATHS /usr/local/bin /opt/local/bin ${LLVM_ROOT_DIR}/bin
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
  
  string(REGEX REPLACE "-D[^ ]*|-U[^ ]*|-I[^ ]*|-g[^ ]*|-[oO][^ ]*" "" llvm_cxxflags ${llvm_cxxflags})
  string(REGEX REPLACE "[ ]+" " " llvm_cxxflags ${llvm_cxxflags})
  set(LLVM_COMPILE_FLAGS ${llvm_cxxflags} PARENT_SCOPE)
endfunction()

function(set_llvm_lib_path)
  execute_process(
    COMMAND ${LLVM_CONFIG} --libdir
    OUTPUT_VARIABLE llvm_ldflags
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(LLVM_LIBRARY_DIRS ${llvm_ldflags} PARENT_SCOPE)
endfunction()

function(set_llvm_system_libs)
  execute_process(
    COMMAND ${LLVM_CONFIG} --system-libs
    OUTPUT_VARIABLE llvm_system_libs
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(LLVM_SYSTEM_LIBS ${llvm_system_libs} PARENT_SCOPE)
endfunction()

function(set_llvm_include_dir)
  execute_process(
    COMMAND ${LLVM_CONFIG} --includedir
    OUTPUT_VARIABLE llvm_includdir
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(LLVM_INCLUDE_DIRS ${llvm_includdir} PARENT_SCOPE)
endfunction()

function(set_llvm_definitions)
  execute_process(
    COMMAND ${LLVM_CONFIG} --cppflags
    OUTPUT_VARIABLE llvm_definitions
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  string(REGEX REPLACE "-I[^ ]*" "" llvm_definitions ${llvm_definitions})
  string(REGEX REPLACE "[ ]+" " " llvm_definitions ${llvm_definitions})
  set(LLVM_DEFINITIONS ${llvm_definitions} PARENT_SCOPE)
endfunction()

function(set_llvm_libs_all)
  execute_process(
    COMMAND ${LLVM_CONFIG} --libs
    OUTPUT_VARIABLE llvm_libs
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE " -" ";-" llvm_libs ${llvm_libs})
  set(LLVM_LIBS ${llvm_libs} PARENT_SCOPE)
endfunction()

setup_llvm()

## Use existing CMake feature provided by LLVM
##  Vars (partial): ${LLVM_INCLUDE_DIRS}, ${LLVM_LIBRARY_DIRS}, ${LLVM_DEFINITIONS}
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT_DIR}/share/llvm-3.7/cmake")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT_DIR}/share/llvm-3.6/cmake")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT_DIR}/share/llvm-3.5/cmake")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT_DIR}/share/llvm/cmake")
#message(STATUS ${CMAKE_MODULE_PATH})
#include(LLVMConfig)
# Alternative: seems buggy on some (binary) installs
#find_package(LLVM REQUIRED CONFIG)

# FIXME does not work on this plattform (CLang 3.5.0)
#llvm_map_components_to_libnames(LLVM_LIBS support core)

#set(LLVM_LIBS LLVMOption;LLVMAsmParser;LLVMBitReader;LLVMIRReader;LLVMObject;LLVMMC;LLVMMCParser;LLVMCodeGen;LLVMExecutionEngine;LLVMInterpreter;LLVMCore;LLVMSupport)
#set(LLVM_LIBS LLVMOption;LLVMAsmParser;LLVMBitReader;LLVMIRReader;LLVMObject;LLVMMCParser;LLVMInterpreter;LLVMExecutionEngine;LLVMMC;LLVMCore;LLVMSupport)
#set(LLVM_LIBS LLVMOption;LLVMAsmParser;LLVMBitReader;LLVMIRReader;LLVMObject;LLVMMCParser;LLVMMC;LLVMCore;LLVMSupport)
set(LLVM_LIBS LLVMIRReader;LLVMObject;LLVMMCParser;LLVMMC;LLVMBitReader;LLVMAsmParser;LLVMCore;LLVMOption;LLVMSupport)
#set_llvm_libs_all()
set_llvm_cppflags()
set_llvm_lib_path()
set_llvm_system_libs()
set_llvm_include_dir()
set_llvm_definitions()
