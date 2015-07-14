set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#setup of all necessary include/lib dirs for the development of a clang based tool
find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

if(NOT CLANG_FOUND)
	message(FATAL_ERROR "Detection of Clang failed.")
else()
	include_directories(${LLVM_INCLUDE_DIRS})
	add_definitions(${LLVM_DEFINITIONS})
	link_directories(${LLVM_LIBRARY_DIRS})
	set(TOOLCHAIN_LINK_LIB ${CLANG_LIBS} ${LLVM_LIBS} ${LLVM_SYSTEM_LIBS}) 
endif()

# Misc. find out if clang compiler is used
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

#setup general compiler options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    # Ignore for now: ${LLVM_COMPILE_FLAGS}
	set(CXX_ONLY_FLAGS "-std=c++11 -Wall -Wextra -pedantic -Wunreachable-code -Wwrite-strings -Wpointer-arith -Wcast-align -Wcast-qual -Wno-unused-parameter -fPIC -fexceptions -fno-rtti ${CXX_ONLY_FLAGS}")

	# Release build
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	# Release build with debug symbols
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
	# Debug Build
	set(CMAKE_CXX_FLAGS_DEBUG "-Og")
	# Release build optimized for size
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

	set(CMAKE_CXX_FLAGS  "${CXX_ONLY_FLAGS} ${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")
endif()

# set default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)

if(CMAKE_BUILD_TYPE_UPPER STREQUAL "DEBUG")
	set(EXE_SUFFIX "Debug")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(EXE_SUFFIX "")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(EXE_SUFFIX "RelDebg")
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "MINSIZEREL")
	set(EXE_SUFFIX "RelMin")
else()
	message(WARNING "Unknown exe suffix found.")
	set(EXE_SUFFIX "Unknown")
endif()

if(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "MINSIZEREL")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_MINSIZEREL})
else()
	# Fallback to Debug
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler Flags (Modus): ${ALL_CXX_FLAGS}")
message(STATUS "Compiler Flags (cmake): ${CMAKE_CXX_FLAGS}")
message(STATUS "Found Clang: ${CLANG_FOUND}")
message(STATUS "Found LLVM: ${LLVM_INCLUDE_DIR}")
message(STATUS "LLVM root directory: ${LLVM_ROOT_DIR}")
message(STATUS "LLVM CXX flags: ${LLVM_COMPILE_FLAGS}")
message(STATUS "LLVM LD flags: ${LLVM_LIBRARY_DIRS}")
message(STATUS "LLVM system libs: ${LLVM_SYSTEM_LIBS}")
message(STATUS "LLVM libs: ${LLVM_LIBS}")
message(STATUS "Clang libs: ${CLANG_LIBS}")
