include_directories(${PROJECT_SOURCE_DIR}/test/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CATCH_INCLUDE})

set(unit_test_names implicitcond_matcher union_matcher explicitcast conditionalassgn implicitconversion system explicitconstructor allimplicitconversion globalscope ifelse)

add_custom_target(unit-tests
  COMMENT "Target to compile all unit tests"
)

foreach(name ${unit_test_names})
  add_executable(test_${name}${EXE_SUFFIX} src/test_${name}.cpp)
  target_link_libraries(test_${name}${EXE_SUFFIX}  stdimpl)
  add_test(NAME ${name} COMMAND test_${name}${EXE_SUFFIX})
  add_dependencies(unit-tests test_${name}${EXE_SUFFIX})
endforeach()

 add_executable(test_core${EXE_SUFFIX} src/test_core.cpp)
 target_link_libraries(test_core${EXE_SUFFIX} opov)
 add_test(NAME core COMMAND test_core${EXE_SUFFIX})
 add_dependencies(unit-tests test_core${EXE_SUFFIX})

