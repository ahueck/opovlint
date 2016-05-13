CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
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


include_directories(${PROJECT_SOURCE_DIR}/include)

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
  src/core/issue/filter/UniqueFilter.cpp
  src/core/reporting/ConsoleReporter.cpp
  src/core/reporting/CSVReporter.cpp
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
target_link_libraries(libopov ${TOOLCHAIN_LINK_LIB})
add_library(stdimpl ${PSOURCES})
target_link_libraries(stdimpl libopov)

add_executable(find-type${EXE_SUFFIX} src/main.cpp src/OpOvApp.cpp)
target_link_libraries(find-type${EXE_SUFFIX} stdimpl)

if(MAKE_TEST)
  message(STATUS "Requested generation of tests.")
  add_subdirectory(test)
endif()
