cmake_minimum_required(VERSION 3.0.2)

project(stumpless VERSION 1.2.0)

option(BUILD_PYTHON "include the python libary" OFF)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(COVERAGE "Include coverage information" OFF)

# load modules
include(CheckIncludeFiles)
include(CheckSymbolExists)

# load utilities
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

# adding in the gtest support
find_package(Threads REQUIRED)
include(ExternalProject)

ExternalProject_Add(gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
    INSTALL_COMMAND ""
)

set_target_properties(gtest
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/${CMAKE_CFG_INTDIR}/gtestd.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )
  else()
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/${CMAKE_CFG_INTDIR}/gtest.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
  set_target_properties(libgtest PROPERTIES
      "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
      "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )
endif(WIN32)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/${CMAKE_CFG_INTDIR}/gmockd.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )
  else()
    set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/${CMAKE_CFG_INTDIR}/gmock.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
  set_target_properties(libgmock PROPERTIES
      "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
      "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )
endif(WIN32)

include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

# test suites
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

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE}
  DEPENDS ${STUMPLESS_FUNCTION_TEST_TARGETS}
)


# google benchmark support
ExternalProject_Add(benchmark
    URL https://github.com/google/benchmark/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
    CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=RELEASE
    INSTALL_COMMAND ""
)

set_target_properties(benchmark
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

ExternalProject_Get_Property(benchmark source_dir binary_dir)

add_library(libbenchmark IMPORTED STATIC GLOBAL)
add_dependencies(libbenchmark benchmark)

set_target_properties(libbenchmark PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  IMPORTED_LOCATION "${binary_dir}/src/libbenchmark.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories("${source_dir}/include")

add_performance_test(target
  test/performance/target.cpp
)

add_custom_target(bench
    COMMAND performance-test-target
    DEPENDS ${STUMPLESS_PERFORMANCE_TEST_TARGETS}
)


# add in the swig project
if(BUILD_PYTHON)
  ExternalProject_Add(swig
    URL https://github.com/swig/swig/archive/master.zip
    PREFIX ${CMAKE_BINARY_DIR}/swig
    CONFIGURE_COMMAND cd <SOURCE_DIR> && <SOURCE_DIR>/autogen.sh && cd <BINARY_DIR> && <SOURCE_DIR>/configure --without-alllang --with-python
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
  )

  set_target_properties(swig
    PROPERTIES
    EXCLUDE_FROM_ALL TRUE
  )

  ExternalProject_Get_Property(swig
    source_dir
  )

  ExternalProject_Get_Property(swig
    binary_dir
  )

  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/stumpless_python_wrap.c
    COMMAND ${CMAKE_COMMAND} -E env SWIG_LIB=${source_dir}/Lib ${binary_dir}/swig -python -I${PROJECT_SOURCE_DIR}/include -o ${CMAKE_BINARY_DIR}/stumpless_python_wrap.c -outdir ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src/swig/stumpless.i
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
    PRIVATE include
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
