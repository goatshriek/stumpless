list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/target/network.c")
list(
  APPEND WRAPTURE_SPECS
  "${PROJECT_SOURCE_DIR}/tools/wrapture/network_target.yml"
)

if(HAVE_SYS_SOCKET_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_sys_socket.c"
  )
  set(HAVE_WINSOCK2_H FALSE)

  if(HAVE_GETADDRINFO)
    list(
      APPEND STUMPLESS_SOURCES
      "${PROJECT_SOURCE_DIR}/src/config/have_getaddrinfo.c"
    )
  elseif(HAVE_GETHOSTBYNAME2 OR HAVE_GETHOSTBYNAME)
    set(SUPPORT_GETHOSTBYNAME TRUE)
    list(
      APPEND STUMPLESS_SOURCES
      "${PROJECT_SOURCE_DIR}/src/config/gethostbyname_supported.c"
    )
  endif()
elseif(HAVE_WINSOCK2_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_winsock2.c"
  )
  find_library(WINSOCK2 NAMES Ws2_32)
endif()

if(INSTALL_HEADERS)
  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/target/network.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/target"
  )
endif()

list(
  APPEND DOXYGEN_MANPAGES
  "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/network.h.3"
)

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/network.h.3"
    RENAME stumpless_target_network.h.3
    DESTINATION "${CMAKE_INSTALL_MANDIR}/man3"
  )
endif()

if(WIN32)
  set(network_libraries Ws2_32)
endif(WIN32)

if(BUILD_TESTING)
  add_function_test(network
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/network.cpp"
      $<TARGET_OBJECTS:test_helper_resolve>
    LIBRARIES ${network_libraries} GTest::gmock
  )

  add_function_test(tcp4
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/tcp4.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_rfc5424>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp6
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/tcp6.cpp"
      $<TARGET_OBJECTS:test_helper_rfc5424>
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp4
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/udp4.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_network>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_rfc5424>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries} GTest::gmock
  )

  add_function_test(udp6
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/udp6.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_network>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_rfc5424>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries} GTest::gmock
  )

  add_function_test(network_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/network.cpp"
  )

  add_function_test(tcp4_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/tcp4.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp6_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/tcp6.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp4_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/udp4.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp6_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/udp6.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_thread_safety_test(network
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/thread_safety/target/network.cpp"
      $<TARGET_OBJECTS:test_helper_usage>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )
endif()

if(BUILD_BENCHMARKING)
  add_performance_test(network
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/performance/target/network.cpp"
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )
endif()

add_no_run_example(tcp
  ${PROJECT_SOURCE_DIR}/docs/examples/network/tcp_example.c
)

add_no_run_example(udp
  ${PROJECT_SOURCE_DIR}/docs/examples/network/udp_example.c
)
