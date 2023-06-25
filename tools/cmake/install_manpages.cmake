# build the docs so that they are available for install
install(CODE
  "execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target docs)"
)

set(MANPAGE_BUILD_DIR "${PROJECT_BINARY_DIR}/docs/man/man3")

# install the generated manpages
# rename them so that they are globally unique
install(FILES
  ${MANPAGE_BUILD_DIR}/config.h.3
  RENAME stumpless_config.h.3
  DESTINATION "man/man3"
)
