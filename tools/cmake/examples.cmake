
add_example(basic
  "${PROJECT_SOURCE_DIR}/docs/examples/basic/basic_example.c"
)

add_example(entry
  "${PROJECT_SOURCE_DIR}/docs/examples/entry/entry_example.c"
)

add_example(file
  "${PROJECT_SOURCE_DIR}/docs/examples/file/file_example.c"
)

add_example(filter
  "${PROJECT_SOURCE_DIR}/docs/examples/filter/filter_example.c"
)

add_example(function
  "${PROJECT_SOURCE_DIR}/docs/examples/function/function_example.c"
)

add_example(severity_level
  "${PROJECT_SOURCE_DIR}/docs/examples/severity_level/severity_level_example.c"
)

add_example(stream
  "${PROJECT_SOURCE_DIR}/docs/examples/stream/stream_example.c"
)

add_custom_target(examples
  DEPENDS ${STUMPLESS_EXAMPLE_RUNNERS}
)
