// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stumpless.h>
#include "private/memory.h"
#include "private/entry.h"
#include "private/validate.h"
#include "private/config.h"

static void toUpperCase( char *str ) {
  for( int i = 0; str[i]; i++) {
    str[i] = toupper( str[i] );
  }
}

int
stumpless_prival_from_string( const char *string ) {
  int prival;
  int severity;
  int facility;
  char *param;
  char *period;
  char *sec_period;
  size_t len;
  size_t slen;
  size_t pre_len;
  const char pre_facility[] = "STUMPLESS_FACILITY_";
  const char pre_severity[] = "STUMPLESS_SEVERITY_";

  VALIDATE_ARG_NOT_NULL_INT_RETURN( string );

  if( unlikely( !string[0] ) ) {
    return -1;
  }

  slen = strlen( string );

  if( isdigit( string[0] ) ) {
    prival = atoi( string );
    if( prival >= 0 && prival <= 191 && slen < 4 ) {
      return prival;
    }
  }

  // find the first period character
  period = strchr( string, '.' );
  if( !period )
    return -1;

  // check there is no another period character
  sec_period = strchr( period + 1, '.' );
  if( sec_period != NULL ) {
    return -1;
  }

  // Calculate the facility length, up to the first period character
  len = period - string;
  pre_len = sizeof(pre_facility) - 1;
  param = alloc_mem( len + 1 + pre_len );
  if( !param ) {
    return -1;
  }
  // Copy the facility substring to the param buffer
  memcpy( param, pre_facility, pre_len );
  memcpy( param + pre_len, string, len );
  param[pre_len + len] = '\0';

  toUpperCase(param);
  facility = stumpless_get_facility_enum( param );

  free_mem( param );

  if( facility < 0 )
    return -1;

  // Calculate the severity length
  len = slen - ++len;
  pre_len = sizeof(pre_severity) - 1;

  param = alloc_mem( len + 1 + pre_len );
  if( !param ) {
    return -1;
  }
  // Copy the severity substring to the param buffer
  memcpy( param, pre_severity, pre_len );
  memcpy( param + pre_len, ++period, len);
  param[pre_len + len] = '\0';

  toUpperCase(param);
  severity = stumpless_get_severity_enum( param );

  free_mem( param );

  if( severity < 0 )
    return -1;

  return get_prival( facility, severity );
}

