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
#include <string.h>
#include <stumpless/facility.h>
#include "private/facility.h"
#include "private/strhelper.h"

static char *facility_enum_to_string[] = {
  STUMPLESS_FOREACH_FACILITY( GENERATE_STRING )
};

const char *
stumpless_get_facility_string( enum stumpless_facility facility ) {
  size_t facility_upper_bound = sizeof facility_enum_to_string;
  if ( !facility_is_invalid(facility) ) {
    return facility_enum_to_string[facility >> 3];
  }
  return "NO_SUCH_FACILITY";
}

enum stumpless_facility
stumpless_get_facility_enum( const char *facility_string ) {
  for (int i = 0; i < sizeof facility_enum_to_string / sizeof facility_enum_to_string[0]; i++)
    if (strcmp(facility_string, facility_enum_to_string[i]) == 0)
      return i << 3;
  return -1;
}

/* private functions */

int
get_facility( int prival ) {
  return prival & 0xf8;
}

int
facility_is_invalid( int facility ) {
  return facility < 0 || facility > ( 23 << 3 ) || facility % 8 != 0;
}
