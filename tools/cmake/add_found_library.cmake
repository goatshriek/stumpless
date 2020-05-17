function(add_found_library)
  set(single_val_args LIB_NAME LIB_PATH DLL_PATH)
  cmake_parse_arguments(FOUND_LIBRARY "" "${single_val_args}" "" ${ARGN})

  if(${FOUND_LIBRARY_LIB_PATH} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    add_library(${FOUND_LIBRARY_LIB_NAME} SHARED IMPORTED GLOBAL)

    set_target_properties(${FOUND_LIBRARY_LIB_NAME} PROPERTIES
      INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
    )
  else()
    add_library(${FOUND_LIBRARY_LIB_NAME} STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(${FOUND_LIBRARY_LIB_NAME} PROPERTIES
    IMPORTED_LOCATION ${FOUND_LIBRARY_LIB_PATH}
  )

  if(NOT ${FOUND_LIBRARY_DLL_PATH} MATCHES "-NOTFOUND$")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E copy ${FOUND_LIBRARY_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}
    )
  endif()
endfunction(add_found_library)
