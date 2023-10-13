enable_testing()

if(MSVC)
  # the benefit of simple test code outweighs the burden of writing
  # platform-dependent code, such as the _s functions, just for tests
  set(function_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
else()
  set(function_test_compile_flags "-std=gnu++14 -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
  set(performance_test_compile_flags "-std=gnu++14")
endif(MSVC)
set(fuzz_test_compile_flags "-g -O1 -fsanitize=fuzzer,address")

function(private_add_function_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(FUNCTION_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(function-test-${FUNCTION_TEST_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${FUNCTION_TEST_ARG_SOURCES}
  )

  set_target_properties(function-test-${FUNCTION_TEST_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME function-test-${FUNCTION_TEST_ARG_NAME}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${FUNCTION_TEST_ARG_COMPILE_DEFINITIONS}"
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
    ${PROJECT_BINARY_DIR}/include
  )

  add_test(NAME ${FUNCTION_TEST_ARG_NAME}
    COMMAND function-test-${FUNCTION_TEST_ARG_NAME}
  )
endfunction(private_add_function_test)

function(private_add_single_file_function_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(FUNCTION_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(function-test-single-file-${FUNCTION_TEST_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${SINGLE_SOURCE_FILE}
    ${FUNCTION_TEST_ARG_SOURCES}
  )

  set_target_properties(function-test-single-file-${FUNCTION_TEST_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME function-test-single-file-${FUNCTION_TEST_ARG_NAME}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${FUNCTION_TEST_ARG_COMPILE_DEFINITIONS}"
  )

  target_link_libraries(function-test-single-file-${FUNCTION_TEST_ARG_NAME}
    libgtest
    libgtestmain
    ${FUNCTION_TEST_ARG_LIBRARIES}
  )

  target_include_directories(function-test-single-file-${FUNCTION_TEST_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )
endfunction(private_add_single_file_function_test)

macro(add_function_test name)
  list(APPEND STUMPLESS_FUNCTION_TESTS function-test-${name})
  private_add_function_test(NAME ${name} ${ARGN})

  private_add_single_file_function_test(NAME ${name} ${ARGN})
  list(APPEND STUMPLESS_SINGLE_FILE_TARGETS function-test-single-file-${name})
  list(APPEND STUMPLESS_CHECK_SINGLE_FILE_RUNNERS run-function-test-single-file-${name})
  add_custom_target(run-function-test-single-file-${name}
    COMMAND "function-test-single-file-${name}"
    DEPENDS function-test-single-file-${name}
  )
endmacro(add_function_test name)

function(private_add_thread_safety_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(THREAD_SAFETY_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${THREAD_SAFETY_TEST_ARG_SOURCES}
  )

  set_target_properties(thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${THREAD_SAFETY_TEST_ARG_COMPILE_DEFINITIONS}"
  )

  target_link_libraries(thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    stumpless
    libgtest
    libgtestmain
    ${THREAD_SAFETY_TEST_ARG_LIBRARIES}
  )

  if(NOT HAVE_WINDOWS_H)
    target_link_libraries(thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
      pthread
    )
  endif()

  target_include_directories(thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_custom_target(run-thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
    COMMAND "thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}"
    DEPENDS thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME}
  )
endfunction(private_add_thread_safety_test)

macro(add_thread_safety_test name)
  list(APPEND STUMPLESS_THREAD_SAFETY_TEST_RUNNERS run-thread-safety-test-${name})

  private_add_thread_safety_test(NAME ${name} ${ARGN})
endmacro(add_thread_safety_test name)

set(PERFORMANCE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/performance-output")
file(MAKE_DIRECTORY ${PERFORMANCE_OUTPUT_DIR})

function(private_add_performance_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_PERF_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(performance-test-${FUNCTION_PERF_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${FUNCTION_PERF_ARG_SOURCES}
  )

  if(MSVC OR MINGW)
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
      pthread
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  endif()

  set_target_properties(performance-test-${FUNCTION_PERF_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    COMPILE_FLAGS "${performance_test_compile_flags}"
    OUTPUT_NAME performance-test-${FUNCTION_PERF_ARG_NAME}
  )

  target_include_directories(performance-test-${FUNCTION_PERF_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_custom_target(run-performance-test-${FUNCTION_PERF_ARG_NAME}
	  COMMAND ${PROJECT_BINARY_DIR}/performance-test-${FUNCTION_PERF_ARG_NAME} --benchmark_out=${PERFORMANCE_OUTPUT_DIR}/${FUNCTION_PERF_ARG_NAME}.json --benchmark_out_format=json
    DEPENDS performance-test-${FUNCTION_PERF_ARG_NAME}
  )
endfunction(private_add_performance_test)

function(private_add_single_file_performance_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_PERF_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${SINGLE_SOURCE_FILE}
    ${FUNCTION_PERF_ARG_SOURCES}
  )

  if(MSVC OR MINGW)
    target_link_libraries(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
      libbenchmark
      libbenchmarkmain
      Shlwapi.lib
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  else()
    target_link_libraries(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
      libbenchmark
      libbenchmarkmain
      pthread
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  endif()

  set_target_properties(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    COMPILE_FLAGS "${performance_test_compile_flags}"
    OUTPUT_NAME performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
  )

  target_include_directories(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_custom_target(run-performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    COMMAND ${PROJECT_BINARY_DIR}/performance-test-single-file-${FUNCTION_PERF_ARG_NAME} --benchmark_out=${PERFORMANCE_OUTPUT_DIR}/${FUNCTION_PERF_ARG_NAME}.json --benchmark_out_format=json
    DEPENDS performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
  )
endfunction(private_add_single_file_performance_test)

macro(add_performance_test name)
  list(APPEND STUMPLESS_PERFORMANCE_TEST_RUNNERS run-performance-test-${name})
  private_add_performance_test(NAME ${name} ${ARGN})

  private_add_single_file_performance_test(NAME ${name} ${ARGN})
  list(APPEND STUMPLESS_SINGLE_FILE_TARGETS performance-test-single-file-${name})
  list(APPEND STUMPLESS_BENCH_SINGLE_FILE_RUNNERS run-performance-test-single-file-${name})
endmacro(add_performance_test)

function(private_add_fuzz_test)
  set(single_val_args NAME CORPUS_NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_FUZZ_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${FUNCTION_FUZZ_ARG_SOURCES}
  )

  target_link_libraries(fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
    stumpless
    "-fsanitize=fuzzer,address"
    ${FUNCTION_FUZZ_ARG_LIBRARIES}
  )

  set_target_properties(fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    COMPILE_FLAGS "${fuzz_test_compile_flags}"
    OUTPUT_NAME fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
  )

  target_include_directories(fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  set(generated_corpus_dir ${PROJECT_BINARY_DIR}/fuzz-corpora/${FUNCTION_FUZZ_ARG_CORPUS_NAME})
  file(MAKE_DIRECTORY ${generated_corpus_dir})
  add_custom_target(run-fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
    COMMAND ${PROJECT_BINARY_DIR}/fuzz-test-${FUNCTION_FUZZ_ARG_NAME} ${generated_corpus_dir} "${FUZZ_CORPORA_DIR}/${FUNCTION_FUZZ_ARG_CORPUS_NAME}"
    DEPENDS fuzz-test-${FUNCTION_FUZZ_ARG_NAME}
  )
endfunction(private_add_fuzz_test)

macro(add_fuzz_test name)
  list(APPEND STUMPLESS_FUZZ_TESTS fuzz-test-${name})

  private_add_fuzz_test(NAME ${name} ${ARGN})
endmacro(add_fuzz_test)

# helper libraries
add_library(test_helper_fixture
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/fixture.cpp
)

set_target_properties(test_helper_fixture
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

add_dependencies(test_helper_fixture libgtest)

target_include_directories(test_helper_fixture
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)

add_library(test_helper_network
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/network.cpp
)

set_target_properties(test_helper_network
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

add_dependencies(test_helper_network libgtest)

target_include_directories(test_helper_network
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)

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
    ${PROJECT_BINARY_DIR}/include
)
add_library(test_helper_rfc5424
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/rfc5424.cpp ${PROJECT_SOURCE_DIR}/test/helper/utf8.cpp
)

set_target_properties(test_helper_rfc5424
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

add_dependencies(test_helper_rfc5424 libgtest)

target_include_directories(test_helper_rfc5424
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
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
    ${PROJECT_BINARY_DIR}/include
)

add_library(test_helper_usage
  EXCLUDE_FROM_ALL
  OBJECT ${PROJECT_SOURCE_DIR}/test/helper/usage.cpp
)

set_target_properties(test_helper_usage
  PROPERTIES
  COMPILE_FLAGS "${function_test_compile_flags}"
)

target_include_directories(test_helper_usage
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)
