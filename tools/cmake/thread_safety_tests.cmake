add_thread_safety_test(buffer
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/target/buffer.cpp"
    $<TARGET_OBJECTS:test_helper_rfc5424>
    $<TARGET_OBJECTS:test_helper_usage>
)

add_thread_safety_test(element
  SOURCES "${PROJECT_SOURCE_DIR}/test/thread_safety/element.cpp"
)

add_thread_safety_test(entry
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/entry.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_thread_safety_test(file
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/target/file.cpp"
    $<TARGET_OBJECTS:test_helper_rfc5424>
    $<TARGET_OBJECTS:test_helper_usage>
)

add_thread_safety_test(function
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/target/function.cpp"
    $<TARGET_OBJECTS:test_helper_usage>
)

add_thread_safety_test(param
  SOURCES "${PROJECT_SOURCE_DIR}/test/thread_safety/param.cpp"
)

add_thread_safety_test(stream
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/target/stream.cpp"
    $<TARGET_OBJECTS:test_helper_rfc5424>
    $<TARGET_OBJECTS:test_helper_usage>
)

add_thread_safety_test(target
  SOURCES "${PROJECT_SOURCE_DIR}/test/thread_safety/target.cpp"
)

add_custom_target(check-thread-safety
  DEPENDS ${STUMPLESS_THREAD_SAFETY_TEST_RUNNERS}
)
