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
#include <stdio.h>
#include <time.h>
#include "private/config/have_gmtime_r.h"
#include "private/formatter.h"

size_t
gmtime_r_get_now( char *buffer ) {
  int gettime_result;
  struct tm now_tm;
  struct timespec now_ts;
  const struct tm *gmtime_result;
  size_t written;

  gettime_result = clock_gettime( CLOCK_REALTIME, &now_ts );
  if( gettime_result != 0 ) {
    return 0;
  }

  gmtime_result = gmtime_r( &(now_ts.tv_sec), &now_tm );
  if( !gmtime_result ) {
    return 0;
  }

  written = strftime( buffer,
                      RFC_5424_WHOLE_TIME_BUFFER_SIZE,
                      "%FT%T",
                      &now_tm );
  written += snprintf( buffer + written,
                       RFC_5424_TIME_SECFRAC_BUFFER_SIZE + 2,
                       ".%06ldZ",
                       ( now_ts.tv_nsec / 1000 ) % 1000000 );

  return written;
}
