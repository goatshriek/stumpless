macro(add_function_test name)
  list(APPEND STUMPLESS_FUNCTION_TESTS ${name})

  add_executable(${name}
    EXCLUDE_FROM_ALL
    ${ARGN}
  )

  set_target_properties(${name}
    PROPERTIES COMPILE_FLAGS "-std=c++11"
  )

  target_link_libraries(${name}
    stumpless
    libgtest
  )

  target_include_directories(${name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  add_test(NAME ${name}
    COMMAND ${name}
  )
endmacro(add_function_test)
