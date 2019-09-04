if(MSVC)
  # the benefit of simple test code outweighs the burden of writing
  # platform-dependent code, such as the _s functions, just for tests
  set(cpp_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
else()
  set(cpp_test_compile_flags "-std=c++11")
endif(MSVC)

function(private_add_cpp_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(CPP_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  add_executable(cpp-test-${CPP_TEST_ARG_NAME}
    EXCLUDE_FROM_ALL
    ${CPP_TEST_ARG_SOURCES}
  )

  set_target_properties(cpp-test-${CPP_TEST_ARG_NAME}
    PROPERTIES
    OUTPUT_NAME cpp-test-${CPP_TEST_ARG_NAME}
    COMPILE_FLAGS "${cpp_test_compile_flags}"
  )

  target_link_libraries(cpp-test-${CPP_TEST_ARG_NAME}
    stumplesscpp
    libgtest
    libgtestmain
    ${CPP_TEST_ARG_LIBRARIES}
  )

  target_include_directories(cpp-test-${CPP_TEST_ARG_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_BINARY_DIR}/cpp-lib
  )

  add_custom_target(run-cpp-test-${CPP_TEST_ARG_NAME}
    COMMAND "cpp-test-${CPP_TEST_ARG_NAME}"
    DEPENDS cpp-test-${CPP_TEST_ARG_NAME}
  )
endfunction(private_add_cpp_test)

macro(add_cpp_test name)
  list(APPEND STUMPLESS_CPP_TEST_RUNNERS run-cpp-test-${name})

  private_add_cpp_test(NAME ${name} ${ARGN})
endmacro(add_cpp_test name)
