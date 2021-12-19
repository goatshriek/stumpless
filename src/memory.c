// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2021 Joel E. Anderson
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
#include <stdlib.h>
#include <stumpless/memory.h>
#include "private/config/wrapper.h"
#include "private/config/wrapper/journald.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/strbuilder.h"
#include "private/validate.h"

typedef void ( *free_func_t ) ( void * );
typedef void *( *malloc_func_t ) ( size_t );
typedef void *( *realloc_func_t ) ( void *, size_t );

static free_func_t stumpless_free = free;
static malloc_func_t stumpless_malloc = malloc;
static realloc_func_t stumpless_realloc = realloc;

void
stumpless_free_all( void ) {
  // thread-local resources must be destroyed before the global resources as
  // they may be using space from caches allocated globally
  stumpless_free_thread(  );

  target_free_global(  );
  entry_free_all(  );
  strbuilder_free_all(  );
  config_network_free_all(  );
  config_thread_safety_free_all(  );
}

void
stumpless_free_thread( void ) {
  clear_error(  );

  config_journald_free_thread(  );
  target_free_thread(  );
}

malloc_func_t
stumpless_set_malloc( malloc_func_t malloc_func ) {
  VALIDATE_ARG_NOT_NULL( malloc_func );

  clear_error(  );
  stumpless_malloc = malloc_func;
  return stumpless_malloc;
}

free_func_t
stumpless_set_free( free_func_t free_func ) {
  VALIDATE_ARG_NOT_NULL( free_func );

  clear_error(  );
  stumpless_free = free_func;
  return stumpless_free;
}

realloc_func_t
stumpless_set_realloc( realloc_func_t realloc_func ) {
  VALIDATE_ARG_NOT_NULL( realloc_func );

  clear_error(  );
  stumpless_realloc = realloc_func;
  return stumpless_realloc;
}

/* private functions */

void *
alloc_mem( size_t size ) {
  void *mem = stumpless_malloc( size );

  if( !mem ) {
    raise_memory_allocation_failure(  );
  }

  return mem;
}

void
free_mem( const void *mem ) {
  stumpless_free( ( void * ) mem );
}

size_t
get_paged_size( size_t size ) {
  size_t paged_size;

  paged_size = config_getpagesize(  );
  while ( paged_size < size ) {
    paged_size *= 2;
  }

  return paged_size;
}

void *
realloc_mem( void *mem, size_t size ) {
  void *new_mem = stumpless_realloc( mem, size );

  if( !new_mem ) {
    raise_memory_allocation_failure(  );
  }

  return new_mem;
}
