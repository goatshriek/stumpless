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
endmacro(add_example)
