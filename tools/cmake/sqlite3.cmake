list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/target/sqlite3.c")
list(
  APPEND WRAPTURE_SPECS
  "${PROJECT_SOURCE_DIR}/tools/wrapture/sqlite3_target.yml"
)
list(
  APPEND DOXYGEN_MANPAGES
  "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/sqlite3.h.3"
)

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/sqlite3.h.3"
    RENAME "stumpless_target_sqlite3.h.3"
    DESTINATION "${CMAKE_INSTALL_MANDIR}/man3"
  )
endif()

if(SQLITE3_SRC_PATH)
  add_library(sqlite3-src SHARED EXCLUDE_FROM_ALL "${SQLITE3_SRC_PATH}")
  set_target_properties(sqlite3-src PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
  target_compile_definitions(sqlite3-src PUBLIC "SQLITE_OMIT_LOAD_EXTENSION")
  set(SQLITE3_LINK_NAME "sqlite3-src")
else()
  list(APPEND STUMPLESS_LINK_LIBRARIES "sqlite3")
  set(SQLITE3_LINK_NAME "sqlite3")
endif()

if(BUILD_TESTING)
  add_function_test(sqlite3
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/sqlite3.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_rfc5424>
    LIBRARIES
      "${SQLITE3_LINK_NAME}"
  )
endif()

if(BUILD_BENCHMARKING)
  add_performance_test(sqlite3
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/performance/target/sqlite3.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()

if(STUMPLESS_THREAD_SAFETY_SUPPORTED)
  add_thread_safety_test(sqlite3
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/thread_safety/target/sqlite3.cpp"
      $<TARGET_OBJECTS:test_helper_usage>
    LIBRARIES
      "${SQLITE3_LINK_NAME}"
  )
endif()

add_example(sqlite3
  "${PROJECT_SOURCE_DIR}/docs/examples/sqlite3/sqlite3_example.c"
  "${SQLITE3_SRC_PATH}"
)

target_link_libraries(example-sqlite3
  "${SQLITE3_LINK_NAME}"
)
