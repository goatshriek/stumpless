set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "a fast and feature-rich C logging library")
string(CONCAT CPACK_PACKAGE_DESCRIPTION
  "Stumpless is a C logging library built for high performance and a rich "
  "feature set.\n"
  "\n"
  "Stumpless supports a variety of target types including files, streams, "
  "network servers, Unix sockets, and the Windows Event Log. It also supports "
  "structured logging, compile-time log statement removal, and is completely "
  "thread safe. Check out the project homepage at "
  "https://goatshriek.github.io/stumpless/ for more info and documentation."
)

set(CPACK_PACKAGE_CONTACT "Joel Anderson <joelanderson333@gmail.com>")
set(CPACK_PACKAGE_VENDOR "Goatshriek Software")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/COPYING" "${PROJECT_BINARY_DIR}/COPYING.txt"
)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_BINARY_DIR}/COPYING.txt")


# Debian settings
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_ARCHIVE_TYPE "gnutar")


# WIX settings
set(CPACK_WIX_PRODUCT_GUID "c0ac11a2-d1ab-4aa9-9f4f-b67d7c6db291")
set(CPACK_WIX_UPGRADE_GUID "21affd82-0719-4144-9f54-5e893a08633d")
set(CPACK_WIX_PRODUCT_ICON "${PROJECT_SOURCE_DIR}/assets/logo.ico")


include(CPack)
