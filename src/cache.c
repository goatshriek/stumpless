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
  size_t entries_per_page;
  size_t i;
  char *current_page;
  char *locks;

  current_page = c->pages[page_index];
  entries_per_page = c->page_size / ( c->entry_size + sizeof( char ) );
  for( i = 0; i < entries_per_page; i++ ) {
    locks = current_page + ( entries_per_page * c->entry_size );
    locks[i] = 0;

    if( c->entry_init ) {
      c->entry_init( current_page + ( i * c->entry_size ) );
    }
  }
}

static int
add_page( struct cache *c ) {
  size_t new_page_index;
  char **new_pages;
  char *new_page;

  new_pages = realloc_mem( c->pages, sizeof( char * ) * ( c->page_count + 1 ) );
  if( !new_pages ) {
    return -1;
  }

  new_page = alloc_mem( c->page_size );
  if( !new_page ) {
    return -1;
  }

  new_page_index = c->page_count;
  c->page_count++;

  c->pages = new_pages;
  c->pages[new_page_index] = new_page;
  init_page( c, new_page_index );

  return new_page_index;
}

void *
cache_alloc( struct cache *c ) {
  size_t i;
  size_t j;
  size_t entries_per_page;
  int new_page;
  char *current_page;
  char *locks;

  entries_per_page = c->page_size / ( c->entry_size + sizeof( char ) );
  for( i = 0; i < c->page_count; i++ ) {
    current_page = c->pages[i];
    locks = current_page + ( entries_per_page * c->entry_size );
    for( j = 0; j < entries_per_page; j++ ) {
      if( locks[j] == 0 ) {
        locks[j] = 1;
        return current_page + ( j * c->entry_size );
      }
    }
  }

  new_page = add_page( c );
  if( new_page < 0 ) {
    return NULL;
  }

  current_page = c->pages[new_page];
  locks = current_page + ( entries_per_page * c->entry_size );
  locks[0] = 1;
  return current_page;
}

void
cache_free( struct cache *c, void *entry ) {
  size_t entry_index;
  size_t i;
  size_t entries_per_page;
  char *current_page;
  char *locks;
  uintptr_t entry_int;
  uintptr_t current_page_int;

  entry_int = ( uintptr_t ) entry;

  for( i = 0; i < c->page_count; i++ ) {
    current_page = c->pages[i];
    current_page_int = ( uintptr_t ) current_page;

    if( entry_int >= current_page_int
        && entry_int < ( current_page_int + c->page_size ) ) {

      entries_per_page = c->page_size / ( c->entry_size + sizeof( char ) );
      locks = current_page + ( entries_per_page * c->entry_size );
      entry_index = ( ( char * ) entry - current_page ) / c->entry_size;
      locks[entry_index] = 0;

      return;
    }
  }
}

struct cache *
cache_new( size_t size, void ( *entry_init ) ( void * ) ) {
  struct cache *c;
  size_t first_page;

  c = alloc_mem( sizeof( *c ) );
  if( !c ) {
    goto fail;
  }

  c->pages = alloc_mem( sizeof( char * ) );
  if( !c->pages ) {
    goto fail_pages;
  }

  c->entry_init = entry_init;
  c->entry_size = size;
  c->page_size = get_paged_size( size );
  c->page_count = 0;

  first_page = add_page( c );
  if( first_page != 0 ) {
    goto fail_pages;
  }

  return c;


fail_pages:
  free_mem( c );
fail:
  return NULL;
}
