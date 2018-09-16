macro(add_function_test name)
  list(APPEND STUMPLESS_FUNCTION_TESTS function-test-${name})

  add_executable(function-test-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  if(MSVC)
    set(function_test_compile_flags "")
  else()
    set(function_test_compile_flags "-std=c++11")
  endif(MSVC)

  set_target_properties(function-test-${name}
    PROPERTIES
    OUTPUT_NAME function-test-${name}
    COMPILE_FLAGS "${function_test_compile_flags}"
  )

  target_link_libraries(function-test-${name}
    stumpless
    libgtest
  )

  target_include_directories(function-test-${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  add_test(NAME ${name}
    COMMAND function-test-${name}
  )
endmacro(add_function_test)

macro(add_performance_test name)
  list(APPEND STUMPLESS_PERFORMANCE_TESTS performance-test-${name})

  add_executable(performance-test-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  if(MSVC)
    target_link_libraries(performance-test-${name}
      stumpless
      libbenchmark
      Shlwapi.lib
    )
  else()
    target_link_libraries(performance-test-${name}
      stumpless
      libbenchmark
    )
  endif(MSVC)

  set_target_properties(performance-test-${name}
    PROPERTIES
    OUTPUT_NAME performance-test-${name}
  )

  target_include_directories(performance-test-${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )
endmacro(add_performance_test)
