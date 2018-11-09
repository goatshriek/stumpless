if(MSVC)
  set(function_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
else()
  set(function_test_compile_flags "-std=c++11")
endif(MSVC)

macro(add_function_test name)
  list(APPEND STUMPLESS_FUNCTION_TESTS function-test-${name})

  add_executable(function-test-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  set_target_properties(function-test-${name}
    PROPERTIES
    OUTPUT_NAME function-test-${name}
    COMPILE_FLAGS "${function_test_compile_flags}"
  )

  target_link_libraries(function-test-${name}
    stumpless
    libgtest
    libgtestmain
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

  list(APPEND STUMPLESS_PERFORMANCE_TEST_RUNNERS run-performance-test-${name})
  add_custom_target(run-performance-test-${name}
    COMMAND "performance-test-${name}"
    DEPENDS performance-test-${name}
  )
endmacro(add_performance_test)

# RFC 5424 checking tools
add_library(rfc5424_checker
  OBJECT ${PROJECT_SOURCE_DIR}/test/function/rfc5424.cpp ${PROJECT_SOURCE_DIR}/test/function/utf8.cpp
)

set_target_properties(rfc5424_checker
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

add_dependencies(rfc5424_checker libgtest)

target_include_directories(rfc5424_checker
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)
