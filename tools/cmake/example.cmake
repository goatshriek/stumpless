macro(add_example name)
  list(APPEND STUMPLESS_EXAMPLES example-${name})

  add_executable(example-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  target_link_libraries(example-${name}
    stumpless
  )

  target_include_directories(example-${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  list(APPEND STUMPLESS_EXAMPLE_RUNNERS run-example-${name})
  add_custom_target(run-example-${name}
    COMMAND "example-${name}"
    DEPENDS example-${name}
  )
endmacro(add_example)
