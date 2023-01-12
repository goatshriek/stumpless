// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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
#include <time.h>
#include "private/config/have_gmtime.h"
#include "private/formatter.h"

size_t
gmtime_get_now( char *buffer ) {
  time_t now_time;
  time_t time_result;
  struct tm *now_tm;

  time_result = time( &now_time );
  if( time_result == -1 ) {
    return 0;
  }

  now_tm = gmtime( &now_time );
  if( !now_tm ) {
    return 0;
  }

  return strftime( buffer,
                   RFC_5424_WHOLE_TIME_BUFFER_SIZE + 1,
                   "%FT%TZ",
                   now_tm );
}
