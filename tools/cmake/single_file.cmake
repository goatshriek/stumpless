set(STUMPLESS_SOURCES_MANIFEST_FILE "${PROJECT_BINARY_DIR}/stumpless_sources.txt")
file(WRITE "${STUMPLESS_SOURCES_MANIFEST_FILE}" "")
foreach(source_file ${STUMPLESS_SOURCES})
  file(APPEND "${STUMPLESS_SOURCES_MANIFEST_FILE}" "${source_file}\n")
endforeach()

add_custom_target(single-file
  COMMAND
    ${CMAKE_COMMAND}
    -DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}
    -DSOURCE_MANIFEST_FILE=${STUMPLESS_SOURCES_MANIFEST_FILE}
    -DSINGLE_SOURCE_FILE=${SINGLE_SOURCE_FILE}
    -DSINGLE_HEADER_FILE=${SINGLE_HEADER_FILE}
    -P ${PROJECT_SOURCE_DIR}/tools/cmake/build_single_files.cmake
  DEPENDS
    ${STUMPLESS_SOURCES}
  BYPRODUCTS
    ${SINGLE_SOURCE_FILE}
    ${SINGLE_HEADER_FILE}
)

# this needs to happen after the stumpless library is set up
get_property(STUMPLESS_LINK_LIBRARIES TARGET stumpless PROPERTY LINK_LIBRARIES)
foreach(single_file_target ${STUMPLESS_SINGLE_FILE_TARGETS})
  target_link_libraries(${single_file_target} ${STUMPLESS_LINK_LIBRARIES})
endforeach()

add_custom_target(bench-single-file
  DEPENDS ${STUMPLESS_BENCH_SINGLE_FILE_RUNNERS}
)

add_custom_target(check-single-file
  DEPENDS ${STUMPLESS_CHECK_SINGLE_FILE_RUNNERS}
)

add_custom_target(examples-single-file
  DEPENDS ${STUMPLESS_EXAMPLE_SINGLE_FILE_RUNNERS}
)
