set(my_gtest_binary_dir "${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build")

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(my_gtest_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gtestd.lib")
    set(my_gtest_main_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gtest_maind.lib")
    set(my_gmock_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gmockd.lib")
  else()
    set(my_gtest_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gtest.lib")
    set(my_gtest_main_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gtest_main.lib")
    set(my_gmock_imported_location "${my_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}/gmock.lib")
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
else()
  set(my_gtest_imported_location "${my_gtest_binary_dir}/lib/libgtest.a")
  set(my_gtest_main_imported_location "${my_gtest_binary_dir}/lib/libgtest_main.a")
  set(my_gmock_imported_location "${my_gtest_binary_dir}/lib/libgmock.a")
endif(WIN32)

ExternalProject_Add(gtest
  URL https://github.com/abseil/googletest/archive/8b6d3f9c4a774bef3081195d422993323b6bb2e0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  CMAKE_ARGS -Dgtest_force_shared_crt=ON -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  CMAKE_GENERATOR "Unix Makefiles"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  BINARY_DIR "${my_gtest_binary_dir}"
  BUILD_BYPRODUCTS "${my_gtest_imported_location}" "${my_gtest_main_imported_location}" "${my_gmock_imported_location}"
)

set_target_properties(gtest
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
set(gtest_imported_location "${my_gtest_imported_location}")

add_library(libgtestmain IMPORTED STATIC GLOBAL)
add_dependencies(libgtestmain gtest)
set(gtest_main_imported_location "${my_gtest_main_imported_location}")

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)
set(gmock_imported_location "${my_gmock_imported_location}")

set_target_properties(libgtest PROPERTIES
  IMPORTED_LOCATION "${gtest_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

set_target_properties(libgtestmain PROPERTIES
  IMPORTED_LOCATION "${gtest_main_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

set_target_properties(libgmock PROPERTIES
  IMPORTED_LOCATION "${gmock_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

ExternalProject_Get_Property(gtest source_dir)
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include"
)
