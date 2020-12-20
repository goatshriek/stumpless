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
#include "private/config/no_vsnprintf_s.h"
#include "private/memory.h"

char *
no_vsnprintf_s_format_string( const char *format,
                              va_list subs,
                              size_t *length ) {
  char *buffer;
  size_t buffer_size = 128;
  int result;
  char *new_buffer;

  buffer = alloc_mem( buffer_size );
  if( !buffer ) {
    goto fail;
  }

  result = vsnprintf( buffer, buffer_size, format, subs );
  if( result < 0 ) {
    goto fail_buffer;
  }

  if( result > buffer_size ) {

    new_buffer = realloc_mem( buffer, result );
    if( !new_buffer ) {
      goto fail_buffer;
    }
    buffer = new_buffer;

    result = vsnprintf( buffer, buffer_size, format, subs );
    if( result < 0 ) {
      goto fail_buffer;
    }

  }

  *length = result;
  return buffer;

fail_buffer:
  free_mem( buffer );
fail:
  return NULL;
}
