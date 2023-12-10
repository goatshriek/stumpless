include(tools/cmake/cpp_test.cmake)

set(CPP_LIB_BUILD_DIR ${CMAKE_BINARY_DIR}/cpp-lib)

set(GENERATED_CPP_LIB_HEADERS
  ${CMAKE_BINARY_DIR}/include/stumpless/AddressFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/ArgumentEmpty.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/ArgumentTooBig.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/BufferTarget.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/DuplicateElement.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Element.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/ElementNotFound.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Entry.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/ErrorId.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Facility.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/FileOpenFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/FileTarget.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/FileWriteFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/FunctionTarget.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/FunctionTargetFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/IndexOutOfBounds.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/InvalidFacility.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/InvalidId.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/InvalidSeverity.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/MemoryAllocationFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/MemoryManager.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/NetworkProtocolUnsupported.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Param.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/ParamNotFound.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Severity.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/SocketBindFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/SocketConnectFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/SocketFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/SocketSendFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/StreamTarget.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/StreamWriteFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/StumplessException.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/TargetIncompatible.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/TargetUnsupported.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/TransportProtocolUnsupported.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/Version.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/WindowsEventLogCloseFailure.hpp
  ${CMAKE_BINARY_DIR}/include/stumpless/WindowsEventLogOpenFailure.hpp
)

set(GENERATED_CPP_LIB_SOURCES
  ${CPP_LIB_BUILD_DIR}/AddressFailure.cpp
  ${CPP_LIB_BUILD_DIR}/ArgumentEmpty.cpp
  ${CPP_LIB_BUILD_DIR}/ArgumentTooBig.cpp
  ${CPP_LIB_BUILD_DIR}/BufferTarget.cpp
  ${CPP_LIB_BUILD_DIR}/DuplicateElement.cpp
  ${CPP_LIB_BUILD_DIR}/Element.cpp
  ${CPP_LIB_BUILD_DIR}/ElementNotFound.cpp
  ${CPP_LIB_BUILD_DIR}/Entry.cpp
  ${CPP_LIB_BUILD_DIR}/FileOpenFailure.cpp
  ${CPP_LIB_BUILD_DIR}/FileTarget.cpp
  ${CPP_LIB_BUILD_DIR}/FileWriteFailure.cpp
  ${CPP_LIB_BUILD_DIR}/FunctionTarget.cpp
  ${CPP_LIB_BUILD_DIR}/FunctionTargetFailure.cpp
  ${CPP_LIB_BUILD_DIR}/IndexOutOfBounds.cpp
  ${CPP_LIB_BUILD_DIR}/InvalidFacility.cpp
  ${CPP_LIB_BUILD_DIR}/InvalidId.cpp
  ${CPP_LIB_BUILD_DIR}/InvalidSeverity.cpp
  ${CPP_LIB_BUILD_DIR}/MemoryAllocationFailure.cpp
  ${CPP_LIB_BUILD_DIR}/MemoryManager.cpp
  ${CPP_LIB_BUILD_DIR}/NetworkProtocolUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/Param.cpp
  ${CPP_LIB_BUILD_DIR}/ParamNotFound.cpp
  ${CPP_LIB_BUILD_DIR}/SocketBindFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketConnectFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketSendFailure.cpp
  ${CPP_LIB_BUILD_DIR}/StreamTarget.cpp
  ${CPP_LIB_BUILD_DIR}/StreamWriteFailure.cpp
  ${CPP_LIB_BUILD_DIR}/StumplessException.cpp
  ${CPP_LIB_BUILD_DIR}/TargetIncompatible.cpp
  ${CPP_LIB_BUILD_DIR}/TargetUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/TransportProtocolUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/Version.cpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogCloseFailure.cpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogOpenFailure.cpp
)

if(STUMPLESS_JOURNALD_TARGETS_SUPPORTED)
  list(APPEND GENERATED_CPP_LIB_HEADERS ${CPP_LIB_BUILD_DIR}/JournaldTarget.hpp)
  list(APPEND GENERATED_CPP_LIB_SOURCES ${CPP_LIB_BUILD_DIR}/JournaldTarget.cpp)

  add_cpp_test(journald
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/cpp/target/journald.cpp
  )
endif()


if(STUMPLESS_NETWORK_TARGETS_SUPPORTED)
  list(APPEND GENERATED_CPP_LIB_HEADERS ${CPP_LIB_BUILD_DIR}/NetworkTarget.hpp)
  list(APPEND GENERATED_CPP_LIB_SOURCES ${CPP_LIB_BUILD_DIR}/NetworkTarget.cpp)

  add_cpp_test(network
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/cpp/target/network.cpp
  )
endif()

if(STUMPLESS_SOCKET_TARGETS_SUPPORTED)
  list(APPEND GENERATED_CPP_LIB_HEADERS ${CPP_LIB_BUILD_DIR}/SocketTarget.hpp)
  list(APPEND GENERATED_CPP_LIB_SOURCES ${CPP_LIB_BUILD_DIR}/SocketTarget.cpp)
endif()

if(STUMPLESS_SQLITE3_TARGETS_SUPPORTED)
  list(APPEND GENERATED_CPP_LIB_HEADERS ${CPP_LIB_BUILD_DIR}/Sqlite3Target.hpp)
  list(APPEND GENERATED_CPP_LIB_SOURCES ${CPP_LIB_BUILD_DIR}/Sqlite3Target.cpp)
endif()

if(STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED)
  list(APPEND GENERATED_CPP_LIB_HEADERS ${CPP_LIB_BUILD_DIR}/WelTarget.hpp)
  list(APPEND GENERATED_CPP_LIB_SOURCES ${CPP_LIB_BUILD_DIR}/WelTarget.cpp)

  add_cpp_test(wel
    SOURCES
      ${PROJECT_SOURCE_DIR}/test/function/cpp/target/wel.cpp
  )
endif()

file(MAKE_DIRECTORY ${CPP_LIB_BUILD_DIR})

if(MSVC)
  add_custom_command(
    OUTPUT ${GENERATED_CPP_LIB_SOURCES}
    COMMAND call wrapture ${WRAPTURE_SPECS}
    COMMAND powershell ${PROJECT_SOURCE_DIR}/scripts/Repair-HeaderDllExports.ps1 -InputFileDir ${CPP_LIB_BUILD_DIR} -OutputFileDir ${CMAKE_BINARY_DIR}/include/stumpless
    DEPENDS ${WRAPTURE_SPECS}
    WORKING_DIRECTORY ${CPP_LIB_BUILD_DIR}
    VERBATIM
  )
else()
  add_custom_command(
    OUTPUT ${GENERATED_CPP_LIB_SOURCES}
    COMMAND wrapture ${WRAPTURE_SPECS}
    COMMAND ruby ${PROJECT_SOURCE_DIR}/scripts/copy_headers.rb ${CMAKE_BINARY_DIR}/include/stumpless
    DEPENDS ${WRAPTURE_SPECS}
    WORKING_DIRECTORY ${CPP_LIB_BUILD_DIR}
    VERBATIM
  )
endif()


# create the rollup header
SET(cpp_rollup_header "${PROJECT_BINARY_DIR}/include/stumpless.hpp")
FILE(WRITE ${cpp_rollup_header} "#ifndef __STUMPLESS_HPP\n")
FILE(APPEND ${cpp_rollup_header} "#  define __STUMPLESS_HPP\n\n")

foreach(header_path ${GENERATED_CPP_LIB_HEADERS})
  get_filename_component(header_filename ${header_path} NAME)
  FILE(APPEND ${cpp_rollup_header} "#  include <stumpless/${header_filename}>\n")
endforeach(header_path)

FILE(APPEND ${cpp_rollup_header} "\n#endif /* __STUMPLESS_HPP */\n")


# shared library definition
add_library(stumplesscpp SHARED
  ${GENERATED_CPP_LIB_SOURCES}
)

target_link_libraries(stumplesscpp
  stumpless
)

target_include_directories(stumplesscpp
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_BINARY_DIR}/include/stumpless
)

set_target_properties(stumplesscpp
  PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${cpp_rollup_header}
)

if(WIN32)
  set_target_properties(stumplesscpp
    PROPERTIES
      COMPILE_DEFINITIONS DLL_EXPORTS
  )
endif()

if(MINGW)
  target_compile_options(stumplesscpp PRIVATE -D__USE_MINGW_ANSI_STDIO)
  set_target_properties(stumplesscpp PROPERTIES PREFIX "")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(stumplesscpp PUBLIC "-std=c++14")
endif()

add_cpp_test(element
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/element.cpp
)

add_cpp_test(entry
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/entry.cpp
)

add_cpp_test(file
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/target/file.cpp
    ${PROJECT_SOURCE_DIR}/test/helper/rfc5424.cpp
    ${PROJECT_SOURCE_DIR}/test/helper/utf8.cpp
)

add_cpp_test(function
  SOURCES ${PROJECT_SOURCE_DIR}/test/function/cpp/target/function.cpp
)

add_cpp_test(memory
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/memory.cpp
)

add_cpp_test(param
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/param.cpp
)

add_cpp_test(stream
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/target/stream.cpp
)

add_cpp_test(target
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/target.cpp
)

add_cpp_test(version
  SOURCES
    ${PROJECT_SOURCE_DIR}/test/function/cpp/version.cpp
)

add_custom_target(check-cpp
  DEPENDS ${STUMPLESS_CPP_TEST_RUNNERS}
)


add_no_run_example(cpp
  ${PROJECT_SOURCE_DIR}/docs/examples/cpp/cpp_example.cpp
)

target_link_libraries(example-cpp
  stumplesscpp
)

target_include_directories(example-cpp
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_BINARY_DIR}/cpp-lib
)

add_custom_target(run-example-cpp
  COMMAND "example-cpp"
  DEPENDS example-cpp
)

# add c++ library to installation
install(TARGETS stumplesscpp
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include"
  ARCHIVE DESTINATION "lib"
)

install(
  FILES ${GENERATED_CPP_LIB_HEADERS}
  DESTINATION "include/stumpless"
)

#documentation generation
if(DOXYGEN_FOUND)
  file(MAKE_DIRECTORY ${PROJECT_DOCS_DIR})

  set(CPP_DOCS_DIR ${PROJECT_DOCS_DIR}/cpp)

  configure_file(${PROJECT_SOURCE_DIR}/tools/doxygen/CppDoxyfile.in ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile)

  add_custom_target(docs-cpp
    DEPENDS ${GENERATED_CPP_LIB_HEADERS}
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile
  )
endif()
