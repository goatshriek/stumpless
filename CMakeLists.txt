cmake_minimum_required(VERSION 3.2.3)

project(stumpless VERSION 1.2.0)

option(BUILD_PYTHON "include the python libary" OFF)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(ENABLE_WINDOWS_EVENT_LOG_TARGETS "support windows event log targets" ON)
option(COVERAGE "Include coverage information" OFF)

find_package(Threads REQUIRED)


# load modules
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(ExternalProject)


# load utilities
include(tools/cmake/benchmark.cmake)
include(tools/cmake/example.cmake)
include(tools/cmake/gtest.cmake)
include(tools/cmake/swig.cmake)
include(tools/cmake/test.cmake)

check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(windows.h HAVE_WINDOWS_H)
check_include_files(winsock2.h HAVE_WINSOCK2_H)
check_symbol_exists(gmtime_r time.h HAVE_GMTIME_R)
configure_file(${PROJECT_SOURCE_DIR}/include/private/config.h.in ${CMAKE_BINARY_DIR}/include/private/config.h)

set(STUMPLESS_SOURCES
  src/cache.c
  src/entry.c
  src/error.c
  src/formatter.c
  src/memory.c
  src/strbuilder.c
  src/strhelper.c
  src/target.c
  src/target/buffer.c
  src/target/file.c
  src/version.c
)

if(WIN32)
  list(APPEND STUMPLESS_SOURCES src/windows/stumpless.def)
endif(WIN32)

if(ENABLE_SOCKET_TARGETS AND NOT HAVE_SYS_SOCKET_H)
  message("socket targets are not supported without sys/socket.h")
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED TRUE)
  list(APPEND STUMPLESS_SOURCES src/target/socket.c)
endif(ENABLE_SOCKET_TARGETS AND NOT HAVE_SYS_SOCKET_H)

if(ENABLE_WINDOWS_EVENT_LOG_TARGETS AND NOT HAVE_WINDOWS_H)
  message("windows event log targets are not supported without windows.h")
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED TRUE)
  list(APPEND STUMPLESS_SOURCES src/target/wel.c)
  list(APPEND STUMPLESS_SOURCES src/config/wel_supported.c)
endif(ENABLE_WINDOWS_EVENT_LOG_TARGETS AND NOT HAVE_WINDOWS_H)

if(HAVE_UNISTD_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_unistd.c)
endif(HAVE_UNISTD_H)

if(HAVE_WINDOWS_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_windows.c)
endif(HAVE_WINDOWS_H)

if(HAVE_WINSOCK2_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_winsock2.c)
  find_library(WINSOCK2 NAMES Ws2_32)
endif(HAVE_WINSOCK2_H)

if(HAVE_GMTIME_R)
  list(APPEND STUMPLESS_SOURCES src/config/have_gmtime_r.c)
endif(HAVE_GMTIME_R)

check_include_files(syslog.h STUMPLESS_SYSLOG_H_COMPATIBLE)
configure_file(${PROJECT_SOURCE_DIR}/include/stumpless/config.h.in ${CMAKE_BINARY_DIR}/include/stumpless/config.h)

add_library(stumpless SHARED ${STUMPLESS_SOURCES})
set_target_properties(stumpless PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(stumpless PROPERTIES SOVERSION 0)
set_target_properties(stumpless PROPERTIES PUBLIC_HEADER include/stumpless.h)

if(HAVE_WINSOCK2_H)
  target_link_libraries(stumpless PRIVATE Ws2_32)
endif(HAVE_WINSOCK2_H)

if(COVERAGE)
  target_compile_options(stumpless PRIVATE --coverage)
  target_link_libraries(stumpless PRIVATE --coverage)
endif(COVERAGE)

target_include_directories(stumpless
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)


# standard functionality tests
enable_testing()

add_function_test(buffer
  test/function/target/buffer.cpp
  test/function/rfc5424.cpp
  test/function/utf8.cpp
)

add_function_test(entry
  test/function/entry.cpp
)

add_function_test(entry_memory_failure
  test/function/startup/entry_memory_failure.cpp
)

add_function_test(file
  test/function/target/file.cpp
  test/function/rfc5424.cpp
  test/function/utf8.cpp
)

add_function_test(memory
  test/function/memory.cpp
)

add_function_test(target
  test/function/target.cpp
)

add_function_test(version
  test/function/version.cpp
)


# standard performance tests
add_performance_test(target
  test/performance/target.cpp
)


# socket target support
if(STUMPLESS_SOCKET_TARGETS_SUPPORTED)
  add_function_test(socket
    test/function/target/socket.cpp
    test/function/rfc5424.cpp
    test/function/utf8.cpp
  )

  add_function_test(socket_add_malloc_failure
    test/function/startup/target/socket_add_malloc_failure.cpp
  )
endif(STUMPLESS_SOCKET_TARGETS_SUPPORTED)


# windows event log target support
if(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)
  ADD_CUSTOM_COMMAND(
     OUTPUT
      "${PROJECT_BINARY_DIR}/include/test/function/windows/events.h"
      "${PROJECT_BINARY_DIR}/events.rc"
     COMMAND mc -c
        -U "${PROJECT_SOURCE_DIR}/test/function/windows/events.mc"
        -r "${PROJECT_BINARY_DIR}"
        -h "${PROJECT_BINARY_DIR}/include/test/function/windows"
     DEPENDS "${PROJECT_SOURCE_DIR}/test/function/windows/events.mc"
     COMMENT "Generating test event resources")

  add_library(events SHARED EXCLUDE_FROM_ALL "${PROJECT_BINARY_DIR}/events.rc")
  set_target_properties(events PROPERTIES LINKER_LANGUAGE "CXX" )
  set_target_properties(events PROPERTIES LINK_FLAGS "/NOENTRY" )
  set_target_properties(events PROPERTIES VERSION ${PROJECT_VERSION})
  set_target_properties(events PROPERTIES SOVERSION 0)
  set_target_properties(events PROPERTIES PUBLIC_HEADER "${PROJECT_BINARY_DIR}/include/test/function/windows/events.h")

  add_function_test(wel
    test/function/target/wel.cpp
    ${PROJECT_BINARY_DIR}/events.rc
  )
  add_dependencies(function-test-wel events)

  add_function_test(wel_supported
    test/function/config/wel_supported.cpp
    ${PROJECT_BINARY_DIR}/events.rc
  )

  add_example(wel
    ${PROJECT_SOURCE_DIR}/docs/examples/wel/wel_example.c
  )
endif(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)


# python support
if(BUILD_PYTHON)
  add_swig_project()

  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/stumpless_python_wrap.c
    COMMAND ${CMAKE_COMMAND} -E env SWIG_LIB=${source_dir}/Lib ${binary_dir}/swig -python -I${PROJECT_SOURCE_DIR}/include -I${CMAKE_BINARY_DIR}/include -o ${CMAKE_BINARY_DIR}/stumpless_python_wrap.c -outdir ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src/swig/stumpless.i
    MAIN_DEPENDENCY swig
  )

  add_library(stumplesspython SHARED
    ${CMAKE_BINARY_DIR}/stumpless_python_wrap.c
  )

  target_link_libraries(stumplesspython
    optimized stumpless
  )

  target_include_directories(stumplesspython
    PRIVATE /usr/include/python2.7
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )

  set_target_properties(stumplesspython
    PROPERTIES
    PREFIX "_"
    OUTPUT_NAME stumpless
  )

  set(CTEST_ENVIRONMENT
    "PYTHONPATH=${CMAKE_BINARY_DIR}"
  )

  add_dependencies(check
    stumplesspython
  )

  add_test(NAME python-version
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_BINARY_DIR} python ${PROJECT_SOURCE_DIR}/test/function/python/version.py
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )

endif()


# documentation generation
find_program(HAVE_DOXYGEN NAMES doxygen)

if(HAVE_DOXYGEN)
  configure_file(${PROJECT_SOURCE_DIR}/tools/doxygen/Doxyfile.in ${CMAKE_BINARY_DIR}/tools/doxygen/Doxyfile)

  add_custom_target(docs
    COMMAND doxygen ${CMAKE_BINARY_DIR}/tools/doxygen/Doxyfile
  )
endif(HAVE_DOXYGEN)


# function test suite target
add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE}
  DEPENDS ${STUMPLESS_FUNCTION_TESTS}
)


# performance test suite target
add_custom_target(bench
  DEPENDS ${STUMPLESS_PERFORMANCE_TEST_RUNNERS}
)


# examples target
add_custom_target(examples
  DEPENDS ${STUMPLESS_EXAMPLE_RUNNERS}
)
