list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/target/socket.c)
list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/socket_supported.c)

list(APPEND WRAPTURE_SPECS ${PROJECT_SOURCE_DIR}/tools/wrapture/socket_target.yml)

if(INSTALL_HEADERS)
  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/target/socket.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/target"
  )
endif()

list(APPEND DOXYGEN_MANPAGES ${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/socket.h.3)

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    ${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/socket.h.3
    RENAME stumpless_target_socket.h.3
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
  )
endif()

add_function_test(socket
  SOURCES
    test/function/target/socket.cpp
    $<TARGET_OBJECTS:test_helper_rfc5424>
    $<TARGET_OBJECTS:test_helper_fixture>
  LIBRARIES GTest::gmock
)

add_function_test(socket_add_malloc_failure
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/startup/target/socket_add_malloc_failure.cpp"
  LIBRARIES GTest::gmock
)

add_function_test(socket_supported
  SOURCES "${PROJECT_SOURCE_DIR}/test/function/config/socket_supported.cpp"
)

add_thread_safety_test(socket
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/thread_safety/target/socket.cpp"
    $<TARGET_OBJECTS:test_helper_usage>
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_example(socket
  "${PROJECT_SOURCE_DIR}/docs/examples/socket/socket_example.c"
)
