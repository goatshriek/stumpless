find_library(gtest_lib
  NAMES gtest
  PATHS ${GTEST_PATH}
)

set(local_gtest_binary_dir "${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build")
set(local_gtest_static_dir "${local_gtest_binary_dir}/lib/${CMAKE_CFG_INTDIR}")

if(CYGWIN OR MINGW OR WIN32)
  set(local_gtest_shared_dir "${local_gtest_binary_dir}/bin/${CMAKE_CFG_INTDIR}")
else()
  set(local_gtest_shared_dir "${local_gtest_static_dir}")
endif()

set(local_gtest_shared "${local_gtest_shared_dir}/${google_libs_shared_prefix}gtest${google_libs_debug_suffix}.${google_libs_shared_suffix}")
set(local_gtest_main_shared "${local_gtest_shared_dir}/${google_libs_shared_prefix}gtest_main${google_libs_debug_suffix}.${google_libs_shared_suffix}")
set(local_gmock_shared "${local_gtest_shared_dir}/${google_libs_shared_prefix}gmock${google_libs_debug_suffix}.${google_libs_shared_suffix}")

set(local_gtest_static "${local_gtest_static_dir}/${google_libs_static_prefix}gtest${google_libs_debug_suffix}.${google_libs_static_suffix}")
set(local_gtest_main_static "${local_gtest_static_dir}/${google_libs_static_prefix}gtest_main${google_libs_debug_suffix}.${google_libs_static_suffix}")
set(local_gmock_static "${local_gtest_static_dir}/${google_libs_static_prefix}gmock${google_libs_debug_suffix}.${google_libs_static_suffix}")

set(local_gtest_byproducts
  ${local_gtest_shared}
  ${local_gtest_main_shared}
  ${local_gmock_shared}
  ${local_gtest_static}
  ${local_gtest_main_static}
  ${local_mock_static}
)

ExternalProject_Add(gtest
  URL https://github.com/google/googletest/archive/6f5fd0d7199b9a19faa9f499ecc266e6ae0329e7.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  CMAKE_ARGS -Dgtest_force_shared_crt=ON -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_SH=${CMAKE_SH} -DBUILD_SHARED_LIBS=ON
  UPDATE_COMMAND ""
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${local_gtest_shared} ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${local_gtest_main_shared} ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${local_gmock_shared} ${CMAKE_CURRENT_BINARY_DIR}
  BUILD_BYPRODUCTS ${local_gtest_byproducts}
)

set_target_properties(gtest
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

add_library(libgtest SHARED IMPORTED GLOBAL)
add_dependencies(libgtest gtest)

add_library(libgtestmain SHARED IMPORTED GLOBAL)
add_dependencies(libgtestmain gtest)

add_library(libgmock SHARED IMPORTED GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgtest PROPERTIES
  IMPORTED_LOCATION "${local_gtest_shared}"
  IMPORTED_IMPLIB "${local_gtest_static}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

set_target_properties(libgtestmain PROPERTIES
  IMPORTED_LOCATION "${local_gtest_main_shared}"
  IMPORTED_IMPLIB "${local_gtest_main_static}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

set_target_properties(libgmock PROPERTIES
  IMPORTED_LOCATION "${local_gmock_shared}"
  IMPORTED_IMPLIB "${local_gmock_static}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

ExternalProject_Get_Property(gtest source_dir)
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include"
)
