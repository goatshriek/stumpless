cmake_minimum_required(VERSION 3.2.3)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(stumpless
  VERSION 3.0.0
)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://goatshriek.github.io/stumpless/")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

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

option(ENABLE_CHAIN_TARGETS "support chain targets" ON)
option(ENABLE_JOURNALD_TARGETS "support systemd journald service targets" ON)
option(ENABLE_NETWORK_TARGETS "support network targets" ON)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(ENABLE_SQLITE3_TARGETS "support sqlite3 targets" ON)
option(ENABLE_WINDOWS_EVENT_LOG_TARGETS "support windows event log targets" ON)

option(INSTALL_EXAMPLES "install examples" ON)
option(INSTALL_HEADERS "install header files" ON)
option(INSTALL_HTML "install html documentation" ON)
option(INSTALL_MANPAGES "install generated manpages" ON)

option(COVERAGE "Include coverage information" OFF)
option(FUZZ "Support fuzzing with libFuzzer" OFF)

string(CONCAT enable_deprecation_warnings_help_string
  "Print warnings to the standard output when deprecated functionality is used."
)
option(ENABLE_DEPRECATION_WARNINGS ${enable_deprecation_warnings_help_string} ON)


# default settings
set(CHAIN_TARGET_ARRAY_LENGTH 4
  CACHE STRING "the chain target static array size"
)

string(CONCAT default_facility_help_string
  "The facility code to use for messages where one is not explicitly provided."
)
set(DEFAULT_FACILITY "STUMPLESS_FACILITY_USER"
  CACHE STRING ${default_facility_help_string}
)

string(CONCAT default_file_help_string
  "The name of the file opened if the default target is to a file."
)
set(DEFAULT_FILE "stumpless-default.log"
  CACHE STRING "${default_file_help_string}"
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

string(CONCAT sqlite3_src_path_help_string
  "The path to a SQLite3 source file, referred to as an 'amalgamation' in "
  "SQLite documentation. If this variable is set, it is used to link SQLite3 "
  "statically with Stumpless, instead of the default dynamic linking."
)
set(SQLITE3_SRC_PATH ""
  CACHE FILEPATH ${sqlite3_src_path_help_string}
)

string(CONCAT sqlite3_include_path_help_string
  "The path to the sqlite3.h header matching the source file provided in "
  "SQLITE3_SRC_PATH. If the header is already in the include directores, this "
  "does not need to be specified."
)
set(SQLITE3_INCLUDE_PATH ""
  CACHE FILEPATH ${sqlite3_include_path_help_string}
)

set(SQLITE3_DEFAULT_TABLE_NAME "logs"
  CACHE STRING "the name of the table used by default for SQLite3 targets"
)

set(SQLITE3_RETRY_MAX 3
  CACHE STRING "the maximum number of retries on SQLite3 operations"
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


# single file build paths
set(SINGLE_SOURCE_FILE "${PROJECT_BINARY_DIR}/stumpless.c")
set(SINGLE_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include/single_file")
set(SINGLE_HEADER_FILE "${SINGLE_INCLUDE_DIR}/stumpless.h")


# load modules
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(ExternalProject)
include(FindDoxygen QUIET)
include(GNUInstallDirs)


# load utilities
include(tools/cmake/google_libs.cmake)
include(tools/cmake/add_found_library.cmake)
# the above two need to be before benchmark and gtest

include(tools/cmake/benchmark.cmake)
include(tools/cmake/example.cmake)
include(tools/cmake/gtest.cmake)
include(tools/cmake/l10n.cmake)
include(tools/cmake/swig.cmake)
include(tools/cmake/test.cmake)


# building configuration
if(EXISTS ${SQLITE3_INCLUDE_PATH})
  file(COPY
    "${SQLITE3_INCLUDE_PATH}"
    DESTINATION "${PROJECT_BINARY_DIR}/include"
  )
endif()

check_include_files(pthread.h HAVE_PTHREAD_H)
check_include_files(stdatomic.h HAVE_STDATOMIC_H)
check_include_files("sqlite3.h" HAVE_SQLITE3_H)
check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_files(syslog.h STUMPLESS_SYSLOG_H_COMPATIBLE)
check_include_files(systemd/sd-journal.h HAVE_SYSTEMD_SD_JOURNAL_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(windows.h HAVE_WINDOWS_H)
check_include_files(winsock2.h HAVE_WINSOCK2_H)

check_symbol_exists(fopen_s stdio.h HAVE_FOPEN_S)
check_symbol_exists(getaddrinfo netdb.h HAVE_GETADDRINFO)
check_symbol_exists(gethostname unistd.h HAVE_UNISTD_GETHOSTNAME)
check_symbol_exists(gethostbyname netdb.h HAVE_GETHOSTBYNAME)
check_symbol_exists(gethostbyname2 netdb.h HAVE_GETHOSTBYNAME2)
check_symbol_exists(getpagesize unistd.h HAVE_UNISTD_GETPAGESIZE)
check_symbol_exists(gmtime time.h HAVE_GMTIME)
check_symbol_exists(gmtime_r time.h HAVE_GMTIME_R)
check_symbol_exists(_SC_PAGESIZE unistd.h HAVE_UNISTD_SC_PAGESIZE)
check_symbol_exists(sprintf_s stdio.h HAVE_SPRINTF_S)
check_symbol_exists(sysconf unistd.h HAVE_UNISTD_SYSCONF)
check_symbol_exists(vsnprintf_s stdio.h HAVE_VSNPRINTF_S)
check_symbol_exists(wcsrtombs_s wchar.h HAVE_WCSRTOMBS_S)
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


# standard source files
set(STUMPLESS_SOURCES
  ${PROJECT_SOURCE_DIR}/src/cache.c
  ${PROJECT_SOURCE_DIR}/src/element.c
  ${PROJECT_SOURCE_DIR}/src/entry.c
  ${PROJECT_SOURCE_DIR}/src/error.c
  ${PROJECT_SOURCE_DIR}/src/facility.c
  ${PROJECT_SOURCE_DIR}/src/filter.c
  ${PROJECT_SOURCE_DIR}/src/formatter.c
  ${PROJECT_SOURCE_DIR}/src/inthelper.c
  ${PROJECT_SOURCE_DIR}/src/log.c
  ${PROJECT_SOURCE_DIR}/src/memory.c
  ${PROJECT_SOURCE_DIR}/src/param.c
  ${PROJECT_SOURCE_DIR}/src/prival.c
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


# documentation and doxygen steup
set(PROJECT_DOCS_DIR "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}")
set(DOXYGEN_MANPAGES
  "${PROJECT_DOCS_DIR}/man/man3/stumpless.h.3"
  "${PROJECT_DOCS_DIR}/man/man3/config.h.3"
)

if(DOXYGEN_FOUND)
  set(INCLUDE_HTML_IN_INSTALL ${INSTALL_HTML})
  set(INCLUDE_MANPAGES_IN_INSTALL ${INSTALL_MANPAGES})
else()
  if(INSTALL_HTML)
    message("doxygen is required to generate and install html documentation")
  endif()

  if(INSTALL_MANPAGES)
    message("doxygen is required to generate and install manpages")
  endif()

  set(INCLUDE_HTML_IN_INSTALL FALSE)
  set(INCLUDE_MANPAGES_IN_INSTALL FALSE)
endif()

if(${INCLUDE_HTML_IN_INSTALL} OR ${INCLUDE_MANPAGES_IN_INSTALL})
  # we need to do this before any other install commands that depend on the
  # html or manpages generated by doxygen, so that they are generated before use
  install(CODE
    "execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target docs)"
  )
endif()


# configuration-specific source files

# we don't check for win32 as on win32 socket operations are handled directly through return values
# Check if SO_NOSIGPIPE exists
check_symbol_exists(SO_NOSIGPIPE "sys/socket.h" HAVE_SO_NOSIGPIPE)

# Check if MSG_NOSIGNAL exists
check_symbol_exists(MSG_NOSIGNAL "sys/socket.h" HAVE_MSG_NOSIGNAL)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(SUPPORT_ABSTRACT_SOCKET_NAMES TRUE)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/abstract_socket_names_supported.c)
else()
  set(SUPPORT_ABSTRACT_SOCKET_NAMES FALSE)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/abstract_socket_names_unsupported.c)
endif()

if(HAVE_FOPEN_S)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_fopen_s.c)
endif(HAVE_FOPEN_S)

if(HAVE_PTHREAD_H)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_pthread.c)
endif()

if(HAVE_STDATOMIC_H)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_stdatomic.c)
endif()

if(HAVE_UNISTD_H)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_unistd.c)
endif(HAVE_UNISTD_H)

if(HAVE_VSNPRINTF_S)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_vsnprintf_s.c)
else()
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/no_vsnprintf_s.c)
endif(HAVE_VSNPRINTF_S)

if(NOT HAVE_WCSRTOMBS_S)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/no_wcsrtombs_s.c)
endif()

if(HAVE_WINDOWS_H)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_windows.c)
endif(HAVE_WINDOWS_H)

if(WIN32)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/windows/stumpless.def)
endif(WIN32)

if(HAVE_WINDOWS_H AND HAVE_SPRINTF_S)
  set(SUPPORT_WINDOWS_GET_NOW TRUE)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/windows_get_now_supported.c)
endif()

if(HAVE_GMTIME_R)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_gmtime_r.c)
elseif(NOT SUPPORT_WINDOWS_GET_NOW AND HAVE_GMTIME)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_gmtime.c)
else()
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/no_gmtime.c)
endif()

if(HAVE_UNISTD_GETHOSTNAME)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_unistd_gethostname.c)
elseif(NOT HAVE_WINSOCK2_H)
  # need the fallback gethostname definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(HAVE_UNISTD_SYSCONF AND HAVE_UNISTD_SC_PAGESIZE)
  set(SUPPORT_UNISTD_SYSCONF_GETPAGESIZE TRUE)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/unistd_sysconf_getpagesize_supported.c)
elseif(HAVE_UNISTD_GETPAGESIZE)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/have_unistd_getpagesize.c)
elseif(NOT HAVE_WINDOWS_H)
  # need the fallback getpagesize definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NOT HAVE_UNISTD_H AND NOT HAVE_WINDOWS_H)
  # need the fallback getpid definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NEED_FALLBACK)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/fallback.c)
endif()


# thread safety support check
if(NOT ENABLE_THREAD_SAFETY)
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED FALSE)
elseif(NOT HAVE_WINDOWS_H AND (NOT HAVE_PTHREAD_H OR NOT HAVE_STDATOMIC_H))
  message("thread safety is not supported without either windows.h or both pthread.h and stdatomic.h")
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED FALSE)
else()
  set(STUMPLESS_THREAD_SAFETY_SUPPORTED TRUE)
endif()


# chain target support
if(NOT ENABLE_CHAIN_TARGETS)
  set(STUMPLESS_CHAIN_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_CHAIN_TARGETS_SUPPORTED TRUE)
endif()

if(STUMPLESS_CHAIN_TARGETS_SUPPORTED)
  include(tools/cmake/chain.cmake)
else()
  if(WIN32)
    list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/config/chain_unsupported.c")
  endif(WIN32)
endif()


# journald target support
if(NOT ENABLE_JOURNALD_TARGETS)
  set(STUMPLESS_JOURNALD_TARGETS_SUPPORTED FALSE)
elseif(ENABLE_JOURNALD_TARGETS AND NOT HAVE_SYSTEMD_SD_JOURNAL_H)
  message("journald targets are not supported without systemd/sd-journal.h")
  set(STUMPLESS_JOURNALD_TARGETS_SUPPORTED FALSE)
else()
  find_library(LIBSYSTEMD_FOUND systemd)
  if(LIBSYSTEMD_FOUND)
    set(STUMPLESS_JOURNALD_TARGETS_SUPPORTED TRUE)
  else()
    message("journald targets are not supported without libsystemd")
    set(STUMPLESS_JOURNALD_TARGETS_SUPPORTED FALSE)
  endif()
endif()

if(STUMPLESS_JOURNALD_TARGETS_SUPPORTED)
  include(tools/cmake/journald.cmake)
else()
  add_function_test(journald_unsupported
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/config/journald_unsupported.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()


# network target support
if(NOT ENABLE_NETWORK_TARGETS)
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED FALSE)
elseif(NOT HAVE_WINSOCK2_H AND NOT HAVE_SYS_SOCKET_H)
  message("network targets are not supported without either winsock2.h or sys/socket.h")
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_NETWORK_TARGETS_SUPPORTED TRUE)
endif()

if(STUMPLESS_NETWORK_TARGETS_SUPPORTED)
  include(tools/cmake/network.cmake)
else()
  if(WIN32)
    list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/network_unsupported.c)
  endif(WIN32)

  add_function_test(network_unsupported
    SOURCES ${PROJECT_SOURCE_DIR}/test/function/config/network_unsupported.cpp
  )
endif()


# socket target support
if(NOT ENABLE_SOCKET_TARGETS)
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED FALSE)
elseif(NOT HAVE_SYS_SOCKET_H)
  message("socket targets are not supported without sys/socket.h")
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_SOCKET_TARGETS_SUPPORTED TRUE)
endif()

if(STUMPLESS_SOCKET_TARGETS_SUPPORTED)
  include(tools/cmake/socket.cmake)
else()
  add_function_test(socket_unsupported
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/config/socket_unsupported.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()


# sqlite3 target support
if(NOT ENABLE_SQLITE3_TARGETS)
  set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED FALSE)
elseif(SQLITE3_SRC_PATH)
  if(NOT EXISTS "${SQLITE3_SRC_PATH}")
    message("the specified sqlite3 source file does not exist")
    set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED FALSE)
  else()
    list(APPEND STUMPLESS_SOURCES "${SQLITE3_SRC_PATH}")
    set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED TRUE)
  endif()
elseif(NOT HAVE_SQLITE3_H)
  message("sqlite3 targets are not supported without sqlite3.h")
  set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED FALSE)
else()
  find_library(LIBSQLITE3_FOUND sqlite3)
  if(LIBSQLITE3_FOUND)
    set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED TRUE)
  else()
    message("sqlite3 targets are not supported without libsqlite3")
    set(STUMPLESS_SQLITE3_TARGETS_SUPPORTED FALSE)
  endif()
endif()

if(STUMPLESS_SQLITE3_TARGETS_SUPPORTED)
  include(tools/cmake/sqlite3.cmake)
else()
  list(APPEND
    STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/config/sqlite3_unsupported.c"
  )

  add_function_test(sqlite3_unsupported
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/config/sqlite3_unsupported.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()


# windows event log target support
if(NOT ENABLE_WINDOWS_EVENT_LOG_TARGETS)
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
elseif(ENABLE_WINDOWS_EVENT_LOG_TARGETS AND NOT HAVE_WINDOWS_H)
  message("windows event log targets are not supported without windows.h")
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED TRUE)
endif()

if(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)
  include(tools/cmake/wel.cmake)
else()
  list(INSERT WRAPTURE_SPECS 0 ${PROJECT_SOURCE_DIR}/tools/wrapture/no_wel_templates.yml)

  add_function_test(wel_unsupported
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/config/wel_unsupported.cpp
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()


# thread safety support
if(NOT STUMPLESS_THREAD_SAFETY_SUPPORTED)
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/thread_safety_unsupported.c)
else()
  list(APPEND STUMPLESS_SOURCES ${PROJECT_SOURCE_DIR}/src/config/thread_safety_supported.c)

  # thread safety tests
  add_thread_safety_test(buffer
    SOURCES
      test/thread_safety/target/buffer.cpp
      $<TARGET_OBJECTS:test_helper_rfc5424>
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
      $<TARGET_OBJECTS:test_helper_rfc5424>
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
      $<TARGET_OBJECTS:test_helper_rfc5424>
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


# library definition
add_library(stumpless ${STUMPLESS_SOURCES})
set_target_properties(stumpless PROPERTIES VERSION ${PROJECT_VERSION})

target_link_libraries(stumpless PRIVATE ${STUMPLESS_LINK_LIBRARIES})

if(MINGW)
  target_compile_options(stumpless PRIVATE -D__USE_MINGW_ANSI_STDIO)
  set_target_properties(stumpless PROPERTIES PREFIX "")
endif()

if(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)
  add_dependencies(stumpless default_events)
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

if(FUZZ)
  target_compile_options(stumpless PRIVATE "-fsanitize=fuzzer,address")
  target_link_libraries(stumpless PRIVATE "-fsanitize=fuzzer,address")
endif(FUZZ)

target_include_directories(stumpless
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
)


# optimization options
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set(PUBLIC_FUNCTION_DECORATION "__attribute__ ((visibility (\"default\")))")
  set(UNLIKELY_FUNCTION "__builtin_expect( ( EXPRESSION ), 0 )")
  set(COLD_FUNCTION "__attribute__ ((cold))")
else()
  set(PUBLIC_FUNCTION_DECORATION "")
  set(UNLIKELY_FUNCTION "( EXPRESSION )")
  set(COLD_FUNCTION "")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(stumpless
      PRIVATE "-fvisibility=hidden")

    target_link_libraries(stumpless
      PRIVATE "-s")

    if(NOT CYGWIN)
      target_compile_options(stumpless
        PRIVATE "-flto")

      target_link_libraries(stumpless
        PRIVATE "-flto")
    endif()
  endif()
endif()



# generating configuration files
set(FUZZ_CORPORA_DIR ${PROJECT_SOURCE_DIR}/test/corpora)
configure_file(${PROJECT_SOURCE_DIR}/include/stumpless/config.h.in ${PROJECT_BINARY_DIR}/include/stumpless/config.h)
configure_file(${PROJECT_SOURCE_DIR}/include/private/config.h.in ${PROJECT_BINARY_DIR}/include/private/config.h)
configure_file(${PROJECT_SOURCE_DIR}/include/test/config.hpp.in ${PROJECT_BINARY_DIR}/include/test/config.hpp)
configure_file(${PROJECT_SOURCE_DIR}/tools/portage/libstumpless.ebuild.in
  ${PROJECT_BINARY_DIR}/tools/portage/libstumpless-${PROJECT_VERSION}.ebuild
  @ONLY
)
configure_file(${PROJECT_SOURCE_DIR}/tools/portage/libstumpless.ebuild.in
  ${PROJECT_BINARY_DIR}/tools/portage/libstumpless-9999.ebuild
  @ONLY
)


# generating level header files
set(LEVEL_NAME_UPCASE "ALERT")
set(LEVEL_NAME_DOWNCASE "alert")
set(LEVEL_SHORTNAME "a")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "CRIT")
set(LEVEL_NAME_DOWNCASE "crit")
set(LEVEL_SHORTNAME "c")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "DEBUG")
set(LEVEL_NAME_DOWNCASE "debug")
set(LEVEL_SHORTNAME "d")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "EMERG")
set(LEVEL_NAME_DOWNCASE "emerg")
set(LEVEL_SHORTNAME "em")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "ERR")
set(LEVEL_NAME_DOWNCASE "err")
set(LEVEL_SHORTNAME "er")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "INFO")
set(LEVEL_NAME_DOWNCASE "info")
set(LEVEL_SHORTNAME "i")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "NOTICE")
set(LEVEL_NAME_DOWNCASE "notice")
set(LEVEL_SHORTNAME "n")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "WARNING")
set(LEVEL_NAME_DOWNCASE "warning")
set(LEVEL_SHORTNAME "w")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "TRACE")
set(LEVEL_NAME_DOWNCASE "trace")
set(LEVEL_SHORTNAME "t")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)


# installation of the library
install(TARGETS stumpless
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(INSTALL_HEADERS)
  include(tools/cmake/install_headers.cmake)
endif()

include(tools/cmake/cpack.cmake)

include(FindPkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  configure_file(
    "${PROJECT_SOURCE_DIR}/tools/pkg-config/libstumpless.pc.in"
    "${PROJECT_BINARY_DIR}/tools/pkg-config/libstumpless.pc"
    @ONLY
  )

  install(FILES "${PROJECT_BINARY_DIR}/tools/pkg-config/libstumpless.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
endif()


# installation of examples if enabled
if(INSTALL_EXAMPLES)
  install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/docs/examples"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/doc/libstumpless"
  )
endif()


# installation of html if enabled and supported
if(INCLUDE_HTML_IN_INSTALL)
  include(tools/cmake/install_html.cmake)
endif()


# installation of manpages if enabled and supported
if(INCLUDE_MANPAGES_IN_INSTALL)
  include(tools/cmake/install_manpages.cmake)
endif()


# functionality tests
add_function_test(buffer
  SOURCES
    test/function/target/buffer.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
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
  SOURCES
    test/function/entry.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
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
  SOURCES
    test/function/error.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(error_leak
  SOURCES test/function/leak/error.cpp
)

add_function_test(error_memory_failure
  SOURCES test/function/startup/error_memory_failure.cpp
)

add_function_test(facility
  SOURCES test/function/facility.cpp
)

add_function_test(file
  SOURCES
    test/function/target/file.cpp
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_function_test(filter
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/filter.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(function
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/target/function.cpp
)

add_function_test(get_error_stream
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/startup/get_error_stream.cpp
)

add_function_test(level_all_disabled
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/all_disabled.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_ALL_LEVELS
)

add_function_test(level_all_enabled
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/all_enabled.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_function_test(level_disabled_downto_alert
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_emerg.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ALERT
)

add_function_test(level_disabled_downto_emerg
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/all_disabled.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_EMERG
)

add_function_test(level_disabled_downto_err
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_crit.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_ERR
)

add_function_test(level_disabled_downto_crit
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_alert.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_CRIT
)

add_function_test(level_disabled_downto_debug
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_info.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_DEBUG
)

add_function_test(level_disabled_downto_info
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_notice.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_INFO
)

add_function_test(level_disabled_downto_notice
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_warning.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_NOTICE
)

add_function_test(level_disabled_downto_trace
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_debug.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_TRACE
)

add_function_test(level_disabled_downto_warning
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_err.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_DISABLE_DOWNTO_WARNING
)

add_function_test(level_enable_upto_alert
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_alert.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ALERT
)

add_function_test(level_enable_upto_crit
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_crit.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_CRIT
)

add_function_test(level_enable_upto_debug
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_debug.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_DEBUG
)

add_function_test(level_enable_upto_emerg
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_emerg.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_EMERG
)

add_function_test(level_enable_upto_err
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_err.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_ERR
)

add_function_test(level_enable_upto_info
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_info.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_INFO
)

add_function_test(level_enable_upto_notice
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_notice.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_NOTICE
)

add_function_test(level_enable_upto_trace
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/all_enabled.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_TRACE
)

add_function_test(level_enable_upto_warning
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/level/enable_upto_warning.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
  COMPILE_DEFINITIONS STUMPLESS_ENABLE_UPTO_WARNING
)

add_function_test(log
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/log.cpp
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_function_test(memory
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/memory.cpp
)

add_function_test(param
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/param.cpp
)

add_function_test(perror
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/startup/perror.cpp
)

add_function_test(severity
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/severity.cpp
)

add_function_test(stream
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/target/stream.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_function_test(target
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/target.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
    $<TARGET_OBJECTS:test_helper_rfc5424>
)

add_function_test(target_leak
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/leak/target.cpp
)

add_function_test(version
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/version.cpp
)

add_function_test(prival
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/prival.cpp
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

add_example(filter
  ${PROJECT_SOURCE_DIR}/docs/examples/filter/filter_example.c
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

add_performance_test(prival
  SOURCES "${PROJECT_SOURCE_DIR}/test/performance/prival.cpp"
)

add_performance_test(entry
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/entry.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(function
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/target/function.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(buffer
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/target/buffer.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(log
  SOURCES test/performance/log.cpp
)

add_performance_test(param
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/param.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(target
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/performance/target.cpp
    $<TARGET_OBJECTS:test_helper_fixture>
)

add_performance_test(version
  SOURCES ${PROJECT_SOURCE_DIR}/test/performance/version.cpp
)

add_custom_target(bench
  DEPENDS ${STUMPLESS_PERFORMANCE_TEST_RUNNERS}
)

if(FUZZ)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fuzz-corpora)

  add_fuzz_test(add_message_str
    SOURCES ${PROJECT_SOURCE_DIR}/test/fuzz/add_message_str.cpp
    CORPUS_NAME cstring
  )

  add_fuzz_test(stump_str
    SOURCES ${PROJECT_SOURCE_DIR}/test/fuzz/stump_str.cpp
    CORPUS_NAME cstring
  )

  add_custom_target(fuzz
    DEPENDS ${STUMPLESS_FUZZ_TESTS}
  )
endif()


# single file generation
include(tools/cmake/single_file.cmake)


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


# doxygen build target
if(DOXYGEN_FOUND)
  include(tools/cmake/doxygen.cmake)
endif()
