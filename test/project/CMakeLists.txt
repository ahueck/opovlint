CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OpOv)

include(${PROJECT_SOURCE_DIR}/ToolchainOptions.cmake)

set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(PHEADERS
    src/main4.h
)

add_executable(test${EXE_SUFFIX} src/main.cpp)
add_executable(test2${EXE_SUFFIX} src/main2.cpp)
add_executable(test3${EXE_SUFFIX} src/main3.cpp)
add_executable(test4${EXE_SUFFIX} src/main4.cpp ${PHEADERS})
add_executable(test5${EXE_SUFFIX} src/main5.cpp src/main6.cpp)
