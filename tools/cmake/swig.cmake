macro(add_swig_project)
  ExternalProject_Add(swig
    URL https://github.com/swig/swig/archive/master.zip
    PREFIX ${CMAKE_BINARY_DIR}/swig
    CONFIGURE_COMMAND cd <SOURCE_DIR> && <SOURCE_DIR>/autogen.sh && cd <BINARY_DIR> && <SOURCE_DIR>/configure --without-alllang --with-python
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND ""
  )

  set_target_properties(swig
    PROPERTIES
    EXCLUDE_FROM_ALL TRUE
  )

  ExternalProject_Get_Property(swig
    source_dir
  )

  ExternalProject_Get_Property(swig
    binary_dir
  )
endmacro(add_swig_project)
