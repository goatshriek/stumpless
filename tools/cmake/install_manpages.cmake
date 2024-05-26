set(MANPAGE_BUILD_DIR "${PROJECT_BINARY_DIR}/docs/${STUMPLESS_LANGUAGE}/man/man3")

# install the generated manpages
# rename them so that they are globally unique
install(FILES
  ${MANPAGE_BUILD_DIR}/stumpless.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/config.h.3
  RENAME stumpless_config.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/element.h.3
  RENAME stumpless_element.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/entry.h.3
  RENAME stumpless_entry.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/error.h.3
  RENAME stumpless_error.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/facility.h.3
  RENAME stumpless_facility.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/filter.h.3
  RENAME stumpless_filter.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/generator.h.3
  RENAME stumpless_generator.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/id.h.3
  RENAME stumpless_id.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/log.h.3
  RENAME stumpless_log.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/memory.h.3
  RENAME stumpless_memory.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/option.h.3
  RENAME stumpless_option.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/param.h.3
  RENAME stumpless_param.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/severity.h.3
  RENAME stumpless_severity.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/target.h.3
  RENAME stumpless_target.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/version.h.3
  RENAME stumpless_version.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/alert.h.3
  RENAME stumpless_level_alert.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/crit.h.3
  RENAME stumpless_level_crit.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/debug.h.3
  RENAME stumpless_level_debug.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/emerg.h.3
  RENAME stumpless_level_emerg.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/err.h.3
  RENAME stumpless_level_err.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/info.h.3
  RENAME stumpless_level_info.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/mask.h.3
  RENAME stumpless_level_mask.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/notice.h.3
  RENAME stumpless_level_notice.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/trace.h.3
  RENAME stumpless_level_trace.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/warning.h.3
  RENAME stumpless_level_warning.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/buffer.h.3
  RENAME stumpless_target_buffer.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/chain.h.3
  RENAME stumpless_target_chain.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/file.h.3
  RENAME stumpless_target_file.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/function.h.3
  RENAME stumpless_target_function.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)

install(FILES
  ${MANPAGE_BUILD_DIR}/stream.h.3
  RENAME stumpless_target_stream.h.3
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man3
)
