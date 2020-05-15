function(add_found_library)
  set(single_val_args NAME PATH)
  cmake_parse_arguments()

  if(${gtest_lib} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    add_library(libgtest SHARED IMPORTED GLOBAL)

    set_target_properties(libgtest PROPERTIES
      IMPORTED_LINK_INTERFACE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
  else()
    add_library(libgtest STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(libgtest PROPERTIES
    IMPORTED_LOCATION ${gtest_lib}
  )
endfunction(add_found_library)
