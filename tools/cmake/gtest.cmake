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
    set(gtest_imported_location "${binary_dir}/googlemock/gtest/${CMAKE_CFG_INTDIR}/gtestd.lib")
  else()
    set(gtest_imported_location "${binary_dir}/googlemock/gtest/${CMAKE_CFG_INTDIR}/gtest.lib")
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
  set(gtest_imported_location "${binary_dir}/googlemock/gtest/libgtest.a")
endif(WIN32)

set_target_properties(libgtest PROPERTIES
  IMPORTED_LOCATION "${gtest_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(gmock_imported_location "${binary_dir}/googlemock/${CMAKE_CFG_INTDIR}/gmockd.lib")
  else()
    set(gmock_imported_location "${binary_dir}/googlemock/${CMAKE_CFG_INTDIR}/gmock.lib")
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
 set(gmock_imported_location "${binary_dir}/googlemock/libgmock.a")
endif(WIN32)

set_target_properties(libgmock PROPERTIES
  IMPORTED_LOCATION "${gmock_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")
