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

#include <errno.h>
#include <stddef.h>
#include <wchar.h>
#include "private/config/locale/wrapper.h"
#include "private/config/no_wcsrtombs_s.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"

char *
no_wcsrtombs_s_copy_wstring_to_cstring( const wchar_t *str, int *copy_size ) {
  size_t buffer_size;
  char *buffer;
  mbstate_t state;
  size_t conversion_result;

  conversion_result = wcsrtombs( NULL, &str, 0, &state );
  if( conversion_result == -1 ) {
    raise_wide_conversion_failure( errno, L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail;
  }

  buffer_size = conversion_result + 1; // add NULL terminator
  buffer = alloc_mem( buffer_size );
  if( !buffer ) {
    goto fail;
  }

  conversion_result = wcsrtombs( buffer, &str, buffer_size, &state );
  if( conversion_result == -1 ) {
    raise_wide_conversion_failure( errno, L10N_ERRNO_ERROR_CODE_TYPE );
    goto cleanup_and_fail;
  }

  if( copy_size ) {
    *copy_size = cap_size_t_to_int( buffer_size );
  }

  return buffer;

cleanup_and_fail:
  free_mem( buffer );
fail:
  return NULL;
}
