CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(OpOv)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)

if(NOT BINARY_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINARY_OUTPUT_DIRECTORY})
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message(STATUS "Binary output directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(EXTERNALPACKAGES ${PROJECT_SOURCE_DIR}/externalpackages)
add_subdirectory(${EXTERNALPACKAGES})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${JSONPP_INCLUDE})

set(LSOURCES
  src/core/Application.cpp
  src/core/module/AbstractModule.cpp
  src/core/module/ModuleContext.cpp
  src/core/module/ASTMatcherModule.cpp
  src/core/AbstractModuleConsumer.cpp
  src/core/AbstractFactory.cpp
  src/core/configuration/JSONConfiguration.cpp
  include/external/IncludeDirectives.cpp
  include/external/ReplacementHandling.cpp
  src/core/issue/IssueHandler.cpp
  src/core/reporting/FormattedReporter.cpp
  src/core/transformation/TransformationHandler.cpp
)

set(PSOURCES 
  src/AnalyzerFactory.cpp
  src/ModuleConsumer.cpp
  src/modules/ImplicitConditionMatcher.cpp
  src/modules/UnionMatcher.cpp
  src/modules/ExplicitCast.cpp
  src/modules/ConditionalAssgnMatcher.cpp
  src/modules/ImplicitConversion.cpp
  src/modules/ExplicitConstructor.cpp
  src/modules/AllImplicitConversion.cpp
  src/modules/GlobalScope.cpp
  src/modules/IfElseAssign.cpp
  src/modules/LocalScope.cpp
)

add_library(libopov ${LSOURCES})
target_link_libraries(libopov ${TOOLCHAIN_LINK_LIB} jsonpp)
add_library(stdimpl ${PSOURCES})
target_link_libraries(stdimpl libopov)

add_executable(find-type${EXE_SUFFIX} src/main.cpp src/OpOvApp.cpp)
target_link_libraries(find-type${EXE_SUFFIX} stdimpl)

add_custom_target(executable
  COMMENT "Target to compile find-type executable"
  DEPENDS find-type${EXE_SUFFIX}
)

set(OPOVLINT_TEST_DEPS find-type${EXE_SUFFIX})
add_lit_testsuite(check-oolint "Running the OO-Lint regression tests"
  ${CMAKE_CURRENT_SOURCE_DIR}/test/collection
  PARAMS ${OPOVLINT_TEST_PARAMS}
  DEPENDS ${OPOVLINT_TEST_DEPS}
  ARGS ${OPOVLINT_TEST_EXTRA_ARGS}
)

enable_testing()
add_subdirectory(test)
