include(tools/cmake/cpp_test.cmake)

set(CPP_LIB_BUILD_DIR ${CMAKE_BINARY_DIR}/cpp-lib)

set(GENERATED_CPP_LIB_HEADERS
  ${CPP_LIB_BUILD_DIR}/AddressFailure.hpp
  ${CPP_LIB_BUILD_DIR}/Element.hpp
  ${CPP_LIB_BUILD_DIR}/Entry.hpp
  ${CPP_LIB_BUILD_DIR}/FileTarget.hpp
  ${CPP_LIB_BUILD_DIR}/Param.hpp
  ${CPP_LIB_BUILD_DIR}/StumplessException.hpp
  ${CPP_LIB_BUILD_DIR}/Version.hpp
)

set(GENERATED_CPP_LIB_SOURCES
  ${CPP_LIB_BUILD_DIR}/AddressFailure.cpp
  ${CPP_LIB_BUILD_DIR}/Element.cpp
  ${CPP_LIB_BUILD_DIR}/Entry.cpp
  ${CPP_LIB_BUILD_DIR}/FileTarget.cpp
  ${CPP_LIB_BUILD_DIR}/Param.cpp
  ${CPP_LIB_BUILD_DIR}/StumplessException.cpp
  ${CPP_LIB_BUILD_DIR}/Version.cpp
)

file(MAKE_DIRECTORY ${CPP_LIB_BUILD_DIR})

add_custom_command(
  OUTPUT ${GENERATED_CPP_LIB_SOURCES} ${GENERATED_CPP_LIB_HEADERS}
  COMMAND wrapture ${WRAPTURE_SPECS}
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
  file(MAKE_DIRECTORY ${CPP_LIB_BUILD_DIR}/cpp)
  file(MAKE_DIRECTORY ${PROJECT_DOCS_DIR})

  set(CPP_DOCS_DIR ${PROJECT_DOCS_DIR}/cpp)

  configure_file(${PROJECT_SOURCE_DIR}/tools/doxygen/CppDoxyfile.in ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile)

  add_custom_target(docs-cpp
    DEPENDS ${GENERATED_CPP_LIB_HEADERS}
    COMMAND doxygen ${CMAKE_BINARY_DIR}/tools/doxygen/CppDoxyfile
  )
endif(HAVE_DOXYGEN)
