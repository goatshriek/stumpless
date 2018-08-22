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

#include <stdint.h>
#include <stddef.h>
#include "private/cache.h"
#include "private/memory.h"

static void
init_page( struct cache *c, size_t page_index ) {
  size_t entries_per_page, i;

  entries_per_page = c->page_size / c->entry_size;
  for( i = 0; i < entries_per_page; i++ ) {
    c->locks[ ( ( page_index + 1 ) * entries_per_page ) + i] = 0;

    if( c->entry_init ) {
      c->entry_init( c->pages[page_index] + ( i * c->entry_size ) );
    }
  }
}

static int
add_page( struct cache *c ) {
  size_t new_page_index;
  char *new_page;

  new_page_index = c->page_count;
  c->page_count++;

  new_page = alloc_mem( c->page_size );
  if( !new_page ) {
    return -1;
  }

  init_page( c, new_page_index );
  c->pages[new_page_index] = new_page;

  return new_page_index;
}

void *
cache_alloc( struct cache *c ) {
  size_t i, entries_per_page;
  int new_page;
  char *current_page;

  entries_per_page = c->page_size / c->entry_size;
  for( i = 0; i < entries_per_page * c->page_count; i++ ) {
    if( c->locks[i] == 0 ) {
      c->locks[i] = 1;
      current_page = c->pages[i / entries_per_page];
      return current_page + ( ( i % entries_per_page ) * c->entry_size );
    }
  }

  new_page = add_page( c );
  if( new_page < 0 ) {
    return NULL;
  }

  c->locks[new_page * entries_per_page] = 1;
  return c->pages[new_page];
}

void
cache_free( struct cache *c, void *entry ) {
  size_t entry_index, i, entries_per_page;

  for( i = 0; i < c->page_count; i++ ) {
    if( (uintptr_t)entry >= (uintptr_t)c->pages[i] && (uintptr_t)entry < (uintptr_t)(c->pages[i] + c->page_size) ) {
      entries_per_page = c->page_size / c->entry_size;
      entry_index = ( i * entries_per_page ) + ( ( ( char * ) entry - c->pages[i] ) / c->entry_size );
      
      c->locks[entry_index] = 0;
      return;
    }
  }
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
  c->page_size = mem_size;
  c->pages[0] = mem;
  c->page_count = 1;

  for( i = 0; i < ( mem_size / size ); i++ ) {
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
