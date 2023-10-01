if(MSVC)
  set(example_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
else()
  set(function_test_compile_flags "")
endif(MSVC)

function(add_no_run_example name)
  add_executable(example-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  set_target_properties(example-${name}
    PROPERTIES
    BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}"
    COMPILE_FLAGS "${example_compile_flags}"
  )

  target_link_libraries(example-${name}
    stumpless
  )

  target_include_directories(example-${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )
endfunction(add_no_run_example)

function(add_no_run_single_file_example name)
  add_executable(example-single-file-${name}
    EXCLUDE_FROM_ALL
    ${SINGLE_SOURCE_FILE}
    ${ARGN}
  )

  set_target_properties(example-single-file-${name}
    PROPERTIES
    BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}"
    COMPILE_FLAGS "${example_compile_flags}"
  )

  target_include_directories(example-single-file-${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )
endfunction(add_no_run_single_file_example)

macro(add_example name)
  add_no_run_example(${name} ${ARGN})

  list(APPEND STUMPLESS_EXAMPLE_RUNNERS run-example-${name})
  add_custom_target(run-example-${name}
    COMMAND "example-${name}"
    DEPENDS example-${name}
  )

  if(BUILD_SINGLE_FILE)
    add_no_run_single_file_example(${name} ${ARGN})
    list(APPEND STUMPLESS_SINGLE_FILE_TARGETS example-single-file-${name})
    list(APPEND STUMPLESS_EXAMPLE_RUNNERS run-example-single-file-${name})
    add_custom_target(run-example-single-file-${name}
      COMMAND "example-single-file-${name}"
      DEPENDS example-single-file-${name}
    )
  endif()
endmacro(add_example)
