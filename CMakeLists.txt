CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OpOv)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(LSOURCES
src/core/Application.cpp
src/core/AbstractModule.cpp
src/core/ModuleContext.cpp
src/core/ASTMatcherModule.cpp
src/core/AbstractModuleConsumer.cpp
src/core/AbstractFactory.cpp
src/core/ConsoleReporter.cpp
src/core/CSVReporter.cpp
src/core/JSONConfiguration.cpp

include/external/IncludeDirectives.cpp
include/external/ReplacementHandling.cpp

src/core/TransformationHandler.cpp
src/core/IssueHandler.cpp
)

set(LHEADERS
include/core/Application.h
include/core/AbstractModule.h
include/core/ModuleContext.h
include/core/AbstractModuleConsumer.h
include/core/ASTVisitorModule.h
include/core/ASTMatcherModule.h
include/core/AbstractFactory.h
include/core/Configuration.h
include/core/IFactory.h
include/core/Module.h
include/core/Issue.h
include/core/IssueReporter.h
include/core/ConsoleReporter.h

include/core/JSONConfiguration.h
include/core/TransformationUtil.h

include/core/TransformationHandler.h
include/core/IssueHandler.h
)

set(PSOURCES 
src/AnalyzerFactory.cpp
src/ModuleConsumer.cpp

src/modules/ImplicitCondition.cpp
src/modules/ImplicitConditionMatcher.cpp
src/modules/ImplicitCastVisitor.cpp
src/modules/FieldDeclCollector.cpp
src/modules/UnionMatcher.cpp
src/modules/ExplicitCast.cpp
src/modules/ExplicitCastVisitor.cpp
src/modules/ConditionalAssgnMatcher.cpp
src/modules/ImplicitConversion.cpp
src/modules/ExplicitConstructor.cpp
src/modules/AllImplicitConversion.cpp
src/modules/GlobalScope.cpp
src/modules/GlobalScopeT.cpp
)

set(PHEADERS
include/AnalyzerFactory.h
include/ModuleConsumer.h

include/modules/ImplicitCondition.h
include/modules/ImplicitConditionMatcher.h
include/modules/ImplicitCastVisitor.h
include/modules/FieldDeclCollector.h
include/modules/UnionMatcher.h
include/modules/ExplicitCast.h
include/modules/ExplicitCastVisitor.h
include/modules/ConditionalAssgnMatcher.h
include/modules/ImplicitConversion.h
include/modules/ExplicitConstructor.h
include/modules/AllImplicitConversion.h
)

add_library(libopov ${LSOURCES} ${LHEADERS})
target_link_libraries(libopov "${TOOLCHAIN_LINK_LIB}")
add_library(stdimpl ${PSOURCES} ${PHEADERS})
target_link_libraries(stdimpl libopov)

add_executable(find-type${EXE_SUFFIX} src/main.cpp src/OpOvApp.cpp)
target_link_libraries(find-type${EXE_SUFFIX} "${TOOLCHAIN_LINK_LIB}" libopov stdimpl)

#add_subdirectory(test)
