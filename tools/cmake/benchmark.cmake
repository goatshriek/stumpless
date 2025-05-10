# Google Benchmark dependency
set(BENCHMARK_URL https://github.com/google/benchmark/archive/299e5928955cc62af9968370293b916f5130916f.zip) # v1.9.3
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "disable benchmark tests")
if(CMAKE_VERSION VERSION_LESS "3.24")
  # FIND_PACKAGE_ARGS is not available before 3.24, but for now we don't require
  # the higher version just for it
  FetchContent_Declare(
    googlebenchmark
    URL ${BENCHMARK_URL}
  )
else()
  FetchContent_Declare(
    googlebenchmark
    URL ${BENCHMARK_URL}
    FIND_PACKAGE_ARGS NAMES benchmark
  )
endif()
FetchContent_MakeAvailable(googlebenchmark)

# performance test output directory
set(PERFORMANCE_OUTPUT_DIR "${PROJECT_BINARY_DIR}/performance-output")
file(MAKE_DIRECTORY ${PERFORMANCE_OUTPUT_DIR})

function(private_add_performance_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_PERF_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  set(t performance-test-${FUNCTION_PERF_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    ${FUNCTION_PERF_ARG_SOURCES}
  )

  if(MSVC OR MINGW)
    target_link_libraries(${t}
      stumpless
      GTest::gtest
      benchmark::benchmark_main
      Shlwapi.lib
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  else()
    target_link_libraries(${t}
      stumpless
      GTest::gtest
      benchmark::benchmark_main
      pthread
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  endif()

  set(have_runtime_dlls
    $<BOOL:$<TARGET_RUNTIME_DLLS:${t}>>
  )
  set(copy_command
      ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_RUNTIME_DLLS:${t}>
      $<TARGET_FILE_DIR:${t}>
  )
  add_custom_command(TARGET ${t} POST_BUILD
      COMMAND "$<${have_runtime_dlls}:${copy_command}>"
      COMMAND_EXPAND_LISTS
  )

  set_target_properties(${t}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    COMPILE_FLAGS "${performance_test_compile_flags}"
    OUTPUT_NAME ${t}
  )

  target_include_directories(${t}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_custom_target(run-${t}
	  COMMAND ${PROJECT_BINARY_DIR}/${t} --benchmark_out=${PERFORMANCE_OUTPUT_DIR}/${FUNCTION_PERF_ARG_NAME}.json --benchmark_out_format=json
    DEPENDS ${t}
  )
endfunction(private_add_performance_test)

function(private_add_single_file_performance_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_PERF_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    EXCLUDE_FROM_ALL
    $<TARGET_OBJECTS:single_file_object>
    ${FUNCTION_PERF_ARG_SOURCES}
  )

  if(MSVC OR MINGW)
    target_link_libraries(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
      GTest::gtest
      benchmark::benchmark_main
      Shlwapi.lib
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  else()
    target_link_libraries(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
      GTest::gtest
      benchmark::benchmark_main
      pthread
      ${FUNCTION_PERF_ARG_LIBRARIES}
    )
  endif()

  if($<TARGET_RUNTIME_DLLS:performance-test-${FUNCTION_PERF_ARG_NAME}>)
    add_custom_command(TARGET performance-test-${FUNCTION_PERF_ARG_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:performance-test-${FUNCTION_PERF_ARG_NAME}> $<TARGET_FILE_DIR:performance-test-${FUNCTION_PERF_ARG_NAME}>
      COMMAND_EXPAND_LISTS
    )
  endif()

  set_target_properties(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    COMPILE_FLAGS "${performance_test_compile_flags}"
    OUTPUT_NAME "performance-test-single-file-${FUNCTION_PERF_ARG_NAME}"
  )

  target_include_directories(performance-test-single-file-${FUNCTION_PERF_ARG_NAME}
    PRIVATE
    "${SINGLE_INCLUDE_DIR}"
    "${PROJECT_BINARY_DIR}/include"
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