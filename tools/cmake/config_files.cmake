# SPDX-License-Identifier: Apache-2.0

# Copyright 2025 Joel E. Anderson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
set(NAME_DOWNCASE alert crit debug emerg err info notice warning trace)
set(NAME_SHORT a c d em er i n w t)

foreach(LEVEL_NAME_DOWNCASE LEVEL_SHORTNAME IN ZIP_LISTS NAME_DOWNCASE NAME_SHORT)
  string(TOUPPER "${LEVEL_NAME_DOWNCASE}" LEVEL_NAME_UPCASE)
  configure_file(
    "${PROJECT_SOURCE_DIR}/include/stumpless/level/level.h.in"
    "${PROJECT_BINARY_DIR}/include/stumpless/level/${LEVEL_NAME_DOWNCASE}.h"
    @ONLY
  )
endforeach()
