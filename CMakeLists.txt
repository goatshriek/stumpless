cmake_minimum_required(VERSION 3.2.3)

project(stumpless VERSION 2.1.0)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://goatshriek.github.io/stumpless/")

string(CONCAT enable_cpp_help_string
  "Build the C++ language binding library. The library will be added to the "
  "'all' target and will be installed via the 'install' target, alongside the "
  "C library. Other targets (such as 'docs' and 'check') will have a '-cpp' "
  "version that takes the same action for the C++ library. For example, build "
  "the 'check-cpp' target to build and run the test suite for the C++ library."
)
option(ENABLE_CPP ${enable_cpp_help_string} OFF)

option(BUILD_PYTHON "include the python libary" OFF)

option(ENABLE_THREAD_SAFETY "support thread-safe functionality" ON)
option(ENABLE_NETWORK_TARGETS "support network targets" ON)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(ENABLE_WINDOWS_EVENT_LOG_TARGETS "support windows event log targets" ON)
option(COVERAGE "Include coverage information" OFF)

string(CONCAT enable_deprecation_warnings_help_string
  "Print warnings to the standard output when deprecated functionality is used."
)
option(ENABLE_DEPRECATION_WARNINGS ${enable_deprecation_warnings_help_string} ON)

string(CONCAT default_facility_help_string
  "The facility code to use for messages where one is not explicitly provided."
)
set(DEFAULT_FACILITY "STUMPLESS_FACILITY_USER"
  CACHE STRING ${default_facility_help_string}
)

string(CONCAT default_severity_help_string
  "The severity code to use for messages where one is not explicitly provided."
)
set(DEFAULT_SEVERITY "STUMPLESS_SEVERITY_INFO"
  CACHE STRING ${default_severity_help_string}
)

set(FALLBACK_PAGESIZE 4096
  CACHE STRING "the memory page size to use if it cannot be detected at runtime"
)

string(CONCAT benchmark_path_help_string
  "A directory with a build of google benchmark that can be used instead of "
  "downloading and building the library during build. "
  "In order for this to be used the directory must include ALL of the "
  "following at configuration time: the benchmark and benchmark_main "
  "libraries, and the benchmark/benchmark.h header. "
  "If the necessary files are not found, the benchmark library will be "
  "downloaded and built when it is needed, and the export-benchmark target "
  "can be used to populate the provided directory for future builds."
)
set(BENCHMARK_PATH ${PROJECT_BINARY_DIR}
  CACHE PATH ${benchmark_path_help_string}
)

string(CONCAT gtest_path_help_string
  "A directory with a build of google test that can be used instead of "
  "downloading and building the library during build. "
  "In order for this to be used the directory must include ALL of the "
  "following at configuration time: the gtest, gtest_main, and gmock "
  "libraries, the gtest/gtest.h header, and the gmock/gmock.h header. "
  "If the necessary files are not found, the gtest library will be "
  "downloaded and built when it is needed, and the export-gtest target "
  "can be used to populate the provided directory for future builds."
)
set(GTEST_PATH ${PROJECT_BINARY_DIR}
  CACHE PATH ${gtest_path_help_string}
)

string(CONCAT locale_help_string
  "The locale used for strings passed by the library, for example error "
  "messages. If this is not set it will use the LANG environment variable "
  "of the build system."
)
set(LOCALE $ENV{LANG}
  CACHE STRING ${locale_help_string}
)


# documentation and doxygen setup
set(PROJECT_DOCS_DIR ${CMAKE_BINARY_DIR}/docs)
find_program(HAVE_DOXYGEN NAMES doxygen)
if(HAVE_DOXYGEN)
  configure_file(${PROJECT_SOURCE_DIR}/tools/doxygen/Doxyfile.in ${CMAKE_BINARY_DIR}/tools/doxygen/Doxyfile)

  add_custom_target(docs
    COMMAND doxygen ${CMAKE_BINARY_DIR}/tools/doxygen/Doxyfile
  )
endif(HAVE_DOXYGEN)


# load modules
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(ExternalProject)


# load utilities
include(tools/cmake/google_libs.cmake)
include(tools/cmake/add_found_library.cmake)
# the above two need to be before benchmark and gtest

include(tools/cmake/benchmark.cmake)
include(tools/cmake/example.cmake)
include(tools/cmake/gtest.cmake)
include(tools/cmake/swig.cmake)
include(tools/cmake/test.cmake)


# building configuration
check_include_files(pthread.h HAVE_PTHREAD_H)
check_include_files(stdatomic.h HAVE_STDATOMIC_H)
check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_files(syslog.h STUMPLESS_SYSLOG_H_COMPATIBLE)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(windows.h HAVE_WINDOWS_H)
check_include_files(winsock2.h HAVE_WINSOCK2_H)

check_symbol_exists(fopen_s stdio.h HAVE_FOPEN_S)
check_symbol_exists(gmtime_r time.h HAVE_GMTIME_R)
check_symbol_exists(sprintf_s stdio.h HAVE_SPRINTF_S)
check_symbol_exists(vsnprintf_s stdio.h HAVE_VSNPRINTF_S)
check_symbol_exists(gethostname unistd.h HAVE_UNISTD_GETHOSTNAME)
check_symbol_exists(getpagesize unistd.h HAVE_UNISTD_GETPAGESIZE)
check_symbol_exists(_SC_PAGESIZE unistd.h HAVE_UNISTD_SC_PAGESIZE)
check_symbol_exists(sysconf unistd.h HAVE_UNISTD_SYSCONF)
check_symbol_exists(wcstombs_s windows.h HAVE_WCSTOMBS_S)

find_program(HAVE_WRAPTURE NAMES wrapture)

if(ENABLE_DEPRECATION_WARNINGS)
  set(STUMPLESS_DEPRECATION_WARNINGS_ENABLED TRUE)
else()
  set(STUMPLESS_DEPRECATION_WARNINGS_ENABLED OFF)
endif()

if(EXISTS "/var/run/syslog")
  set(STUMPLESS_DEFAULT_SOCKET "/var/run/syslog")
else()
  set(STUMPLESS_DEFAULT_SOCKET "/dev/log")
endif()

# setting the chosen locale
if(LOCALE MATCHES "^es[_-]")
  set(STUMPLESS_LANGUAGE "es-ES")
  set(USE_LOCALE_ES_ES TRUE)
elseif(LOCALE MATCHES "^fr[_-]")
  set(STUMPLESS_LANGUAGE "fr-FR")
  set(USE_LOCALE_FR_FR TRUE)
elseif(LOCALE MATCHES "^de[_-]")
  set(STUMPLESS_LANGUAGE "de-DE")
  set(USE_LOCALE_DE_DE TRUE)
elseif(LOCALE MATCHES "^it[_-]")
  set(STUMPLESS_LANGUAGE "it-IT")
  set(USE_LOCALE_IT_IT TRUE)
elseif(LOCALE MATCHES "^sv[_-]")
  set(STUMPLESS_LANGUAGE "sv-SE")
  set(USE_LOCALE_SV_SE TRUE)
elseif(LOCALE MATCHES "^sk[_-]")
  set(STUMPLESS_LANGUAGE "sk-SK")
  set(USE_LOCALE_SK_SK TRUE)
elseif(LOCALE MATCHES "^bg[_-]")
  set(STUMPLESS_LANGUAGE "bg-BG")
  set(USE_LOCALE_BG_BG TRUE)
else()
  if(NOT LOCALE MATCHES "^en[_-]")
    message("building default language en-US")
  endif()
  set(STUMPLESS_LANGUAGE "en-US")
  set(USE_LOCALE_EN_US TRUE)
endif()

# standard source files
set(STUMPLESS_SOURCES
  ${PROJECT_SOURCE_DIR}/src/cache.c
  ${PROJECT_SOURCE_DIR}/src/element.c
  ${PROJECT_SOURCE_DIR}/src/entry.c
  ${PROJECT_SOURCE_DIR}/src/error.c
  ${PROJECT_SOURCE_DIR}/src/facility.c
  ${PROJECT_SOURCE_DIR}/src/formatter.c
  ${PROJECT_SOURCE_DIR}/src/inthelper.c
  ${PROJECT_SOURCE_DIR}/src/memory.c
  ${PROJECT_SOURCE_DIR}/src/param.c
  ${PROJECT_SOURCE_DIR}/src/severity.c
  ${PROJECT_SOURCE_DIR}/src/strbuilder.c
  ${PROJECT_SOURCE_DIR}/src/strhelper.c
  ${PROJECT_SOURCE_DIR}/src/target.c
  ${PROJECT_SOURCE_DIR}/src/target/buffer.c
  ${PROJECT_SOURCE_DIR}/src/target/file.c
  ${PROJECT_SOURCE_DIR}/src/target/function.c
  ${PROJECT_SOURCE_DIR}/src/target/stream.c
  ${PROJECT_SOURCE_DIR}/src/version.c
  ${PROJECT_SOURCE_DIR}/src/validate.c
)


# wrapture support
set(WRAPTURE_SPECS
  # template files must be first
  ${PROJECT_SOURCE_DIR}/tools/wrapture/error_templates.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/target_templates.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/buffer_target.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/element.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/entry.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/error.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/facility.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/file_target.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/function_target.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/memory.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/param.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/severity.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/stream_target.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/target.yml
  ${PROJECT_SOURCE_DIR}/tools/wrapture/version.yml
)


# configuration-specific source files
if(HAVE_FOPEN_S)
  list(APPEND STUMPLESS_SOURCES src/config/have_fopen_s.c)
endif(HAVE_FOPEN_S)

if(HAVE_GMTIME_R)
  list(APPEND STUMPLESS_SOURCES src/config/have_gmtime_r.c)
endif(HAVE_GMTIME_R)

if(HAVE_PTHREAD_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_pthread.c)
endif()

if(HAVE_STDATOMIC_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_stdatomic.c)
endif()

if(HAVE_UNISTD_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_unistd.c)
endif(HAVE_UNISTD_H)

if(HAVE_VSNPRINTF_S)
  list(APPEND STUMPLESS_SOURCES src/config/have_vsnprintf_s.c)
else()
  list(APPEND STUMPLESS_SOURCES src/config/no_vsnprintf_s.c)
endif(HAVE_VSNPRINTF_S)

if(HAVE_WINDOWS_H)
  list(APPEND STUMPLESS_SOURCES src/config/have_windows.c)
endif(HAVE_WINDOWS_H)

if(WIN32)
  list(APPEND STUMPLESS_SOURCES src/windows/stumpless.def)
endif(WIN32)

if(HAVE_WINDOWS_H AND HAVE_SPRINTF_S)
  set(SUPPORT_WINDOWS_GET_NOW TRUE)
  list(APPEND STUMPLESS_SOURCES src/config/support_windows_get_now.c)
endif()

if(HAVE_UNISTD_GETHOSTNAME)
  list(APPEND STUMPLESS_SOURCES src/config/have_unistd_gethostname.c)
elseif(NOT HAVE_WINSOCK2_H)
  # need the fallback gethostname definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(HAVE_UNISTD_SYSCONF AND HAVE_UNISTD_SC_PAGESIZE)
  set(SUPPORT_UNISTD_SYSCONF_GETPAGESIZE TRUE)
  list(APPEND STUMPLESS_SOURCES src/config/support_unistd_sysconf_getpagesize.c)
elseif(HAVE_UNISTD_GETPAGESIZE)
  list(APPEND STUMPLESS_SOURCES src/config/have_unistd_getpagesize.c)
elseif(NOT HAVE_WINDOWS_H)
  # need the fallback getpagesize definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NOT HAVE_UNISTD_H AND NOT HAVE_WINDOWS_H)
  # need the fallback getpid definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NEED_FALLBACK)
  list(APPEND STUMPLESS_SOURCES src/config/fallback.c)
endif()


# network target support
if(NOT ENABLE_NETWORK_TARGETS)
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED FALSE)

  if(WIN32)
    list(APPEND STUMPLESS_SOURCES src/config/network_unsupported.c)
  endif(WIN32)

  add_function_test(network_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/network_unsupported.cpp
  )

elseif(NOT HAVE_WINSOCK2_H AND NOT HAVE_SYS_SOCKET_H)
  message("network targets are not supported without either winsock2.h or sys/socket.h")
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED FALSE)

  if(WIN32)
    list(APPEND STUMPLESS_SOURCES src/config/network_unsupported.c)
  endif(WIN32)

  add_function_test(network_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/network_unsupported.cpp
  )

else()
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED TRUE)

  list(APPEND STUMPLESS_SOURCES src/target/network.c)
  list(APPEND WRAPTURE_SPECS ${PROJECT_SOURCE_DIR}/tools/wrapture/network_target.yml)

  if(HAVE_SYS_SOCKET_H)
    list(APPEND STUMPLESS_SOURCES src/config/have_sys_socket.c)
    set(HAVE_WINSOCK2_H FALSE)
  elseif(HAVE_WINSOCK2_H)
    list(APPEND STUMPLESS_SOURCES src/config/have_winsock2.c)
    find_library(WINSOCK2 NAMES Ws2_32)
  endif()

  install(FILES
    ${PROJECT_SOURCE_DIR}/include/stumpless/target/network.h
    DESTINATION "include/stumpless/target"
  )

  if(WIN32)
    set(network_libraries Ws2_32)
  endif(WIN32)

  add_function_test(network
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/target/network.cpp
      $<TARGET_OBJECTS:test_helper_resolve>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp4
    SOURCES
      test/function/target/tcp4.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp6
    SOURCES
      test/function/target/tcp6.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp4
    SOURCES
      test/function/target/udp4.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp6
    SOURCES
      test/function/target/udp6.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_resolve>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp4_leak
    SOURCES
      test/function/leak/tcp4.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(tcp6_leak
    SOURCES
      test/function/leak/tcp6.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp4_leak
    SOURCES
      test/function/leak/udp4.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_function_test(udp6_leak
    SOURCES
      test/function/leak/udp6.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_thread_safety_test(network
    SOURCES
      test/thread_safety/target/network.cpp
      $<TARGET_OBJECTS:test_helper_usage>
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_performance_test(network
    SOURCES
      test/performance/target/network.cpp
      $<TARGET_OBJECTS:test_helper_server>
    LIBRARIES ${network_libraries}
  )

  add_no_run_example(tcp
    ${PROJECT_SOURCE_DIR}/docs/examples/network/tcp_example.c
  )

  add_no_run_example(udp
    ${PROJECT_SOURCE_DIR}/docs/examples/network/udp_example.c
  )
endif(NOT ENABLE_NETWORK_TARGETS)


# socket target support
if(NOT ENABLE_SOCKET_TARGETS)
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED FALSE)

  add_function_test(socket_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/socket_unsupported.cpp
  )

elseif(NOT HAVE_SYS_SOCKET_H)
  message("socket targets are not supported without sys/socket.h")
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED FALSE)

  add_function_test(socket_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/socket_unsupported.cpp
  )

else()
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED TRUE)

  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/target/socket.c)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/socket_supported.c)

  list(APPEND WRAPTURE_SPECS ${PROJECT_SOURCE_DIR}/tools/wrapture/socket_target.yml)

  install(FILES
    ${PROJECT_SOURCE_DIR}/include/stumpless/target/socket.h
    DESTINATION "include/stumpless/target"
  )

  add_function_test(socket
    SOURCES
      test/function/target/socket.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
  )

  add_function_test(socket_add_malloc_failure
    SOURCES test/function/startup/target/socket_add_malloc_failure.cpp
  )

  add_function_test(socket_supported
    SOURCES test/function/config/socket_supported.cpp
  )

  add_thread_safety_test(socket
    SOURCES
      test/thread_safety/target/socket.cpp
      $<TARGET_OBJECTS:test_helper_usage>
      $<TARGET_OBJECTS:rfc5424_checker>
  )

  add_example(socket
    ${PROJECT_SOURCE_DIR}/docs/examples/socket/socket_example.c
  )
endif(NOT ENABLE_SOCKET_TARGETS)
# windows event log target support
if(NOT ENABLE_WINDOWS_EVENT_LOG_TARGETS)
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
elseif(ENABLE_WINDOWS_EVENT_LOG_TARGETS AND NOT HAVE_WINDOWS_H)
  message("windows event log targets are not supported without windows.h")
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED TRUE)
endif()

if(NOT STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)
  list(INSERT WRAPTURE_SPECS 0 ${PROJECT_SOURCE_DIR}/tools/wrapture/no_wel_templates.yml)

  add_function_test(wel_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/wel_unsupported.cpp
  )
else()
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/target/wel.c)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/wel_supported.c)

  list(INSERT WRAPTURE_SPECS 0 ${PROJECT_SOURCE_DIR}/tools/wrapture/have_wel_templates.yml)
  list(APPEND WRAPTURE_SPECS ${PROJECT_SOURCE_DIR}/tools/wrapture/wel_target.yml)

  install(FILES
    ${PROJECT_SOURCE_DIR}/include/stumpless/config/wel_supported.h
    DESTINATION "include/stumpless/config"
  )

  install(FILES
    ${PROJECT_SOURCE_DIR}/include/stumpless/target/wel.h
    DESTINATION "include/stumpless/target"
  )

  find_program(MESSAGE_COMPILER_EXE
    NAMES
      mc
      windmc
  )
  if(MESSAGE_COMPILER_EXE STREQUAL "MESSAGE_COMPILER_EXE-NOTFOUND")
    set(MESSAGE_COMPILER_EXE mc)
  endif()

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

  add_function_test(wel
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/target/wel.cpp
      ${PROJECT_BINARY_DIR}/events.rc
  )
  add_dependencies(function-test-wel events)
  target_compile_definitions(function-test-wel
    PUBLIC WEL_EVENTS_LIBRARY_NAME=\"$<TARGET_FILE_NAME:events>\"
  )

  add_function_test(wel_supported
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/config/wel_supported.cpp
      ${PROJECT_BINARY_DIR}/events.rc
  )

  add_thread_safety_test(wel
    SOURCES
      test/thread_safety/target/wel.cpp
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(wel_supported
    SOURCES
      test/thread_safety/config/wel_supported.cpp
      ${PROJECT_BINARY_DIR}/events.rc
      $<TARGET_OBJECTS:test_helper_fixture>
  )

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
    ${PROJECT_SOURCE_DIR}/docs/examples/wel/wel_example.c
    ${PROJECT_BINARY_DIR}/docs/examples/wel/example_events.rc
  )
endif()

# thread safety support
if(NOT ENABLE_THREAD_SAFETY)
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED FALSE)
elseif(NOT HAVE_WINDOWS_H AND (NOT HAVE_PTHREAD_H OR NOT HAVE_STDATOMIC_H))
  message("thread safety is not supported without either windows.h or both pthread.h and stdatomic.h")
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED FALSE)
else()
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED TRUE)
endif()

if(NOT STUMPLESS_THREAD_SAFETY_SUPPORTED)
  list(APPEND STUMPLESS_SOURCES src/config/no_thread_safety.c)
else()
  # thread safety tests
  add_thread_safety_test(buffer
    SOURCES
      test/thread_safety/target/buffer.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(element
    SOURCES
      test/thread_safety/element.cpp
  )

  add_thread_safety_test(entry
    SOURCES
      test/thread_safety/entry.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
  )

  add_thread_safety_test(file
    SOURCES
      test/thread_safety/target/file.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(function
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/thread_safety/target/function.cpp
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(param
    SOURCES
      test/thread_safety/param.cpp
  )

  add_thread_safety_test(stream
    SOURCES
      test/thread_safety/target/stream.cpp
      $<TARGET_OBJECTS:rfc5424_checker>
      $<TARGET_OBJECTS:test_helper_usage>
  )

  add_thread_safety_test(target
    SOURCES
      test/thread_safety/target.cpp
  )

  add_custom_target(check-thread-safety
    DEPENDS ${STUMPLESS_THREAD_SAFETY_TEST_RUNNERS}
  )
endif()


# shared library definition
add_library(stumpless SHARED ${STUMPLESS_SOURCES})
set_target_properties(stumpless PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(stumpless PROPERTIES PUBLIC_HEADER include/stumpless.h)
if(MINGW)
  target_compile_options(stumpless PRIVATE -D__USE_MINGW_ANSI_STDIO)
  set_target_properties(stumpless PROPERTIES PREFIX "")
endif()

if(HAVE_STDATOMIC_H)
  find_library(LIBATOMIC_FOUND atomic)
  if(LIBATOMIC_FOUND)
    target_link_libraries(stumpless PRIVATE atomic)
  endif()
endif()

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


# generating configuration files
configure_file(${PROJECT_SOURCE_DIR}/include/stumpless/config.h.in ${PROJECT_BINARY_DIR}/include/stumpless/config.h)
configure_file(${PROJECT_SOURCE_DIR}/include/private/config.h.in ${PROJECT_BINARY_DIR}/include/private/config.h)



# installation of the library
install(TARGETS stumpless
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include"
  ARCHIVE DESTINATION "lib"
)

install(FILES
  ${PROJECT_BINARY_DIR}/include/stumpless/config.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/element.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/entry.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/error.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/facility.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/generator.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/id.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/memory.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/option.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/param.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/severity.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/target.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/version.h
  DESTINATION "include/stumpless"
)

install(FILES
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/alert.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/crit.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/debug.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/emerg.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/err.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/info.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/mask.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/notice.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/level/warning.h
  DESTINATION "include/stumpless/level"
)

install(FILES
  ${PROJECT_SOURCE_DIR}/include/stumpless/target/buffer.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/target/file.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/target/function.h
  ${PROJECT_SOURCE_DIR}/include/stumpless/target/stream.h
  DESTINATION "include/stumpless/target"
)

include(tools/cmake/cpack.cmake)


# functionality tests
add_function_test(buffer
  SOURCES
    test/function/target/buffer.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:rfc5424_checker>
)

add_function_test(buffer_leak
  SOURCES
    test/function/leak/buffer.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(current_target
  SOURCES test/function/startup/current_target.cpp
)

add_function_test(element
  SOURCES test/function/element.cpp
)

add_function_test(element_leak
  SOURCES test/function/leak/element.cpp
)

add_function_test(entry
  SOURCES test/function/entry.cpp
)

add_function_test(entry_leak
  SOURCES
    test/function/leak/entry.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(entry_memory_failure
  SOURCES test/function/startup/entry_memory_failure.cpp
)

add_function_test(error
  SOURCES test/function/error.cpp
)

add_function_test(error_leak
  SOURCES test/function/leak/error.cpp
)

add_function_test(error_memory_failure
  SOURCES test/function/startup/error_memory_failure.cpp
)

add_function_test(file
  SOURCES
    test/function/target/file.cpp
    $<TARGET_OBJECTS:rfc5424_checker>
)

add_function_test(function
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/target/function.cpp
)

add_function_test(get_error_stream
  SOURCES test/function/startup/get_error_stream.cpp
)

add_function_test(level_all_disabled
  SOURCES test/function/level/all_disabled.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_ALL_LEVELS
)

add_function_test(level_all_enabled
  SOURCES test/function/level/all_enabled.cpp
)

add_function_test(level_disabled_downto_alert
  SOURCES test/function/level/enable_upto_emerg.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ALERT
)

add_function_test(level_disabled_downto_emerg
  SOURCES test/function/level/all_disabled.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_EMERG
)

add_function_test(level_disabled_downto_err
  SOURCES test/function/level/enable_upto_crit.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ERR
)

add_function_test(level_disabled_downto_crit
  SOURCES test/function/level/enable_upto_alert.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_CRIT
)

add_function_test(level_disabled_downto_debug
  SOURCES test/function/level/enable_upto_info.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_DEBUG
)

add_function_test(level_disabled_downto_info
  SOURCES test/function/level/enable_upto_notice.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_INFO
)

add_function_test(level_disabled_downto_notice
  SOURCES test/function/level/enable_upto_warning.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_NOTICE
)

add_function_test(level_disabled_downto_warning
  SOURCES test/function/level/enable_upto_err.cpp
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_WARNING
)

add_function_test(level_enable_upto_alert
  SOURCES test/function/level/enable_upto_alert.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ALERT
)

add_function_test(level_enable_upto_crit
  SOURCES test/function/level/enable_upto_crit.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_CRIT
)

add_function_test(level_enable_upto_debug
  SOURCES test/function/level/all_enabled.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_DEBUG
)

add_function_test(level_enable_upto_emerg
  SOURCES test/function/level/enable_upto_emerg.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_EMERG
)

add_function_test(level_enable_upto_err
  SOURCES test/function/level/enable_upto_err.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ERR
)

add_function_test(level_enable_upto_info
  SOURCES test/function/level/enable_upto_info.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_INFO
)

add_function_test(level_enable_upto_notice
  SOURCES test/function/level/enable_upto_notice.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_NOTICE
)

add_function_test(level_enable_upto_warning
  SOURCES test/function/level/enable_upto_warning.cpp
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_WARNING
)

add_function_test(memory
  SOURCES test/function/memory.cpp
)

add_function_test(param
  SOURCES test/function/param.cpp
)

add_function_test(perror
  SOURCES test/function/startup/perror.cpp
)

add_function_test(stream
  SOURCES
    test/function/target/stream.cpp
    $<TARGET_OBJECTS:rfc5424_checker>
)

add_function_test(target
  SOURCES
    test/function/target.cpp
    $<TARGET_OBJECTS:rfc5424_checker>
)

add_function_test(target_leak
  SOURCES test/function/leak/target.cpp
)

add_function_test(version
  SOURCES test/function/version.cpp
)

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE}
  DEPENDS ${STUMPLESS_FUNCTION_TESTS}
)


# examples
add_example(basic
  ${PROJECT_SOURCE_DIR}/docs/examples/basic/basic_example.c
)

add_example(entry
  ${PROJECT_SOURCE_DIR}/docs/examples/entry/entry_example.c
)

add_example(file
  ${PROJECT_SOURCE_DIR}/docs/examples/file/file_example.c
)

add_example(function
  ${PROJECT_SOURCE_DIR}/docs/examples/function/function_example.c
)

add_example(severity_level
  ${PROJECT_SOURCE_DIR}/docs/examples/severity_level/severity_level_example.c
)

add_example(stream
  ${PROJECT_SOURCE_DIR}/docs/examples/stream/stream_example.c
)

add_custom_target(examples
  DEPENDS ${STUMPLESS_EXAMPLE_RUNNERS}
)


# performance tests
add_performance_test(element
  SOURCES test/performance/element.cpp
)

add_performance_test(entry
  SOURCES test/performance/entry.cpp
)

add_performance_test(function
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/target/function.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(target
  SOURCES test/performance/target.cpp
)

add_custom_target(bench
  DEPENDS ${STUMPLESS_PERFORMANCE_TEST_RUNNERS}
)


# c++ support
if(ENABLE_CPP)
  if(HAVE_WRAPTURE)
    include(tools/cmake/cpp.cmake)
  else()
    message(WARNING "C++ library cannot be built without wrapture. You can install wrapture using standard gem installation tools, e.g. 'gem install wrapture'")
  endif(HAVE_WRAPTURE)
endif()


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
