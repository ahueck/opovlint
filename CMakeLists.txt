CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OpOv)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

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

src/core/reporting/ConsoleReporter.cpp
src/core/reporting/CSVReporter.cpp

src/core/transformation/TransformationHandler.cpp
)


set(PSOURCES 
src/AnalyzerFactory.cpp
src/ModuleConsumer.cpp

src/modules/ImplicitConditionMatcher.cpp
src/modules/FieldDeclCollector.cpp
src/modules/UnionMatcher.cpp
src/modules/ExplicitCast.cpp
src/modules/ConditionalAssgnMatcher.cpp
src/modules/ImplicitConversion.cpp
src/modules/ExplicitConstructor.cpp
src/modules/AllImplicitConversion.cpp
src/modules/GlobalScopeT.cpp
)

add_library(libopov ${LSOURCES})
target_link_libraries(libopov ${TOOLCHAIN_LINK_LIB})
add_library(stdimpl ${PSOURCES})
target_link_libraries(stdimpl libopov)

add_executable(find-type${EXE_SUFFIX} src/main.cpp src/OpOvApp.cpp)
target_link_libraries(find-type${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl)

add_subdirectory(test)
