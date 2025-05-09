configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/config.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/config.h"
)
configure_file(
  "${PROJECT_SOURCE_DIR}/include/private/config.h.in"
  "${PROJECT_BINARY_DIR}/include/private/config.h"
)
configure_file(
  "${PROJECT_SOURCE_DIR}/include/test/config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/test/config.hpp"
)
configure_file(
  "${PROJECT_SOURCE_DIR}/tools/portage/libstumpless.ebuild.in"
  "${PROJECT_BINARY_DIR}/tools/portage/libstumpless-${PROJECT_VERSION}.ebuild"
  @ONLY
)
configure_file(
  "${PROJECT_SOURCE_DIR}/tools/portage/libstumpless.ebuild.in"
  "${PROJECT_BINARY_DIR}/tools/portage/libstumpless-9999.ebuild"
  @ONLY
)

# generating level header files
set(LEVEL_NAME_UPCASE "ALERT")
set(LEVEL_NAME_DOWNCASE "alert")
set(LEVEL_SHORTNAME "a")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "CRIT")
set(LEVEL_NAME_DOWNCASE "crit")
set(LEVEL_SHORTNAME "c")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "DEBUG")
set(LEVEL_NAME_DOWNCASE "debug")
set(LEVEL_SHORTNAME "d")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "EMERG")
set(LEVEL_NAME_DOWNCASE "emerg")
set(LEVEL_SHORTNAME "em")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "ERR")
set(LEVEL_NAME_DOWNCASE "err")
set(LEVEL_SHORTNAME "er")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "INFO")
set(LEVEL_NAME_DOWNCASE "info")
set(LEVEL_SHORTNAME "i")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "NOTICE")
set(LEVEL_NAME_DOWNCASE "notice")
set(LEVEL_SHORTNAME "n")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "WARNING")
set(LEVEL_NAME_DOWNCASE "warning")
set(LEVEL_SHORTNAME "w")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)

set(LEVEL_NAME_UPCASE "TRACE")
set(LEVEL_NAME_DOWNCASE "trace")
set(LEVEL_SHORTNAME "t")
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  @ONLY
)
