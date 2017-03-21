include_directories(${PROJECT_SOURCE_DIR}/test/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CATCH_INCLUDE})

set(unit_test_names implicitcond_matcher union_matcher explicitcast conditionalassgn implicitconversion system explicitconstructor allimplicitconversion globalscope ifelse)

foreach(name ${unit_test_names})
  add_executable(test_${name}${EXE_SUFFIX} src/test_${name}.cpp)
  target_link_libraries(test_${name}${EXE_SUFFIX}  stdimpl )
  add_test(NAME ${name} COMMAND test_${name}${EXE_SUFFIX})
endforeach()

set(OPOVLINT_TEST_DEPS find-type${EXE_SUFFIX})

add_lit_testsuite(check-oolint "Running the OO-Lint regression tests"
  ${CMAKE_CURRENT_SOURCE_DIR}/collection
  PARAMS ${OPOVLINT_TEST_PARAMS}
  DEPENDS ${OPOVLINT_TEST_DEPS}
  ARGS ${OPOVLINT_TEST_EXTRA_ARGS}
  )
