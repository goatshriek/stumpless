// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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
#include <windows.h>
#include "private/config/support_windows_get_now.h"
#include "private/formatter.h"

size_t
windows_get_now( char *buffer ) {
  wchar_t locale_name[LOCALE_NAME_MAX_LENGTH];
  SYSTEMTIME now_st;
  int date_result;
  int time_result;
  int snprintf_result;
  wchar_t full_date[RFC_5424_FULL_DATE_BUFFER_SIZE];
  wchar_t full_time[RFC_5424_FULL_TIME_BUFFER_SIZE];
  size_t conversion_count;
  errno_t error;

  GetUserDefaultLocaleName(locale_name, LOCALE_NAME_MAX_LENGTH);
  GetSystemTime( &now_st );

  snprintf_result = sprintf_s(buffer,
     RFC_5424_TIMESTAMP_BUFFER_SIZE,
      "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
      now_st.wYear,
      now_st.wMonth,
      now_st.wDay,
      now_st.wHour,
      now_st.wMinute,
      now_st.wSecond,
      now_st.wMilliseconds);

  return snprintf_result;

  /*date_result = GetDateFormatEx( locale_name,
                                 0,
                                 &now_st,
                                 L"yyyy'-'MM'-'dd",
                                 full_date,
                                 RFC_5424_FULL_DATE_BUFFER_SIZE, NULL );
  if( date_result == 0 ) {
    return 0;
  }
  date_result--;                // drop off the NULL character

  error = wcstombs_s( &conversion_count,
                      buffer,
                      RFC_5424_FULL_DATE_BUFFER_SIZE,
                      full_date, RFC_5424_FULL_DATE_BUFFER_SIZE - 1 );
  if( error != 0 ) {
    return 0;
  }

  time_result = GetTimeFormatEx( locale_name,
                                 0,
                                 &now_st,
                                 L"'T'HH':'mm':'ss",
                                 full_time, RFC_5424_FULL_TIME_BUFFER_SIZE );
  if( time_result == 0 ) {
    return 0;
  }
  time_result--;                // drop off the NULL character

  error = wcstombs_s( &conversion_count,
                      buffer + date_result,
                      RFC_5424_FULL_TIME_BUFFER_SIZE,
                      full_time, RFC_5424_FULL_TIME_BUFFER_SIZE - 1 );
  if( error != 0 ) {
    return 0;
  }

  snprintf_result = snprintf( buffer + date_result + time_result,
                              RFC_5424_TIME_SECFRAC_BUFFER_SIZE + 2,
                              ".%03dZ", now_st.wMilliseconds );
  if( snprintf_result < 0 ) {
    return 0;
  }

  return date_result + time_result + snprintf_result;
  */
}
