if(MSVC)
  set(example_compile_flags "-D_CRT_SECURE_NO_WARNINGS")
else()
  set(function_test_compile_flags "")
endif(MSVC)

macro(add_example name)
  add_executable(example-${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  set_target_properties(example-${name}
    PROPERTIES
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

  list(APPEND STUMPLESS_EXAMPLE_RUNNERS run-example-${name})
  add_custom_target(run-example-${name}
    COMMAND "example-${name}"
    DEPENDS example-${name}
  )
endmacro(add_example)
