cmake_minimum_required(VERSION 3.21...3.31)

if(POLICY CMP0135)
  # for ExternalProject_Add and FetchContent_Declare()
  # CMake version 3.24
  cmake_policy(SET CMP0135 NEW)
endif()

project(stumpless
  VERSION 3.0.0
  DESCRIPTION "a fast and feature-rich logging library for C"
  HOMEPAGE_URL "https://goatshriek.github.io/stumpless/"
  LANGUAGES C
)

include("${PROJECT_SOURCE_DIR}/tools/cmake/options.cmake")


# single file build paths
set(SINGLE_SOURCE_FILE "${PROJECT_BINARY_DIR}/stumpless.c")
set(SINGLE_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include/single_file")
set(SINGLE_HEADER_FILE "${SINGLE_INCLUDE_DIR}/stumpless.h")


# load modules
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CTest)
include(FindDoxygen QUIET)
include(GNUInstallDirs)

if(BUILD_TESTING OR BUILD_BENCHMARKING)
  include(FetchContent)

  # C++ is required for testing and benchmarking
  enable_language(CXX)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

if(BUILD_PYTHON)
  include(ExternalProject)
endif()


# find and/or get external dependencies
if(BUILD_TESTING)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/test.cmake")
endif()

if(BUILD_BENCHMARKING)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/benchmark.cmake")
endif()

include("${PROJECT_SOURCE_DIR}/tools/cmake/example.cmake")
include("${PROJECT_SOURCE_DIR}/tools/cmake/l10n.cmake")
include("${PROJECT_SOURCE_DIR}/tools/cmake/swig.cmake")



# building configuration
if(EXISTS "${SQLITE3_INCLUDE_PATH}")
  file(COPY
    "${SQLITE3_INCLUDE_PATH}"
    DESTINATION "${PROJECT_BINARY_DIR}/include"
  )
endif()

check_include_files(pthread.h HAVE_PTHREAD_H)
check_include_files(stdatomic.h HAVE_STDATOMIC_H)
check_include_files(sqlite3.h HAVE_SQLITE3_H)
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

# while these checks aim to distinguish between windows sockets and others,
# we don't directly check for win32, as on win32 socket operations are handled
# directly through return values
check_symbol_exists(SO_NOSIGPIPE "sys/socket.h" HAVE_SO_NOSIGPIPE)
check_symbol_exists(MSG_NOSIGNAL "sys/socket.h" HAVE_MSG_NOSIGNAL)

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
  "${PROJECT_SOURCE_DIR}/src/cache.c"
  "${PROJECT_SOURCE_DIR}/src/element.c"
  "${PROJECT_SOURCE_DIR}/src/entry.c"
  "${PROJECT_SOURCE_DIR}/src/error.c"
  "${PROJECT_SOURCE_DIR}/src/facility.c"
  "${PROJECT_SOURCE_DIR}/src/filter.c"
  "${PROJECT_SOURCE_DIR}/src/formatter.c"
  "${PROJECT_SOURCE_DIR}/src/inthelper.c"
  "${PROJECT_SOURCE_DIR}/src/log.c"
  "${PROJECT_SOURCE_DIR}/src/memory.c"
  "${PROJECT_SOURCE_DIR}/src/param.c"
  "${PROJECT_SOURCE_DIR}/src/prival.c"
  "${PROJECT_SOURCE_DIR}/src/severity.c"
  "${PROJECT_SOURCE_DIR}/src/strbuilder.c"
  "${PROJECT_SOURCE_DIR}/src/strhelper.c"
  "${PROJECT_SOURCE_DIR}/src/target.c"
  "${PROJECT_SOURCE_DIR}/src/target/buffer.c"
  "${PROJECT_SOURCE_DIR}/src/target/file.c"
  "${PROJECT_SOURCE_DIR}/src/target/function.c"
  "${PROJECT_SOURCE_DIR}/src/target/stream.c"
  "${PROJECT_SOURCE_DIR}/src/version.c"
  "${PROJECT_SOURCE_DIR}/src/validate.c"
)


# wrapture support
set(WRAPTURE_SPECS
  # template files must be first
  "${PROJECT_SOURCE_DIR}/tools/wrapture/error_templates.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/target_templates.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/buffer_target.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/element.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/entry.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/error.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/facility.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/file_target.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/function_target.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/memory.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/param.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/severity.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/stream_target.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/target.yml"
  "${PROJECT_SOURCE_DIR}/tools/wrapture/version.yml"
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
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(SUPPORT_ABSTRACT_SOCKET_NAMES TRUE)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/abstract_socket_names_supported.c"
  )
else()
  set(SUPPORT_ABSTRACT_SOCKET_NAMES FALSE)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/abstract_socket_names_unsupported.c"
  )
endif()

if(HAVE_FOPEN_S)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_fopen_s.c"
  )
endif(HAVE_FOPEN_S)

if(HAVE_PTHREAD_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_pthread.c"
  )
endif()

if(HAVE_STDATOMIC_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_stdatomic.c"
  )
endif()

if(HAVE_UNISTD_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_unistd.c"
  )
endif(HAVE_UNISTD_H)

if(HAVE_VSNPRINTF_S)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_vsnprintf_s.c"
  )
else()
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/no_vsnprintf_s.c"
  )
endif(HAVE_VSNPRINTF_S)

if(NOT HAVE_WCSRTOMBS_S)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/no_wcsrtombs_s.c"
  )
endif()

if(HAVE_WINDOWS_H)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_windows.c"
  )
endif(HAVE_WINDOWS_H)

if(WIN32)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/windows/stumpless.def"
  )
endif(WIN32)

if(HAVE_WINDOWS_H AND HAVE_SPRINTF_S)
  set(SUPPORT_WINDOWS_GET_NOW TRUE)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/windows_get_now_supported.c"
  )
endif()

if(HAVE_GMTIME_R)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_gmtime_r.c"
  )
elseif(NOT SUPPORT_WINDOWS_GET_NOW AND HAVE_GMTIME)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_gmtime.c"
  )
else()
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/no_gmtime.c"
  )
endif()

if(HAVE_UNISTD_GETHOSTNAME)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_unistd_gethostname.c"
  )
elseif(NOT HAVE_WINSOCK2_H)
  # need the fallback gethostname definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(HAVE_UNISTD_SYSCONF AND HAVE_UNISTD_SC_PAGESIZE)
  set(SUPPORT_UNISTD_SYSCONF_GETPAGESIZE TRUE)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/unistd_sysconf_getpagesize_supported.c"
  )
elseif(HAVE_UNISTD_GETPAGESIZE)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/have_unistd_getpagesize.c"
  )
elseif(NOT HAVE_WINDOWS_H)
  # need the fallback getpagesize definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NOT HAVE_UNISTD_H AND NOT HAVE_WINDOWS_H)
  # need the fallback getpid definition in this case
  set(NEED_FALLBACK TRUE)
endif()

if(NEED_FALLBACK)
  list(APPEND STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/config/fallback.c")
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/chain.cmake")
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/journald.cmake")
else()
  add_function_test(journald_unsupported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/config/journald_unsupported.cpp"
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/network.cmake")
else()
  if(WIN32)
    list(
      APPEND STUMPLESS_SOURCES
      "${PROJECT_SOURCE_DIR}/src/config/network_unsupported.c"
    )
  endif(WIN32)

  add_function_test(network_unsupported
    SOURCES "${PROJECT_SOURCE_DIR}/test/function/config/network_unsupported.cpp"
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/sqlite3.cmake")
else()
  list(APPEND
    STUMPLESS_SOURCES "${PROJECT_SOURCE_DIR}/src/config/sqlite3_unsupported.c"
  )

  add_function_test(sqlite3_unsupported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/config/sqlite3_unsupported.cpp"
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/wel.cmake")
else()
  list(INSERT WRAPTURE_SPECS 0 "${PROJECT_SOURCE_DIR}/tools/wrapture/no_wel_templates.yml")

  add_function_test(wel_unsupported
    SOURCES
      "${PROJECT_SOURCE_DIR}/test/function/config/wel_unsupported.cpp"
      $<TARGET_OBJECTS:test_helper_fixture>
  )
endif()


# thread safety support
if(NOT STUMPLESS_THREAD_SAFETY_SUPPORTED)
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/thread_safety_unsupported.c"
  )
else()
  list(
    APPEND STUMPLESS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/config/thread_safety_supported.c"
  )

  include("${PROJECT_SOURCE_DIR}/tools/cmake/thread_safety_tests.cmake")
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
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_BINARY_DIR}/include"
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
include("${PROJECT_SOURCE_DIR}/tools/cmake/config_files.cmake")

# installation of the library
install(TARGETS stumpless
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(INSTALL_HEADERS)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/install_headers.cmake")
endif()

include("${PROJECT_SOURCE_DIR}/tools/cmake/cpack.cmake")

include(FindPkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  configure_file(
    "${PROJECT_SOURCE_DIR}/tools/pkg-config/libstumpless.pc.in"
    "${PROJECT_BINARY_DIR}/tools/pkg-config/libstumpless.pc"
    @ONLY
  )

  install(
    FILES "${PROJECT_BINARY_DIR}/tools/pkg-config/libstumpless.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
  )
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
  include("${PROJECT_SOURCE_DIR}/tools/cmake/install_html.cmake")
endif()


# installation of manpages if enabled and supported
if(INCLUDE_MANPAGES_IN_INSTALL)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/install_manpages.cmake")
endif()

include("${PROJECT_SOURCE_DIR}/tools/cmake/examples.cmake")

if(BUILD_TESTING)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/function_tests.cmake")
endif()

if(BUILD_BENCHMARKING)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/performance_tests.cmake")
endif()


if(FUZZ)
  include("${PROJECT_SOURCE_DIR}/tools/cmake/fuzz_tests.cmake")
endif()


# single file generation
include("${PROJECT_SOURCE_DIR}/tools/cmake/single_file.cmake")


# c++ library build
if(BUILD_CPP)
  if(HAVE_WRAPTURE)
    include("${PROJECT_SOURCE_DIR}/tools/cmake/cpp.cmake")
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
