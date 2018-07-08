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

#include <stddef.h>
#include <stdlib.h>
#include <stumpless/memory.h>
#include "private/error.h"
#include "private/memory.h"

typedef void *( *malloc_func_t ) ( size_t );
typedef void ( *free_func_t ) ( void * );

static malloc_func_t stumpless_malloc = malloc;
static free_func_t stumpless_free = free;

malloc_func_t
stumpless_set_malloc( malloc_func_t malloc_func ) {
  clear_error(  );

  if( !malloc_func ) {
    raise_argument_empty(  );
    return NULL;
  } else {
    stumpless_malloc = malloc_func;
    return stumpless_malloc;
  }
}

free_func_t
stumpless_set_free( free_func_t free_func ) {
  clear_error(  );

  if( !free_func ) {
    raise_argument_empty(  );
    return NULL;
  } else {
    stumpless_free = free_func;
    return stumpless_free;
  }
}

/* private functions */

void *
alloc_mem( size_t amount ) {
  void *mem = stumpless_malloc( amount );
  if( !mem ) {
    raise_memory_allocation_failure(  );
    return NULL;
  }

  return mem;
}

void
free_mem( void *mem ) {
  if( mem ) {
    stumpless_free( mem );
  }
}
