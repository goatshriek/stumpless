install(
  FILES "${PROJECT_SOURCE_DIR}/include/stumpless.h"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
  FILES
    "${PROJECT_BINARY_DIR}/include/stumpless/config.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/element.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/entry.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/error.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/facility.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/filter.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/generator.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/id.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/log.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/memory.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/option.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/param.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/prival.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/severity.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/target.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/version.h"
  DESTINATION
    "${CMAKE_INSTALL_INCLUDEDIR}/stumpless"
)

install(
  FILES
    "${PROJECT_BINARY_DIR}/include/stumpless/level/alert.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/crit.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/debug.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/emerg.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/err.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/info.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/level/mask.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/notice.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/level/trace.h"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/warning.h"
  DESTINATION
    "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/level"
)

install(
  FILES
    "${PROJECT_SOURCE_DIR}/include/stumpless/target/buffer.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/target/file.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/target/function.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/target/sqlite3.h"
    "${PROJECT_SOURCE_DIR}/include/stumpless/target/stream.h"
  DESTINATION
    "${CMAKE_INSTALL_INCLUDEDIR}/stumpless/target"
)
