include_directories(${PROJECT_SOURCE_DIR}/test/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

#add_executable(test_implicitcond${EXE_SUFFIX} src/test_implicitcond.cpp)
#target_link_libraries(test_implicitcond${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_implicitcond_matcher${EXE_SUFFIX} src/test_implicitcond_matcher.cpp)
target_link_libraries(test_implicitcond_matcher${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_union_matcher${EXE_SUFFIX} src/test_union_matcher.cpp)
target_link_libraries(test_union_matcher${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_explicitcast${EXE_SUFFIX} src/test_explicitcast.cpp)
target_link_libraries(test_explicitcast${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_conditionalassgn${EXE_SUFFIX} src/test_conditionalassgn.cpp)
target_link_libraries(test_conditionalassgn${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_implicitconversion${EXE_SUFFIX} src/test_implicitconversion.cpp)
target_link_libraries(test_implicitconversion${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_system${EXE_SUFFIX} src/test_system.cpp)
target_link_libraries(test_system${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_explicitconstructor${EXE_SUFFIX} src/test_explicitconstructor.cpp)
target_link_libraries(test_explicitconstructor${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )

add_executable(test_allimplicitconversion${EXE_SUFFIX} src/test_allimplicitconversion.cpp)
target_link_libraries(test_allimplicitconversion${EXE_SUFFIX} ${TOOLCHAIN_LINK_LIB} libopov stdimpl )
