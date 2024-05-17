set(DOXYGEN_INPUT "${PROJECT_BINARY_DIR}/include/doxygen")
set(DOXYGEN_OUTPUT "${PROJECT_DOCS_DIR}")

configure_file(
  "${PROJECT_SOURCE_DIR}/tools/doxygen/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/tools/doxygen/Doxyfile"
)

# detect files for dependency tracking
# note that this doesn't support new files being added after configuring:
# cmake will need to be re-run if this happens to include them in dependency tracking
file(GLOB_RECURSE DOXYGEN_SOURCE_HEADERS "${L10N_INCLUDE_DIR}/stumpless/*.h")
file(GLOB_RECURSE DOXYGEN_L10N_HEADERS "${L10N_INCLUDE_DIR}/stumpless/*.h")
file(GLOB_RECURSE DOXYGEN_BINARY_HEADERS "${PROJECT_BINARY_DIR}/include/stumpless/*.h")
file(GLOB_RECURSE DOXYGEN_EXAMPLE_SOURCES "${L10N_EXAMPLE_DIR}/*.c")

# we copy files into a specific doxygen folder because otherwise doxygen
# generates multiple folders with the same name in the file tree
# see https://github.com/doxygen/doxygen/issues/8318 for details
add_custom_command(
  OUTPUT ${DOXYGEN_MANPAGES}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_DOCS_DIR}"
  COMMAND ${CMAKE_COMMAND} -E rm -rf "${DOXYGEN_INPUT}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_BINARY_DIR}/include/stumpless" "${DOXYGEN_INPUT}/stumpless"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/include/stumpless" "${DOXYGEN_INPUT}/stumpless"
  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/include/stumpless.h" "${DOXYGEN_INPUT}/stumpless.h"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${L10N_INCLUDE_DIR}/stumpless" "${DOXYGEN_INPUT}/stumpless"
  COMMAND ${CMAKE_COMMAND} -E copy "${L10N_INCLUDE_DIR}/stumpless.h" "${DOXYGEN_INPUT}/stumpless.h"
  COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/tools/doxygen/Doxyfile"
  MAIN_DEPENDENCY "${PROJECT_BINARY_DIR}/tools/doxygen/Doxyfile"
  DEPENDS
    ${DOXYGEN_SOURCE_HEADERS}
    ${DOXYGEN_L10N_HEADERS}
    ${DOXYGEN_BINARY_HEADERS}
    ${DOXYGEN_EXAMPLE_SOURCES}
    "${L10N_INCLUDE_DIR}/stumpless.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless.h"
  VERBATIM
)

add_custom_target(docs DEPENDS ${DOXYGEN_MANPAGES})
