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
  if ( !facility_is_invalid( facility ) ) {
    return facility_enum_to_string[facility >> 3];
  }
  return "NO_SUCH_FACILITY";
}

enum stumpless_facility
stumpless_get_facility_enum( const char *facility_string ) {
  return stumpless_get_facility_enum_from_buffer(facility_string, strlen(facility_string));
}

enum stumpless_facility
stumpless_get_facility_enum_from_buffer(const char *facility_buffer, size_t facility_buffer_length) {
 size_t facility_bound;
 size_t i;
 const int str_offset = 19; // to ommit "STUMPLESS_FACILITY_"

 facility_bound = sizeof( facility_enum_to_string ) /
           sizeof( facility_enum_to_string[0] );

 for( i = 0; i < facility_bound; i++ ) {
  if( strncasecmp_custom( facility_buffer, facility_enum_to_string[i] + str_offset, facility_buffer_length ) == 0 ) {
   return i << 3;
  }
 }

 // exeption, for 'security' return 'auth' enum value
  if( strncasecmp_custom( facility_buffer, "SECURITY", facility_buffer_length ) == 0 ) {
  return STUMPLESS_FACILITY_AUTH_VALUE;
 }

 // exeption, for 'authpriv' not presented in enum list
  if( strncasecmp_custom( facility_buffer, "AUTHPRIV", facility_buffer_length ) == 0 ) {
  return STUMPLESS_FACILITY_AUTH2_VALUE;
 }

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
