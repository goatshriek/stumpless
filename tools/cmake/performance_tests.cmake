
add_performance_test(element
  SOURCES "${PROJECT_SOURCE_DIR}/test/performance/element.cpp"
)

add_performance_test(prival
  SOURCES "${PROJECT_SOURCE_DIR}/test/performance/prival.cpp"
)

add_performance_test(entry
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/entry.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(function
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/target/function.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(buffer
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/target/buffer.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(log
  SOURCES "${PROJECT_SOURCE_DIR}/test/performance/log.cpp"
)

add_performance_test(param
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/param.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(target
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/target.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(version
  SOURCES "${PROJECT_SOURCE_DIR}/test/performance/version.cpp"
)

add_custom_target(bench
  DEPENDS ${STUMPLESS_PERFORMANCE_TEST_RUNNERS}
)
