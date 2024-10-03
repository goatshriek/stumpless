// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stumpless/prival.h>
#include <stumpless/severity.h>
#include <stumpless/facility.h>
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/facility.h"
#include "private/memory.h"
#include "private/prival.h"
#include "private/severity.h"
#include "private/validate.h"
#include "private/error.h"

const char *
stumpless_get_prival_string( int prival ) {
  const char *severity;
  const char *facility;
  size_t prival_string_size;
  char *prival_string;

  severity = stumpless_get_severity_string( get_severity( prival ) );
  facility = stumpless_get_facility_string( get_facility( prival ) );
   
  size_t len_severity = strlen(severity); // to not call strlen() mutiples times, unsure about impact
  size_t len_facility = strlen(facility);

  // +3 for formatting, +1 for termination
  prival_string_size = ( len_severity + len_facility + 4);
  prival_string = alloc_mem( prival_string_size );
  
  memcpy( prival_string, severity , len_severity); 
  memcpy( prival_string + len_severity, " | ", 3); // 3 is the size of " | "
  memcpy( prival_string + len_severity + 3, facility, len_facility);
  memcpy( prival_string + len_severity + 3 + len_facility, "\0", 1);
  
  return prival_string;
}

const char *
stumpless_get_priority_string( int prival ) {
  const char *severity;
  const char *facility;
  size_t priority_string_size;
  char* priority_string;

  severity = stumpless_get_severity_string( get_severity( prival ) );
  facility = stumpless_get_facility_string( get_facility( prival ) );
   
  size_t len_severity = strlen(severity);
  size_t len_facility = strlen(facility);

  // +1 for '.' formatting, +1 for termination
  priority_string_size = ( len_severity + len_facility + 2);
  priority_string = alloc_mem( priority_string_size );

  memcpy( priority_string, facility , len_facility); 
  priority_string[len_severity] = '.';
  memcpy( priority_string + len_facility + 1, severity, len_severity);
  priority_string[priority_string_size-1] = "\0";

  return priority_string;
}

int
stumpless_prival_from_string( const char *string ) {
  int prival;
  int severity;
  int facility;
  const char *period;
  const char *sec_period;
  size_t len;
  size_t slen;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( string );

  if( unlikely( !string[0] ) ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "string" ) );
    return -1;
  }

  slen = strlen( string );

  if( isdigit( string[0] ) ) {
    prival = atoi( string );
    if( prival <= 191 && slen < 4 ) {
      return prival;
    }
  }

  // find the first period character
  period = strchr( string, '.' );
  if( !period ) {
    raise_invalid_param(  );
    return -1;
  }

  // check there is no another period character
  sec_period = strchr( period + 1, '.' );
  if( sec_period != NULL ) {
    raise_invalid_param(  );
    return -1;
  }

  // Calculate the facility length, up to the first period character
  len = period - string;

  facility = stumpless_get_facility_enum_from_buffer( string, len );

  if( facility < 0 ) {
    raise_invalid_param(  );
    return -1;
  }

  // Calculate the severity length
  len++;
  len = slen - len;

  severity = stumpless_get_severity_enum_from_buffer( period + 1, len );

  if( severity < 0 ) {
    raise_invalid_param(  );
    return -1;
  }

  return get_prival( facility, severity );
}

/* private functions */

int
get_prival( enum stumpless_facility facility,
            enum stumpless_severity severity ) {
  return facility | severity;
}
