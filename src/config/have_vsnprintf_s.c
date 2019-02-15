// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include "private/config/have_vsnprintf_s.h"
#include "private/memory.h"

char *
vsnprintf_s_format_string( const char *format, va_list subs, size_t *length ) {
  char *buffer = NULL;
  char *new_buffer;
  size_t buffer_size = 128;
  int result = -1;

  do {
    new_buffer = realloc_mem( buffer, buffer_size );
    if( !new_buffer ) {
      goto fail;
    }
    buffer = new_buffer;

    result = vsnprintf_s( buffer, buffer_size, _TRUNCATE, format, subs );
    buffer_size = buffer_size << 1;
  } while( result < 1 );

  *length = result;
  return buffer;

fail:
  free_mem( buffer );
  return NULL;
}
