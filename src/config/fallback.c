// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2022 Joel E. Anderson
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
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stumpless/config.h>
#include "private/config/fallback.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"

/** Used to prevent data races on calls to wcstombs. */
static config_atomic_bool_t wcstombs_free = config_atomic_bool_true;

/**
 * Gains exclusive access to call wcstombs. This is to prevent potential race
 * conditions with the internal state used by wcstombs.
 */
static
void
lock_wcstombs( void ) {
  while( !config_compare_exchange_bool( &wcstombs_free, true, false ) );
}
/**
 * Releases exclusive access to call wcstombs.
 */
static
void
unlock_wcstombs( void ) {
  config_write_bool( &wcstombs_free, true );
}

char *
fallback_copy_wstring_to_cstring( const wchar_t *str, int *copy_size ) {
  size_t buffer_size;
  char *buffer;
  size_t conversion_result;

  lock_wcstombs(  );
  conversion_result = wcstombs( NULL, str, 0 );
  unlock_wcstombs(  );
  if( conversion_result == -1 ) {
    raise_wide_conversion_failure( errno, L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail;
  }

  buffer_size = conversion_result + 1; // add NULL terminator
  buffer = alloc_mem( buffer_size );
  if( !buffer ) {
    goto fail;
  }

  lock_wcstombs(  );
  conversion_result = wcstombs( buffer, str, buffer_size );
  unlock_wcstombs(  );
  if( conversion_result == -1 ) {
    raise_wide_conversion_failure( errno, L10N_ERRNO_ERROR_CODE_TYPE );
    goto cleanup_and_fail;
  }

  if( copy_size ) {
    *copy_size = buffer_size;
  }

  return buffer;

cleanup_and_fail:
  free_mem( buffer );
fail:
  return NULL;
}

int
fallback_gethostname( char *buffer, size_t namelen ) {
  if( namelen < 2 ) {
    return -1;
  } else {
    buffer[0] = '-';
    buffer[1] = '\0';
    return 0;
  }
}

size_t
fallback_getpagesize( void ) {
  return STUMPLESS_FALLBACK_PAGESIZE;
}

int
fallback_getpid( void ) {
  return 0;
}
