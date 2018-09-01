// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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

#include <time.h>
#include <windows.h>
#include "private/config/have_gmtime_s.h"

int
gmtime_s_get_now( struct tm *now_tm, struct timespec *now_ts ) {
  SYSTEMTIME now_st;

  GetSystemTime( &now_st );

  now_tm->tm_sec = now_st.wSecond;
  now_tm->tm_min = now_st.wMinute;
  now_tm->tm_hour = now_st.wHour;
  now_tm->tm_mday = now_st.wDay;
  now_tm->tm_mon = now_st.wMonth - 1;
  now_tm->tm_year = now_st.wYear - 1900;
  now_tm->tm_isdst = -1;

  // only good for the fraction, not for absolute value
  now_ts->tv_nsec = now_st.wMilliseconds * 1000;

  return 0;
}
