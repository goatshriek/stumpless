// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stumpless/prival.h>
#include <stumpless/severity.h>
#include <stumpless/facility.h>

const char *
stumpless_get_prival_string(int prival) {
    const char *prival_string;
    int severity = get_severity(prival);
    int facility = get_facility(prival);

  if(severity_is_invalid(severity) == 0 || facility_is_invalid(facility) == 0) {
    return "NO_SUCH_PRIVAL";
  } else {
      asprintf(&prival_string,"%s | %s", stumpless_get_severity_string((enum)*severity), 
      stumpless_get_facility_string((enum)*facility));
      return prival_string;
    }
}
  