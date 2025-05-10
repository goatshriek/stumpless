if(MSVC)
  # the benefit of simple test code outweighs the burden of writing
  # platform-dependent code, such as the _s functions, just for tests
  set(cpp_test_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
else()
  set(cpp_test_compile_flags "")
endif(MSVC)

function(private_add_cpp_test)
  set(single_val_args NAME)
  set(multi_val_args SOURCES LIBRARIES)
  cmake_parse_arguments(CPP_TEST_ARG "" "${single_val_args}" "${multi_val_args}" ${ARGN})

  set(t cpp-test-${CPP_TEST_ARG_NAME})
  add_executable(${t}
    EXCLUDE_FROM_ALL
    ${CPP_TEST_ARG_SOURCES}
  )

  set_target_properties(${t}
    PROPERTIES
    BUILD_RPATH "${PROJECT_BINARY_DIR}"
    OUTPUT_NAME ${t}
    COMPILE_FLAGS "${cpp_test_compile_flags}"
  )

  target_link_libraries(${t}
    stumplesscpp
    GTest::gtest
    GTest::gtest_main
    ${CPP_TEST_ARG_LIBRARIES}
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

  target_include_directories(cpp-test-${CPP_TEST_ARG_NAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    "${PROJECT_BINARY_DIR}/cpp-lib"
  )

  add_custom_target(run-${t}
    COMMAND "${t}"
    DEPENDS ${t}
  )
endfunction(private_add_cpp_test)

macro(add_cpp_test name)
  list(APPEND STUMPLESS_CPP_TEST_RUNNERS run-cpp-test-${name})

  private_add_cpp_test(NAME ${name} ${ARGN})
endmacro(add_cpp_test name)
