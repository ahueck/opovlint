set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#setup of all necessary include/lib dirs for the development of a clang based tool
find_package(LLVM REQUIRED)
  message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} ${LLVM_LIBRARY_DIRS}")

#find_package(LLVM REQUIRED CONFIG)
#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

find_package(Clang REQUIRED)

if(NOT CLANG_FOUND)# OR NOT LLVM_FOUND)
	message(WARNING "Detection of Clang. Status: " CLANG_FOUND)
	#message(WARNING "Detection of LLVM. Status: " LLVM_FOUND)
	message(FATAL_ERROR "Aborting.")
else()
	include_directories(${LLVM_INCLUDE_DIRS})
	add_definitions(${LLVM_DEFINITIONS})
	link_directories(${LLVM_LIBRARY_DIRS})

	set(TOOLCHAIN_LINK_LIB ${CLANG_LIBS} ${LLVM_LIBS} ${LLVM_SYSTEM_LIBS}) 
	#include_directories(${LLVM_INCLUDE_DIR})
	#include_directories(${CLANG_INCLUDE_DIRS})
	#link_directories(${LLVM_LIB_DIR})
	#set(TOOLCHAIN_LINK_LIB ${CLANG_LIBS} ${LLVM_LIBS_CORE} ${LLVM_LDFLAGS}) 
	#set(CXX_ONLY_FLAGS ${CXX_ONLY_FLAGS} "${LLVM_COMPILE_FLAGS}")
endif()

# Misc. find out if clang compiler is used
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

#setup general compiler options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
	set(CXX_ONLY_FLAGS "${CXX_ONLY_FLAGS} ${LLVM_COMPILE_FLAGS} -fno-rtti") 

	# Release build
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	# Release build with debug symbols
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
	# Debug Build
	set(CMAKE_CXX_FLAGS_DEBUG "-Og")
	# Release build optimized for size
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

	set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${CXX_ONLY_FLAGS} ${CMAKE_CXX_FLAGS}")
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

message(STATUS "Build Type: " "${CMAKE_BUILD_TYPE}")
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
