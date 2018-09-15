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
