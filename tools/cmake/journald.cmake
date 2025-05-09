list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/target/journald.c")
list(
  APPEND STUMPLESS_SOURCES
  "${PROJECT_SOURCE_DIR}/src/config/journald_supported.c"
)
list(
  APPEND WRAPTURE_SPECS
  "${PROJECT_SOURCE_DIR}/tools/wrapture/journald_target.yml"
)

if(INSTALL_HEADERS)
  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/target/journald.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/target"
  )

  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/config/journald_supported.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/config"
  )
endif()

list(
  APPEND DOXYGEN_MANPAGES
  "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/journald.h.3"
)
list(
  APPEND DOXYGEN_MANPAGES
  "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/journald_supported.h.3"
)

list(APPEND STUMPLESS_LINK_LIBRARIES "systemd")

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/journald.h.3"
    RENAME stumpless_target_journald.h.3
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
  )

  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/journald_supported.h.3"
    RENAME stumpless_config_journald_supported.h.3
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
  )
endif()

if(BUILD_TESTING)
  add_function_test(journald
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/journald.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
    LIBRARIES
      systemd
  )

  add_function_test(journald_supported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/config/journald_supported.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
    LIBRARIES
      systemd
  )

  if(STUMPLESS_THREAD_SAFETY_SUPPORTED)
    add_thread_safety_test(journald
      SOURCES
        "${PROJECT_SOURCE_DIR}/test/thread_safety/target/journald.cpp"
        $<TARGET_OBJECTS:test_helper_usage>
      LIBRARIES
        systemd
    )
  endif()
endif()

if(BUILD_BENCHMARKING)
  add_performance_test(journald
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/performance/target/journald.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()

add_example(journald
  "${PROJECT_SOURCE_DIR}/docs/examples/journald/journald_example.c"
)
