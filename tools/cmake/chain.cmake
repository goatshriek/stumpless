list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/target/chain.c")
list(APPEND WRAPTURE_SPECS "${PROJECT_SOURCE_DIR}/tools/wrapture/chain_target.yml")

install(FILES
  "${PROJECT_SOURCE_DIR}/include/stumpless/target/chain.h"
  DESTINATION "include/stumpless/target"
)

list(APPEND DOXYGEN_MANPAGES "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/chain.h.3")

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/chain.h.3"
    RENAME "stumpless_target_chain.h.3"
    DESTINATION "${CMAKE_INSTALL_MANDIR}/man3"
  )
endif()

add_function_test(chain
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/function/target/chain.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_performance_test(chain
  SOURCES
    "${PROJECT_SOURCE_DIR}/test/performance/target/chain.cpp"
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_example(chain
  "${PROJECT_SOURCE_DIR}/docs/examples/chain/chain_example.c"
)

if(STUMPLESS_THREAD_SAFETY_SUPPORTED)
  add_thread_safety_test(chain
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/thread_safety/target/chain.cpp"
      $<TARGET_OBJECTS:test_helper_rfc5424>
      $<TARGET_OBJECTS:test_helper_usage>
  )
endif()
