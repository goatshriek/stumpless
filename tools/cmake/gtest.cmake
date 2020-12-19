find_library(gtest_lib
  NAMES gtest gtestd
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}" "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_library(gtest_main_lib
  NAMES gtest_main gtest_maind
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}" "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_library(gmock_lib
  NAMES gmock gmockd
  PATHS ${GTEST_PATH} "${GTEST_PATH}/lib" "${GTEST_PATH}/lib/${CMAKE_CFG_INTDIR}" "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_path(gtest_header_path
  NAMES "gtest/gtest.h"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/googletest/include"
)

find_path(gmock_header_path
  NAMES "gmock/gmock.h"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/googlemock/include"
)

find_file(gtest_dll
  NAMES "gtest${CMAKE_SHARED_LIBRARY_SUFFIX}" "gtestd${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gtest${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gtestd${CMAKE_SHARED_LIBRARY_SUFFIX}"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_file(gtest_main_dll
  NAMES "gtest_main${CMAKE_SHARED_LIBRARY_SUFFIX}" "gtest_maind${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gtest_main${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gtest_maind${CMAKE_SHARED_LIBRARY_SUFFIX}"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_file(gmock_dll
  NAMES "gmock${CMAKE_SHARED_LIBRARY_SUFFIX}" "gmockd${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gmock${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_SHARED_LIBRARY_PREFIX}gmockd${CMAKE_SHARED_LIBRARY_SUFFIX}"
  PATHS ${GTEST_PATH} "${GTEST_PATH}/bin" "${GTEST_PATH}/bin/${CMAKE_CFG_INTDIR}"
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
    URL https://github.com/google/googletest/archive/18f8200e3079b0e54fa00cb7ac55d4c39dcf6da6.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    CMAKE_ARGS -Dgtest_force_shared_crt=ON -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_SH=${CMAKE_SH} -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS=${google_libs_cxx_flags}
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
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_library(libgtestmain SHARED IMPORTED GLOBAL)
  add_dependencies(libgtestmain gtest)

  set_target_properties(libgtestmain PROPERTIES
    IMPORTED_LOCATION "${local_gtest_main_shared}"
    IMPORTED_IMPLIB "${local_gtest_main_static}"
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_library(libgmock SHARED IMPORTED GLOBAL)
  add_dependencies(libgmock gtest)

  set_target_properties(libgmock PROPERTIES
    IMPORTED_LOCATION "${local_gmock_shared}"
    IMPORTED_IMPLIB "${local_gmock_static}"
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  ExternalProject_Get_Property(gtest source_dir)

  include_directories("${source_dir}/googletest/include"
                      "${source_dir}/googlemock/include"
  )

  add_custom_target(export-gtest
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${local_gtest_binary_dir} ${GTEST_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${local_gtest_shared_dir} ${GTEST_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${local_gtest_static_dir} ${GTEST_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_dir}/googletest/include" ${GTEST_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_dir}/googlemock/include" ${GTEST_PATH}
    DEPENDS gtest
  )
else()
  add_found_library(
    LIB_NAME "libgtest"
    LIB_PATH ${gtest_lib}
    DLL_PATH ${gtest_dll}
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_found_library(
    LIB_NAME "libgtestmain"
    LIB_PATH ${gtest_main_lib}
    DLL_PATH ${gtest_main_dll}
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_found_library(
    LIB_NAME "libgmock"
    LIB_PATH ${gmock_lib}
    DLL_PATH ${gmock_dll}
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  include_directories(${gtest_header_path} ${gmock_header_path})
endif()
