function(add_lit_target target comment)
  cmake_parse_arguments(ARG "" "" "PARAMS;DEPENDS;ARGS" ${ARGN})
  message(STATUS "Adding llvm-lit target '${target}' depends on '${ARG_DEPENDS}'")
  set(LIT_ARGS "${ARG_ARGS} ${LLVM_LIT_ARGS}")
  separate_arguments(LIT_ARGS)
  if (NOT CMAKE_CFG_INTDIR STREQUAL ".")
    list(APPEND LIT_ARGS --param build_mode=${CMAKE_CFG_INTDIR})
  endif ()
  find_program(LIT_COMMAND 
               NAMES llvm-lit llvm-lit-4.0 llvm-lit-3.8 llvm-lit-3.7 llvm-lit-3.6)
  if(NOT LIT_COMMAND)
    message(WARNING "Could not find llvm-lit executable.")
  endif()
  list(APPEND LIT_COMMAND ${LIT_ARGS})
  foreach(param ${ARG_PARAMS})
    list(APPEND LIT_COMMAND --param ${param})
  endforeach()
  if (ARG_UNPARSED_ARGUMENTS)
    add_custom_target(${target}
      COMMAND ${LIT_COMMAND} ${ARG_UNPARSED_ARGUMENTS}
      COMMENT "${comment}"
      USES_TERMINAL
      )
  else()
    add_custom_target(${target}
      COMMAND ${CMAKE_COMMAND} -E echo "${target} does nothing, no tools built.")
    message(STATUS "${target} does nothing.")
  endif()
  if (ARG_DEPENDS)
    add_dependencies(${target} ${ARG_DEPENDS})
  endif()

  # Tests should be excluded from "Build Solution".
  set_target_properties(${target} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD ON)
endfunction()

# A function to add a set of lit test suites to be driven through 'check-*' targets.
function(add_lit_testsuite target comment)
  cmake_parse_arguments(ARG "" "" "PARAMS;DEPENDS;ARGS" ${ARGN})

  # EXCLUDE_FROM_ALL excludes the test ${target} out of check-all.
  if(NOT EXCLUDE_FROM_ALL)
    # Register the testsuites, params and depends for the global check rule, if any.
    set_property(GLOBAL APPEND PROPERTY OPOV_LIT_TESTSUITES ${ARG_UNPARSED_ARGUMENTS})
    set_property(GLOBAL APPEND PROPERTY OPOV_LIT_PARAMS ${ARG_PARAMS})
    set_property(GLOBAL APPEND PROPERTY OPOV_LIT_DEPENDS ${ARG_DEPENDS})
    set_property(GLOBAL APPEND PROPERTY OPOV_LIT_EXTRA_ARGS ${ARG_ARGS})
  endif()

  # Produce a specific suffixed check rule.
  add_lit_target(${target} ${comment}
    ${ARG_UNPARSED_ARGUMENTS}
    PARAMS ${ARG_PARAMS}
    DEPENDS ${ARG_DEPENDS}
    ARGS ${ARG_ARGS}
    )
endfunction()
