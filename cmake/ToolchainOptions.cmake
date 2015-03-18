set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

#Setup of all necessary include/lib dirs for the development of a clang based tool
Find_Package(LLVM REQUIRED)
Find_Package(Clang REQUIRED)
IF (CLANG_FOUND AND LLVM_FOUND)
	include_directories(${LLVM_INCLUDE_DIR})
	link_directories(${LLVM_LIB_DIR})
	include_directories(${CLANG_INCLUDE_DIRS})
	set(TOOLCHAIN_LINK_LIB ${CLANG_LIBS} ${LLVM_LIBS_CORE} ${LLVM_LDFLAGS}) 
	set(CXX_ONLY_FLAGS ${CXX_ONLY_FLAGS} "${LLVM_COMPILE_FLAGS}")
ENDIF (CLANG_FOUND AND LLVM_FOUND)

# Misc. find out if clang compiler is used
IF (CMAKE_CXX_COMPILER MATCHES ".*clang")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
ENDIF (CMAKE_CXX_COMPILER MATCHES ".*clang")

#Setup general compiler options
IF (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
#Ignore the following. Most of it is defined through LLVM_COMPILE_FLAGS
	#set(COMMON_FLAGS ${COMMON_FLAGS} "-Wall -Wextra -pedantic -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual")  
	#set(CXX_ONLY_FLAGS ${CXX_ONLY_FLAGS} " -std=c++11")

	SET(CXX_ONLY_FLAGS "${CXX_ONLY_FLAGS} -fno-rtti -fexceptions") # -Wl,-rpath,/home/ahueck/gcc/4.8.3/lib64" Somehow required to make it link!
	SET(TOOLCHAIN_LINK_LIB "${TOOLCHAIN_LINK_LIB}" ) #-Wl,-rpath,/home/ahueck/gcc/4.8.3/lib64
	IF (ENABLE_SSE)
		set(COMMON_FLAGS "${COMMON_FLAGS} -msse4")
		message("Enabling SSE4.")
	ENDIF (ENABLE_SSE)

	IF (ENABLE_NATIVE)
		set(COMMON_FLAGS "${COMMON_FLAGS} -march=native")
		message("Enabling native modus.")
	ENDIF (ENABLE_NATIVE)

	# Release build
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	# Release build with debug symbols
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3 -DNDEBUG")
	# Debug Build
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

	set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${CXX_ONLY_FLAGS} ${CMAKE_CXX_FLAGS}")
ENDIF (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)

# set default build type
IF (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
ENDIF (NOT CMAKE_BUILD_TYPE)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
IF (CMAKE_BUILD_TYPE_UPPER STREQUAL "DEBUG")
	set(EXE_SUFFIX "Debug")
ELSEIF (CMAKE_BUILD_TYPE_UPPER STREQUAL "RELEASE")
	set(EXE_SUFFIX "")
ELSEIF (CMAKE_BUILD_TYPE_UPPER STREQUAL "RELWITHDEBINFO")
	set(EXE_SUFFIX "RelWithDebInfo")
ELSE (CMAKE_BUILD_TYPE_UPPER STREQUAL "DEBUG")
	set(EXE_SUFFIX "Unknown")
ENDIF (CMAKE_BUILD_TYPE_UPPER STREQUAL "DEBUG")

IF (CMAKE_BUILD_TYPE_UPPER MATCHES "RELWITHDEBINFO")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
ENDIF (CMAKE_BUILD_TYPE_UPPER MATCHES "RELWITHDEBINFO")
IF (CMAKE_BUILD_TYPE_UPPER MATCHES "DEBUG")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
ENDIF (CMAKE_BUILD_TYPE_UPPER MATCHES "DEBUG")
IF (CMAKE_BUILD_TYPE_UPPER MATCHES "RELEASE")
	set(ALL_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
ENDIF (CMAKE_BUILD_TYPE_UPPER MATCHES "RELEASE")

message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})
message(STATUS "Compiler Flags (Modus): " ${ALL_CXX_FLAGS})
message(STATUS "Compiler Flags (cmake): " ${CMAKE_CXX_FLAGS})
message(STATUS "Found Clang: " ${CLANG_INCLUDE_DIRS})
message(STATUS "Found LLVM: " ${LLVM_INCLUDE_DIR})
message(STATUS "Clang libs: " ${CLANG_LIBS})
message(STATUS "LLVM CXX flags: " ${LLVM_COMPILE_FLAGS})
message(STATUS "LLVM LD flags: " ${LLVM_LDFLAGS})
message(STATUS "LLVM core libs: " ${LLVM_LIBS_CORE})
message(STATUS "LLVM JIT libs: " ${LLVM_LIBS_JIT})
message(STATUS "LLVM JIT objs: " ${LLVM_LIBS_JIT_OBJECTS})

