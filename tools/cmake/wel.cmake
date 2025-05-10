list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/target/wel.c")
list(
  APPEND STUMPLESS_SOURCES
  "${PROJECT_SOURCE_DIR}/src/config/wel_supported.c"
)

list(
  INSERT WRAPTURE_SPECS 0
  "${PROJECT_SOURCE_DIR}/tools/wrapture/have_wel_templates.yml"
)
list(
  APPEND WRAPTURE_SPECS
  "${PROJECT_SOURCE_DIR}/tools/wrapture/wel_target.yml"
)

if(INSTALL_HEADERS)
  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/config/wel_supported.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/config"
  )

  install(
    FILES "${PROJECT_SOURCE_DIR}/include/stumpless/target/wel.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/target"
  )
endif()

list(
  APPEND DOXYGEN_MANPAGES
  "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/wel.h.3"
)

if(INCLUDE_MANPAGES_IN_INSTALL)
  install(FILES
    "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3/wel.h.3"
    RENAME stumpless_target_wel.h.3
    DESTINATION "${CMAKE_INSTALL_MANDIR}/man3"
  )
endif()

find_program(MESSAGE_COMPILER_EXE
  NAMES
    mc
    windmc
)
if(MESSAGE_COMPILER_EXE STREQUAL "MESSAGE_COMPILER_EXE-NOTFOUND")
  set(MESSAGE_COMPILER_EXE mc)
endif()

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/include/stumpless/windows")
ADD_CUSTOM_COMMAND(
   OUTPUT
     "${PROJECT_BINARY_DIR}/include/stumpless/windows/default_events.h"
     "${PROJECT_BINARY_DIR}/default_events.rc"
   COMMAND ${MESSAGE_COMPILER_EXE} -U -b
     -r "${PROJECT_BINARY_DIR}"
     -h "${PROJECT_BINARY_DIR}/include/stumpless/windows"
     "${PROJECT_SOURCE_DIR}/src/windows/default_events.mc"
   DEPENDS "${PROJECT_SOURCE_DIR}/src/windows/default_events.mc"
   COMMENT "Generating default stumpless events"
)

add_library(
  default_events
  SHARED
  EXCLUDE_FROM_ALL
  "${PROJECT_BINARY_DIR}/default_events.rc"
)
set_target_properties(default_events PROPERTIES LINKER_LANGUAGE "C" )
set_target_properties(default_events PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(default_events PROPERTIES SOVERSION 0)
if(MSVC)
  set_target_properties(default_events PROPERTIES LINK_FLAGS "/NOENTRY" )
endif()

list(APPEND STUMPLESS_SOURCES "${PROJECT_BINARY_DIR}/default_events.rc")

install(FILES
  "${PROJECT_BINARY_DIR}/include/stumpless/windows/default_events.h"
  DESTINATION "include/stumpless/windows"
)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/include/test/function/windows")
ADD_CUSTOM_COMMAND(
   OUTPUT
     "${PROJECT_BINARY_DIR}/include/test/function/windows/events.h"
     "${PROJECT_BINARY_DIR}/events.rc"
   COMMAND ${MESSAGE_COMPILER_EXE} -U -b
     -r "${PROJECT_BINARY_DIR}"
     -h "${PROJECT_BINARY_DIR}/include/test/function/windows"
     "${PROJECT_SOURCE_DIR}/test/function/windows/events.mc"
   DEPENDS "${PROJECT_SOURCE_DIR}/test/function/windows/events.mc"
   COMMENT "Generating test events"
)

add_library(events SHARED EXCLUDE_FROM_ALL "${PROJECT_BINARY_DIR}/events.rc")
set_target_properties(events PROPERTIES LINKER_LANGUAGE "CXX" )
set_target_properties(events PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(events PROPERTIES SOVERSION 0)
if(MSVC)
  set_target_properties(events PROPERTIES LINK_FLAGS "/NOENTRY" )
endif()


list(APPEND STUMPLESS_LINK_LIBRARIES "KtmW32")

if(BUILD_TESTING)
  add_function_test(wel
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/target/wel.cpp"
      "${PROJECT_BINARY_DIR}/events.rc"
    LIBRARIES GTest::gmock
  )
  add_dependencies(function-test-wel events)
  target_compile_definitions(function-test-wel
    PUBLIC WEL_EVENTS_LIBRARY_NAME=\"$<TARGET_FILE_NAME:events>\"
  )
  add_dependencies(function-test-single-file-wel events)
  target_compile_definitions(function-test-single-file-wel
    PUBLIC WEL_EVENTS_LIBRARY_NAME=\"$<TARGET_FILE_NAME:events>\"
  )

  add_function_test(wel_supported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/config/wel_supported.cpp"
      "${PROJECT_BINARY_DIR}/events.rc"
      $<TARGET_OBJECTS:test_helper_fixture>
  )

  add_function_test(wel_supported_leak
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/leak/wel_supported.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
  )

  add_thread_safety_test(wel
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/thread_safety/target/wel.cpp"
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(wel_supported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/thread_safety/config/wel_supported.cpp"
      "${PROJECT_BINARY_DIR}/events.rc"
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()

if(BUILD_BENCHMARKING)
  add_performance_test(wel
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/performance/target/wel.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/docs/examples/wel")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/include/docs/examples/wel")
ADD_CUSTOM_COMMAND(
   OUTPUT
     "${PROJECT_BINARY_DIR}/include/docs/examples/wel/example_events.h"
     "${PROJECT_BINARY_DIR}/docs/examples/wel/example_events.rc"
   COMMAND ${MESSAGE_COMPILER_EXE} -U -b
     -r "${PROJECT_BINARY_DIR}/docs/examples/wel"
     -h "${PROJECT_BINARY_DIR}/include/docs/examples/wel"
     "${PROJECT_SOURCE_DIR}/docs/examples/wel/example_events.mc"
   DEPENDS "${PROJECT_SOURCE_DIR}/docs/examples/wel/example_events.mc"
   COMMENT "Generating wel example event resources"
)

add_example(wel
  "${PROJECT_SOURCE_DIR}/docs/examples/wel/wel_example.c"
  "${PROJECT_BINARY_DIR}/docs/examples/wel/example_events.rc"
)
