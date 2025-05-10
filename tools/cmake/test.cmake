include("${PROJECT_SOURCE_DIR}/tools/cmake/gtest.cmake")

if(MSVC)
  # the benefit of simple test code outweighs the burden of writing
  # platform-dependent code, such as the _s functions, just for tests
  set(function_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
endif(MSVC)
set(fuzz_test_compile_flags "-g -O1 -fsanitize=fuzzer,address")

function(private_add_function_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(FUNCTION_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  set(t function-test-${FUNCTION_TEST_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    ${FUNCTION_TEST_ARG_SOURCES}
  )

  set_target_properties(${t}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME ${t}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${FUNCTION_TEST_ARG_COMPILE_DEFINITIONS}"
  )

  target_link_libraries(${t}
    stumpless
    GTest::gtest
    GTest::gtest_main
    ${FUNCTION_TEST_ARG_LIBRARIES}
  )

  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(${t}
      stdc++fs
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

  target_include_directories(${t}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_test(NAME ${FUNCTION_TEST_ARG_NAME}
    COMMAND ${t}
  )
endfunction(private_add_function_test)

function(private_add_single_file_function_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(FUNCTION_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  set(t function-test-single-file-${FUNCTION_TEST_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    $<TARGET_OBJECTS:single_file_object>
    ${FUNCTION_TEST_ARG_SOURCES}
  )

  set_target_properties(${t}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME ${t}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${FUNCTION_TEST_ARG_COMPILE_DEFINITIONS}"
  )

  target_link_libraries(${t}
    GTest::gtest
    GTest::gtest_main
    ${FUNCTION_TEST_ARG_LIBRARIES}
  )

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

  target_include_directories(${t}
    PRIVATE
    "${SINGLE_INCLUDE_DIR}"
    "${PROJECT_BINARY_DIR}/include"
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

  set(t thread-safety-test-${THREAD_SAFETY_TEST_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    ${THREAD_SAFETY_TEST_ARG_SOURCES}
  )

  set_target_properties(${t}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME ${t}
    COMPILE_FLAGS "${function_test_compile_flags}"
    COMPILE_DEFINITIONS "${THREAD_SAFETY_TEST_ARG_COMPILE_DEFINITIONS}"
  )

  target_link_libraries(${t}
    stumpless
    GTest::gtest
    GTest::gtest_main
    ${THREAD_SAFETY_TEST_ARG_LIBRARIES}
  )

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

  if(NOT HAVE_WINDOWS_H)
    target_link_libraries(${t}
      pthread
    )
  endif()

  target_include_directories(${t}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  add_custom_target(run-${t}
    COMMAND "${t}"
    DEPENDS ${t}
  )
endfunction(private_add_thread_safety_test)

macro(add_thread_safety_test name)
  list(APPEND STUMPLESS_THREAD_SAFETY_TEST_RUNNERS run-thread-safety-test-${name})

  private_add_thread_safety_test(NAME ${name} ${ARGN})
endmacro(add_thread_safety_test name)

set(FUZZ_CORPORA_DIR "${PROJECT_SOURCE_DIR}/test/corpora")

function(private_add_fuzz_test)
  set(single_val_args NAME CORPUS_NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(FUNCTION_FUZZ_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  set(t fuzz-test-${FUNCTION_FUZZ_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    ${FUNCTION_FUZZ_ARG_SOURCES}
  )

  target_link_libraries(${t}
    stumpless
    "-fsanitize=fuzzer,address"
    ${FUNCTION_FUZZ_ARG_LIBRARIES}
  )

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
    COMPILE_FLAGS "${fuzz_test_compile_flags}"
    OUTPUT_NAME ${t}
  )

  target_include_directories(${t}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
  )

  set(generated_corpus_dir ${PROJECT_BINARY_DIR}/fuzz-corpora/${FUNCTION_FUZZ_ARG_CORPUS_NAME})
  file(MAKE_DIRECTORY ${generated_corpus_dir})
  add_custom_target(run-${t}
    COMMAND ${PROJECT_BINARY_DIR}/${t} ${generated_corpus_dir} "${FUZZ_CORPORA_DIR}/${FUNCTION_FUZZ_ARG_CORPUS_NAME}"
    DEPENDS ${t}
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

target_link_libraries(test_helper_fixture GTest::gtest)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  target_link_libraries(test_helper_fixture
    stdc++fs
  )
endif()

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

target_link_libraries(test_helper_network GTest::gtest)

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

target_link_libraries(test_helper_rfc5424 GTest::gtest)

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

target_link_libraries(test_helper_usage GTest::gtest)

target_include_directories(test_helper_usage
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)
