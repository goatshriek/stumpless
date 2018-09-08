cmake_minimum_required(VERSION 3.0.2)

project(stumpless VERSION 1.2.0)

option(BUILD_PYTHON "include the python libary" OFF)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(ENABLE_WINDOWS_EVENT_LOG_TARGETS "support windows event log targets" ON)
option(COVERAGE "Include coverage information" OFF)

# check for header files
include(CheckIncludeFiles)
include(CheckSymbolExists)

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
  message("socket targets are not supported without windows.h")
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED FALSE)
else()
  set(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED TRUE)
  list(APPEND STUMPLESS_SOURCES src/target/wel.c)
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

add_executable(buffer
  EXCLUDE_FROM_ALL
  test/function/target/buffer.cpp
  test/function/rfc5424.cpp
  test/function/utf8.cpp
)
set_target_properties(buffer
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(buffer
  stumpless
  libgtest
)

target_include_directories(buffer
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME buffer
  COMMAND buffer
)

add_executable(entry
  EXCLUDE_FROM_ALL
  test/function/entry.cpp
)

set_target_properties(entry
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(entry
  stumpless
  libgtest
)

target_include_directories(entry
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME entry
  COMMAND entry
)

add_executable(entry_memory_failure
  EXCLUDE_FROM_ALL
  test/function/startup/entry_memory_failure.cpp
)

set_target_properties(entry_memory_failure
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(entry_memory_failure
  stumpless
  libgtest
)

target_include_directories(entry_memory_failure
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME entry_memory_failure
  COMMAND entry_memory_failure
)

add_executable(file
  EXCLUDE_FROM_ALL
  test/function/target/file.cpp
  test/function/rfc5424.cpp
  test/function/utf8.cpp
)

set_target_properties(file
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(file
  stumpless
  libgtest
)

target_include_directories(file
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME file
  COMMAND file
)

add_executable(memory
  EXCLUDE_FROM_ALL
  test/function/memory.cpp
)

set_target_properties(memory
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(memory
  stumpless
  libgtest
)

target_include_directories(memory
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME memory
  COMMAND memory
)

if(STUMPLESS_SOCKET_TARGETS_SUPPORTED)
  add_executable(socket
    EXCLUDE_FROM_ALL
    test/function/target/socket.cpp
    test/function/rfc5424.cpp
    test/function/utf8.cpp
  )
  
  set_target_properties(socket
    PROPERTIES COMPILE_FLAGS "-std=c++11"
  )
  
  target_link_libraries(socket
    stumpless
    libgtest
  )
  
  target_include_directories(socket
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )
  
  add_test(NAME socket
    COMMAND socket
  )

  add_executable(socket_add_malloc_failure
    EXCLUDE_FROM_ALL
    test/function/startup/target/socket_add_malloc_failure.cpp
  )
  
  set_target_properties(socket_add_malloc_failure
    PROPERTIES COMPILE_FLAGS "-std=c++11"
    OUTPUT_NAME "socket_add_malloc_failure"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/function/startup/target"
  )
  
  target_link_libraries(socket_add_malloc_failure
    stumpless
    libgtest
  )
  
  target_include_directories(socket_add_malloc_failure
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
  )
  
  add_test(NAME socket_add_malloc_failure
    COMMAND ${CMAKE_BINARY_DIR}/test/function/startup/target/socket_add_malloc_failure
  )
endif(STUMPLESS_SOCKET_TARGETS_SUPPORTED)

add_executable(target
  EXCLUDE_FROM_ALL
  test/function/target.cpp
)

set_target_properties(target
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(target
  stumpless
  libgtest
)

target_include_directories(target
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME target
  COMMAND target
)

add_executable(version
  EXCLUDE_FROM_ALL
  test/function/version.cpp
)

set_target_properties(version
  PROPERTIES COMPILE_FLAGS "-std=c++11"
)

target_link_libraries(version
  stumpless
  libgtest
)

target_include_directories(version
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_test(NAME version
  COMMAND version
)

if(WIN32)
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE}
    DEPENDS buffer entry entry_memory_failure file memory target version
  )
else()
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS buffer entry entry_memory_failure file memory socket socket_add_malloc_failure target version
  )
endif(WIN32)

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

add_executable(perf-target
  EXCLUDE_FROM_ALL
  test/performance/target.cpp
)

target_link_libraries(perf-target
  stumpless
  libbenchmark
)

set_target_properties(perf-target
  PROPERTIES
  OUTPUT_NAME "target"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/performance"
)

target_include_directories(perf-target
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
)

add_custom_target(bench
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test/performance/target
    DEPENDS perf-target
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
