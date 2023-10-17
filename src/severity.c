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
#include <stumpless/severity.h>
#include "private/severity.h"
#include "private/strhelper.h"
#include "private/memory.h"

static char *severity_enum_to_string[] = {
  STUMPLESS_FOREACH_SEVERITY( GENERATE_STRING )
};

const char *
stumpless_get_severity_string( enum stumpless_severity severity ) {
  if ( !severity_is_invalid( severity ) ) {
    return severity_enum_to_string[severity];
  }
  return "NO_SUCH_SEVERITY";
}

enum stumpless_severity
stumpless_get_severity_enum( const char *severity_string ) {
  size_t severity_bound;
  size_t i;
  char *severity_name;
  const int str_offset = 19; // to ommit "STUMPLESS_SEVERITY_"

  severity_bound = sizeof( severity_enum_to_string ) /
                     sizeof( severity_enum_to_string[0] );

  severity_name = copy_cstring( severity_string );
  if( !severity_name ) {
    return -1;
  }

  to_upper_case( severity_name );
  for( i = 0; i < severity_bound; i++ ) {
    if( strcmp( severity_name, severity_enum_to_string[i] + str_offset ) == 0 ) {
      free_mem( severity_name );
      return i;
    }
  }

  if( strcmp( severity_name, "PANIC" ) == 0 ) {
    free_mem( severity_name );
    return STUMPLESS_SEVERITY_EMERG_VALUE;
  }

  if( strcmp( severity_name, "ERROR" ) == 0 ) {
    free_mem( severity_name );
    return STUMPLESS_SEVERITY_ERR_VALUE;
  }

  if( strcmp( severity_name, "WARN" ) == 0 ) {
    free_mem( severity_name );
    return STUMPLESS_SEVERITY_WARNING_VALUE;
  }

  free_mem( severity_name );
  return -1;
}

enum stumpless_severity
stumpless_get_severity_enum_from_buffer(const char *buffer, size_t length) {
  size_t severity_bound;
  size_t i;

  severity_bound = sizeof(severity_enum_to_string) /
                     sizeof(severity_enum_to_string[0]);

  for (i = 0; i < severity_bound; i++) {
    if (strncmp(buffer, severity_enum_to_string[i], length) == 0 &&
        severity_enum_to_string[i][length] == '\0') {
      return i;
    }
  }

  return -1;
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
