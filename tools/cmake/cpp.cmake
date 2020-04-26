include(tools/cmake/cpp_test.cmake)

set(CPP_LIB_BUILD_DIR ${CMAKE_BINARY_DIR}/cpp-lib)

set(GENERATED_CPP_LIB_HEADERS
  ${CPP_LIB_BUILD_DIR}/AddressFailure.hpp
  ${CPP_LIB_BUILD_DIR}/ArgumentEmpty.hpp
  ${CPP_LIB_BUILD_DIR}/ArgumentTooBig.hpp
  ${CPP_LIB_BUILD_DIR}/Element.hpp
  ${CPP_LIB_BUILD_DIR}/Entry.hpp
  ${CPP_LIB_BUILD_DIR}/FileOpenFailure.hpp
  ${CPP_LIB_BUILD_DIR}/FileTarget.hpp
  ${CPP_LIB_BUILD_DIR}/FileWriteFailure.hpp
  ${CPP_LIB_BUILD_DIR}/IndexOutOfBounds.hpp
  ${CPP_LIB_BUILD_DIR}/InvalidFacility.hpp
  ${CPP_LIB_BUILD_DIR}/InvalidId.hpp
  ${CPP_LIB_BUILD_DIR}/MemoryAllocationFailure.hpp
  ${CPP_LIB_BUILD_DIR}/NetworkProtocolUnsupported.hpp
  ${CPP_LIB_BUILD_DIR}/Param.hpp
  ${CPP_LIB_BUILD_DIR}/SocketBindFailure.hpp
  ${CPP_LIB_BUILD_DIR}/SocketConnectFailure.hpp
  ${CPP_LIB_BUILD_DIR}/SocketFailure.hpp
  ${CPP_LIB_BUILD_DIR}/SocketSend.hpp
  ${CPP_LIB_BUILD_DIR}/StreamWriteFailure.hpp
  ${CPP_LIB_BUILD_DIR}/StumplessException.hpp
  ${CPP_LIB_BUILD_DIR}/TargetIncompatible.hpp
#  ${CPP_LIB_BUILD_DIR}/Target.hpp
  ${CPP_LIB_BUILD_DIR}/TargetType.hpp
  ${CPP_LIB_BUILD_DIR}/TargetUnsupported.hpp
  ${CPP_LIB_BUILD_DIR}/TransportProtocolUnsupported.hpp
  ${CPP_LIB_BUILD_DIR}/Version.hpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogCloseFailure.hpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogOpenFailure.hpp
)

set(GENERATED_CPP_LIB_SOURCES
  ${CPP_LIB_BUILD_DIR}/AddressFailure.cpp
  ${CPP_LIB_BUILD_DIR}/ArgumentEmpty.cpp
  ${CPP_LIB_BUILD_DIR}/ArgumentTooBig.cpp
  ${CPP_LIB_BUILD_DIR}/Element.cpp
  ${CPP_LIB_BUILD_DIR}/Entry.cpp
  ${CPP_LIB_BUILD_DIR}/FileOpenFailure.cpp
  ${CPP_LIB_BUILD_DIR}/FileTarget.cpp
  ${CPP_LIB_BUILD_DIR}/FileWriteFailure.cpp
  ${CPP_LIB_BUILD_DIR}/IndexOutOfBounds.cpp
  ${CPP_LIB_BUILD_DIR}/InvalidFacility.cpp
  ${CPP_LIB_BUILD_DIR}/InvalidId.cpp
  ${CPP_LIB_BUILD_DIR}/MemoryAllocationFailure.cpp
  ${CPP_LIB_BUILD_DIR}/NetworkProtocolUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/Param.cpp
  ${CPP_LIB_BUILD_DIR}/SocketBindFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketConnectFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketFailure.cpp
  ${CPP_LIB_BUILD_DIR}/SocketSendFailure.cpp
  ${CPP_LIB_BUILD_DIR}/StreamWriteFailure.cpp
  ${CPP_LIB_BUILD_DIR}/StumplessException.cpp
#  ${CPP_LIB_BUILD_DIR}/Target.cpp
  ${CPP_LIB_BUILD_DIR}/TargetIncompatible.cpp
  ${CPP_LIB_BUILD_DIR}/TargetUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/TransportProtocolUnsupported.cpp
  ${CPP_LIB_BUILD_DIR}/Version.cpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogCloseFailure.cpp
  ${CPP_LIB_BUILD_DIR}/WindowsEventLogOpenFailure.cpp
)

file(MAKE_DIRECTORY ${CPP_LIB_BUILD_DIR})

add_custom_command(
  OUTPUT ${GENERATED_CPP_LIB_SOURCES} ${GENERATED_CPP_LIB_HEADERS}
  COMMAND wrapture ${WRAPTURE_SPECS}
  DEPENDS ${WRAPTURE_SPECS}
  WORKING_DIRECTORY ${CPP_LIB_BUILD_DIR}
)

add_library(stumplesscpp SHARED
  EXCLUDE_FROM_ALL
  ${GENERATED_CPP_LIB_SOURCES}
)

target_link_libraries(stumplesscpp
  optimized stumpless
)

target_include_directories(stumplesscpp
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
  ${CPP_LIB_BUILD_DIR}
)

add_cpp_test(file
  SOURCES
    test/function/cpp/target/file.cpp
    $<TARGET_OBJECTS:rfc5424_checker>
)

add_cpp_test(version
  SOURCES test/function/cpp/version.cpp
)

add_custom_target(check-cpp
  DEPENDS ${STUMPLESS_CPP_TEST_RUNNERS}
)

#documentation generation
if(HAVE_DOXYGEN)
  file(MAKE_DIRECTORY ${PROJECT_DOCS_DIR})

  set(CPP_DOCS_DIR ${PROJECT_DOCS_DIR}/cpp)

  configure_file(${PROJECT_SOURCE_DIR}/tools/doxygen/CppDoxyfile.in ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile)

  add_custom_target(docs-cpp
    DEPENDS ${GENERATED_CPP_LIB_HEADERS}
    COMMAND doxygen ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile
  )
endif(HAVE_DOXYGEN)
