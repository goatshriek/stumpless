// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2023 Joel E. Anderson
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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <stddef.h>
#include <stdio.h>
#include "private/config/windows_get_now_supported.h"
#include "private/formatter.h"

size_t
windows_get_now( char *buffer ) {
  SYSTEMTIME now_st;
  int sprintf_result;

  GetSystemTime( &now_st );

  sprintf_result = sprintf_s( buffer,
                              RFC_5424_TIMESTAMP_BUFFER_SIZE,
                              "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
                              now_st.wYear,
                              now_st.wMonth,
                              now_st.wDay,
                              now_st.wHour,
                              now_st.wMinute,
                              now_st.wSecond,
                              now_st.wMilliseconds );

  return sprintf_result < 0 ? 0 : sprintf_result;
}
