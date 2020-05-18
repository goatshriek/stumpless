function(add_found_library)
  set(single_val_args LIB_NAME LIB_PATH DLL_PATH)
  set(multiple_val_args INTERFACE_LINK_LIBRARIES)
  cmake_parse_arguments(FOUND "" "${single_val_args}" "${multiple_val_args}" ${ARGN})

  if(${FOUND_LIB_PATH} MATCHES "${CMAKE_SHARED_LIBRARY_SUFFIX}$")
    add_library(${FOUND_LIB_NAME} SHARED IMPORTED GLOBAL)
  else()
    add_library(${FOUND_LIB_NAME} STATIC IMPORTED GLOBAL)
  endif()

  set_target_properties(${FOUND_LIB_NAME} PROPERTIES
    IMPORTED_LOCATION ${FOUND_LIB_PATH}
  )

  if(${FOUND_INTERFACE_LINK_LIBRARIES})
    set_target_properties(${FOUND_LIB_NAME} PROPERTIES
      INTERFACE_LINK_LIBRARIES ${FOUND_INTERFACE_LINK_LIBRARIES}
    )
  endif()

  if(NOT ${FOUND_DLL_PATH} MATCHES "-NOTFOUND$")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E copy ${FOUND_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}
    )
  endif()
endfunction(add_found_library)
