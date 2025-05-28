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

set(NAME_UPCASE ALERT CRIT DEBUG EMERG ERR INFO NOTICE WARNING TRACE)
set(NAME_DOWNCASE alert crit debug emerg err info notice warning trace)
set(NAME_SHORT a c d em er i n w t)

foreach(UPCASE DOWNCASE SHORTNAME IN ZIP_LISTS NAME_UPCASE NAME_DOWNCASE NAME_SHORT)
  set(LEVEL_NAME_UPCASE "${UPCASE}")
  set(LEVEL_NAME_DOWNCASE "${DOWNCASE}")
  set(LEVEL_SHORTNAME "${SHORTNAME}")
  configure_file(
  "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
  "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
  )
endforeach()