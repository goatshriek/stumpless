// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#include <stddef.h>
#include <stumpless/severity.h>
#include "private/severity.h"
#include "private/strhelper.h"

static char *severity_enum_to_string[] = {
  STUMPLESS_FOREACH_SEVERITY( GENERATE_STRING )
};

const char *
stumpless_get_severity_string( enum stumpless_severity severity ) {
  size_t severity_upper_bound =
    sizeof severity_enum_to_string / sizeof severity_enum_to_string[0];
  if ( severity >= 0 && severity < severity_upper_bound ) {
    return severity_enum_to_string[severity];
  }
  return "NO_SUCH_SEVERITY";
}

/* private functions */

int
get_severity( int prival ) {
  return prival & 0x7;
}

int
severity_is_invalid( int severity ) {
  return severity < 0 || severity > 7;
}
