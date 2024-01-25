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
#include "private/strhelper.h"
#include "private/error.h"
#include "private/config/locale/wrapper.h"

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

  // Copy the facility substring to the param buffer
  param = copy_cstring_length( string, len );
  if( !param ) {
    return -1;
  }

  facility = stumpless_get_facility_enum( param );

  free_mem( param );

  if( facility < 0 ) {
    raise_invalid_param(  );
    return -1;
  }

  // Calculate the severity length
  len++;
  len = slen - len;

  // Copy the severity substring to the param buffer
  param = copy_cstring_length( ++period, len );
  if( !param ) {
    return -1;
  }

  severity = stumpless_get_severity_enum( param );

  free_mem( param );

  if( severity < 0 ) {
    raise_invalid_param(  );
    return -1;
  }

  return get_prival( facility, severity );
}

