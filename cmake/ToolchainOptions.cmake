set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#setup of all necessary include/lib dirs for the development of a clang based tool
find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

if(NOT CLANG_FOUND OR NOT LLVM_FOUND)
	message(WARNING "Detection of Clang. Status: " CLANG_FOUND)
	message(WARNING "Detection of LLVM. Status: " LLVM_FOUND)
	message(FATAL_ERROR "Aborting.")
else()
	include_directories(${LLVM_INCLUDE_DIR})
	include_directories(${CLANG_INCLUDE_DIRS})
	link_directories(${LLVM_LIB_DIR})
	set(TOOLCHAIN_LINK_LIB ${CLANG_LIBS} ${LLVM_LIBS_CORE} ${LLVM_LDFLAGS}) 
	set(CXX_ONLY_FLAGS ${CXX_ONLY_FLAGS} "${LLVM_COMPILE_FLAGS}")
endif()

# Misc. find out if clang compiler is used
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

#setup general compiler options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
#Ignore the following. Most of it is defined through LLVM_COMPILE_FLAGS
	#set(COMMON_FLAGS ${COMMON_FLAGS} "-Wall -Wextra -pedantic -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual")  
	#set(CXX_ONLY_FLAGS ${CXX_ONLY_FLAGS} " -std=c++11")

	set(CXX_ONLY_FLAGS "${CXX_ONLY_FLAGS} -fno-rtti -fexceptions") # -Wl,-rpath,/home/ahueck/gcc/4.8.3/lib64" Somehow required to make it link!
	set(TOOLCHAIN_LINK_LIB "${TOOLCHAIN_LINK_LIB}" ) #-Wl,-rpath,/home/ahueck/gcc/4.8.3/lib64
	
	if(ENABLE_SSE)
		set(COMMON_FLAGS "${COMMON_FLAGS} -msse4")
		message(STATUS "Enabling SSE4.")
	endif()

	if(ENABLE_NATIVE)
		set(COMMON_FLAGS "${COMMON_FLAGS} -march=native")
		message(STATUS "Enabling native modus.")
	endif()

	# Release build
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	# Release build with debug symbols
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
	# Debug Build
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

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
	set(EXE_SUFFIX "RelWithDebInfo")
else()
	message(WARNING "Unknown exe suffix found.")
	set(EXE_SUFFIX "Unknown")
endif()

if(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
elseif(CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
else()
	# Fallback to Debug
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif()

message("Build Type: " ${CMAKE_BUILD_TYPE})
message("Compiler Flags (Modus): " ${ALL_CXX_FLAGS})
message("Compiler Flags (cmake): " ${CMAKE_CXX_FLAGS})
message("Found Clang: " ${CLANG_INCLUDE_DIRS})
message("Found LLVM: " ${LLVM_INCLUDE_DIR})
message("Clang libs: " ${CLANG_LIBS})
message("LLVM CXX flags: " ${LLVM_COMPILE_FLAGS})
message("LLVM LD flags: " ${LLVM_LDFLAGS})
message("LLVM core libs: " ${LLVM_LIBS_CORE})
message("LLVM JIT libs: " ${LLVM_LIBS_JIT})
message("LLVM JIT objs: " ${LLVM_LIBS_JIT_OBJECTS})
