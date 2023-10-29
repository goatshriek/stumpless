list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/target/sqlite3.c)

list(APPEND WRAPTURE_SPECS ${PROJECT_SOURCE_DIR}/tools/wrapture/sqlite3_target.yml)

install(FILES
  ${PROJECT_SOURCE_DIR}/include/stumpless/target/sqlite3.h
  DESTINATION "include/stumpless/target"
)

list(APPEND DOXYGEN_MANPAGES ${PROJECT_BINARY_DIR}/docs/man/man3/sqlite3.h.3)

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    ${PROJECT_BINARY_DIR}/docs/man/man3/sqlite3.h.3
    RENAME stumpless_target_sqlite3.h.3
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
  )
endif()

list(APPEND STUMPLESS_LINK_LIBRARIES "sqlite3")

add_function_test(sqlite3
  SOURCES
    test/function/target/sqlite3.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
  LIBRARIES
    "sqlite3"
)

add_performance_test(sqlite3
  SOURCES
    test/performance/target/sqlite3.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_thread_safety_test(sqlite3
  SOURCES
    test/thread_safety/target/sqlite3.cpp
    $<TARGET_OBJECTS:test_helper_usage>
)

add_example(sqlite3
  ${PROJECT_SOURCE_DIR}/docs/examples/sqlite3/sqlite3_example.c
)
