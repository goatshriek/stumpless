enable_testing()

if(MSVC)
  # the benefit of simple test code outweighs the burden of writing
  # platform-dependent code, such as the _s functions, just for tests
  set(function_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
else()
  set(function_test_compile_flags "-std=gnu++11 -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
endif(MSVC)

function(private_add_function_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(function-test-${FUNCTION_TEST_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${FUNCTION_TEST_ARG_SOURCES}
  )

  set_target_properties(function-test-${FUNCTION_TEST_ARG_NAME}
    PROPERTIES
    OUTPUT_NAME function-test-${FUNCTION_TEST_ARG_NAME}
    COMPILE_FLAGS "${function_test_compile_flags}"
  )

  target_link_libraries(function-test-${FUNCTION_TEST_ARG_NAME}
    stumpless
    libgtest
    libgtestmain
    ${FUNCTION_TEST_ARG_LIBRARIES}
  )

  target_include_directories(function-test-${FUNCTION_TEST_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  add_test(NAME ${FUNCTION_TEST_ARG_NAME}
    COMMAND function-test-${FUNCTION_TEST_ARG_NAME}
  )
endfunction(private_add_function_test)

macro(add_function_test name)
  list(APPEND STUMPLESS_FUNCTION_TESTS function-test-${name})

  private_add_function_test(NAME ${name} ${ARGN})
endmacro(add_function_test name)

function(private_add_performance_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_PERF_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(performance-test-${FUNCTION_PERF_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${FUNCTION_PERF_ARG_SOURCES}
  )

  if(MSVC)
    target_link_libraries(performance-test-${FUNCTION_PERF_ARG_NAME}
      stumpless
      libbenchmark
      libbenchmarkmain
      Shlwapi.lib
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  else()
    target_link_libraries(performance-test-${FUNCTION_PERF_ARG_NAME}
      stumpless
      libbenchmark
      libbenchmarkmain
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  endif(MSVC)

  set_target_properties(performance-test-${FUNCTION_PERF_ARG_NAME}
    PROPERTIES
    OUTPUT_NAME performance-test-${FUNCTION_PERF_ARG_NAME}
  )

  target_include_directories(performance-test-${FUNCTION_PERF_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  add_custom_target(run-performance-test-${FUNCTION_PERF_ARG_NAME}
    COMMAND "performance-test-${FUNCTION_PERF_ARG_NAME}"
    DEPENDS performance-test-${FUNCTION_PERF_ARG_NAME}
  )

endfunction(private_add_performance_test)

macro(add_performance_test name)
  list(APPEND STUMPLESS_PERFORMANCE_TEST_RUNNERS run-performance-test-${name})

  private_add_performance_test(NAME ${name} ${ARGN})
endmacro(add_performance_test)

# RFC 5424 checking tools
add_library(rfc5424_checker
  EXCLUDE_FROM_ALL
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

# helper libraries
add_library(test_helper_resolve
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/resolve.cpp
)

set_target_properties(test_helper_resolve
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

target_include_directories(test_helper_resolve
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)

add_library(test_helper_server
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/server.cpp
)

set_target_properties(test_helper_server
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

target_include_directories(test_helper_server
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)
