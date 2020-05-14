find_library(gtest_lib
  NAMES gtest
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}"
)

find_library(gtest_main_lib
  NAMES gtest_main
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}"
)

find_library(gmock_lib
  NAMES gmock
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}"
)

find_path(gtest_header_path
  NAMES "gtest/gtest.h"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/googletest/include"
)

find_path(gmock_header_path
  NAMES "gmock/gmock.h"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/googlemock/include"
)

if(${gtest_lib} STREQUAL "gtest_lib-NOTFOUND" OR ${gtest_main_lib} STREQUAL "gtest_main_lib-NOTFOUND" OR ${gmock_lib} STREQUAL "gmock_lib-NOTFOUND" OR ${gtest_header_path} STREQUAL "gtest_header_path-NOTFOUND" OR ${gmock_header_path} STREQUAL "gmock_header_path-NOTFOUND")
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

  set_target_properties(libgtest PROPERTIES
    IMPORTED_LOCATION "${local_gtest_shared}"
    IMPORTED_IMPLIB "${local_gtest_static}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_library(libgtestmain SHARED IMPORTED GLOBAL)
  add_dependencies(libgtestmain gtest)

  set_target_properties(libgtestmain PROPERTIES
    IMPORTED_LOCATION "${local_gtest_main_shared}"
    IMPORTED_IMPLIB "${local_gtest_main_static}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_library(libgmock SHARED IMPORTED GLOBAL)
  add_dependencies(libgmock gtest)

  set_target_properties(libgmock PROPERTIES
    IMPORTED_LOCATION "${local_gmock_shared}"
    IMPORTED_IMPLIB "${local_gmock_static}"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  ExternalProject_Get_Property(gtest source_dir)

  include_directories("${source_dir}/googletest/include"
                      "${source_dir}/googlemock/include"
  )
else()
  if(${gtest_lib} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    message("found gtest as shared library")
    add_library(libgtest SHARED IMPORTED GLOBAL)

    set_target_properties(libgtest PROPERTIES
      IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
  else()
    message("found gtest as static library")
    add_library(libgtest STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(libgtest PROPERTIES
    IMPORTED_LOCATION ${gtest_lib}
  )

  if(${gtest_main_lib} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    add_library(libgtestmain SHARED IMPORTED GLOBAL)

    set_target_properties(libgtestmain PROPERTIES
      IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
  else()
    add_library(libgtestmain STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(libgtestmain PROPERTIES
    IMPORTED_LOCATION ${gtest_main_lib}
  )

  if(${gmock_lib} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    add_library(libgmock SHARED IMPORTED GLOBAL)

    set_target_properties(libgmock PROPERTIES
      IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
  else()
    add_library(libgmock STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(libgmock PROPERTIES
    IMPORTED_LOCATION ${gmock_lib}
  )

  include_directories(${gtest_header_path} ${gmock_header_path})
endif()
