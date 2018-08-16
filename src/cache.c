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
#include "private/cache.h"
#include "private/memory.h"

void *
cache_alloc( struct cache *c ) {
  size_t i;

  for( i = 0; i < c->size; i++ ) {
    if( c->locks[i] == 0 ) {
      c->locks[i] = 1;
      return c->mem + ( i * c->entry_size );
    }
  }

  // todo need to expand the cache here instead
  return NULL;
}

void
cache_free( struct cache *c, void *entry ) {
  size_t index;

  index = ( ( char * ) entry - c->mem ) / c->entry_size;
  c->locks[index] = 0;
}

struct cache *
cache_new( size_t size, void ( *entry_init ) ( void * ) ) {
  struct cache *c;
  char *mem;
  size_t mem_size, i;

  c = alloc_mem( sizeof( *c ) );
  if( !c ) {
    goto fail;
  }

  mem_size = get_paged_size( size );
  mem = alloc_mem( mem_size );
  if( !mem ) {
    goto fail_mem;
  }

  c->entry_init = entry_init;
  c->entry_size = size;
  c->mem = mem;
  c->size = mem_size / size;

  for( i = 0; i < c->size; i++ ) {
    c->locks[i] = 0;

    if( entry_init ) {
      entry_init( mem + ( i * c->entry_size ) );
    }
  }

  return c;


fail_mem:
  free_mem( c );
fail:
  return NULL;
}
