
add_function_test(buffer
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/target/buffer.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
  LIBRARIES GTest::gmock
)

add_function_test(buffer_leak
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/leak/buffer.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(current_target
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/startup/current_target.cpp"
)

add_function_test(element
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/element.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  LIBRARIES GTest::gmock
)

add_function_test(element_leak
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/leak/element.cpp"
)

add_function_test(entry
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/entry.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  LIBRARIES GTest::gmock
)

add_function_test(entry_leak
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/leak/entry.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(entry_memory_failure
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/startup/entry_memory_failure.cpp"
  LIBRARIES GTest::gmock
)

add_function_test(error
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/error.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  LIBRARIES GTest::gmock
)

add_function_test(error_leak
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/leak/error.cpp"
)

add_function_test(error_memory_failure
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/startup/error_memory_failure.cpp"
)

add_function_test(facility
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/facility.cpp"
)

add_function_test(file
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/target/file.cpp"
    $<TARGET_OBJECTS:test_helper_rfc5424>
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(filter
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/filter.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(function
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/target/function.cpp"
)

add_function_test(get_error_stream
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/startup/get_error_stream.cpp"
)

add_function_test(level_all_disabled
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/all_disabled.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_ALL_LEVELS
  LIBRARIES GTest::gmock
)

add_function_test(level_all_enabled
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/all_enabled.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_alert
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_emerg.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ALERT
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_emerg
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/all_disabled.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_EMERG
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_err
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_crit.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ERR
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_crit
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_alert.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_CRIT
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_debug
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_info.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_DEBUG
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_info
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_notice.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_INFO
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_notice
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_warning.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_NOTICE
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_trace
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_debug.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_TRACE
  LIBRARIES GTest::gmock
)

add_function_test(level_disabled_downto_warning
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_err.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_WARNING
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_alert
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_alert.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ALERT
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_crit
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_crit.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_CRIT
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_debug
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_debug.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_DEBUG
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_emerg
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_emerg.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_EMERG
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_err
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_err.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ERR
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_info
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_info.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_INFO
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_notice
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_notice.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_NOTICE
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_trace
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/all_enabled.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_TRACE
  LIBRARIES GTest::gmock
)

add_function_test(level_enable_upto_warning
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_warning.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_WARNING
  LIBRARIES GTest::gmock
)

add_function_test(log
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/log.cpp"
    $<TARGET_OBJECTS:test_helper_rfc5424>
  LIBRARIES GTest::gmock
)

add_function_test(memory
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/memory.cpp"
)

add_function_test(param
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/param.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(perror
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/startup/perror.cpp"
)

add_function_test(prival
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/prival.cpp"
)

add_function_test(severity
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/severity.cpp"
)

add_function_test(stream
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/target/stream.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
  LIBRARIES GTest::gmock
)

add_function_test(target
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/target.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
  LIBRARIES GTest::gmock
)

add_function_test(target_leak
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/leak/target.cpp"
)

add_function_test(version
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/version.cpp"
)

add_custom_target(build-test
  DEPENDS ${STUMPLESS_FUNCTION_TESTS}
)

if(CMAKE_CONFIGURATION_TYPES)
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
    DEPENDS ${STUMPLESS_FUNCTION_TESTS}
  )
else()
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS ${STUMPLESS_FUNCTION_TESTS}
  )
endif()