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
#include <string.h>
#include "private/cache.h"
#include "private/config/wrapper/getpagesize.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/strbuilder.h"

static struct cache *strbuilder_cache = NULL;

static void
strbuilder_init( void *builder ) {
  struct strbuilder *b = ( struct strbuilder * ) builder;

  b->buffer = NULL;
}

static void
strbuilder_teardown( void *builder ) {
  const struct strbuilder *b = ( struct strbuilder * ) builder;

  free_mem( b->buffer );
}

static size_t
increase_size( struct strbuilder *builder ) {
  const char *old_buffer;
  char *new_buffer;
  size_t old_size;
  size_t new_size;

  old_buffer = builder->buffer;
  old_size = builder->buffer_end - old_buffer;
  new_size = old_size * 2;
  new_buffer = realloc_mem( old_buffer, new_size );
  if( !new_buffer ) {
    return 0;
  }

  builder->position = new_buffer + ( builder->position - old_buffer );
  builder->buffer = new_buffer;
  builder->buffer_end = new_buffer + new_size;

  return old_size;
}

struct strbuilder *
strbuilder_append_buffer( struct strbuilder *builder, const char *buffer,
                          size_t size ) {
  size_t size_added;
  size_t size_left;

  if( !builder || !buffer ) {
    return NULL;
  }

  size_left = builder->buffer_end - builder->position;
  while ( size_left < size ) {
    size_added = increase_size( builder );
    if( size_added == 0 ) {
      return NULL;
    } else {
      size_left += size_added;
    }
  }

  memcpy( builder->position, buffer, size );
  builder->position += size;

  return builder;
}

struct strbuilder *
strbuilder_append_char( struct strbuilder *builder, char c ) {
  size_t old_size;

  if( !builder ) {
    return NULL;
  }

  if( builder->position == builder->buffer_end ) {
    old_size = increase_size( builder );
    if( old_size == 0 ) {
      return NULL;
    }
  }

  *( builder->position ) = c;
  ( builder->position )++;

  return builder;
}

struct strbuilder *
strbuilder_append_positive_int( struct strbuilder *builder, int i ) {
  struct strbuilder *result = builder;
  char buffer[MAX_INT_SIZE];
  size_t digit_count = 0;

  if( i == 0 ) {
    return strbuilder_append_char( builder, '0' );
  }

  while( i != 0 ) {
    buffer[digit_count] = ( i % 10 ) + 48;
    i /= 10;
    digit_count++;
  }

  while( digit_count > 0 ) {
    digit_count--;
    result = strbuilder_append_char( result, buffer[digit_count] );
  }

  return result;
}

struct strbuilder *
strbuilder_append_string( struct strbuilder *builder, const char *str ) {
  const char *curr;
  size_t old_size;

  if( !builder ) {
    return NULL;
  }

  curr = str;
  while ( *curr != '\0' ) {
    if( builder->position == builder->buffer_end ) {
      old_size = increase_size( builder );
      if( old_size == 0 ) {
        return NULL;
      }
    }

    *( builder->position ) = *curr;
    builder->position++;

    curr++;
  }

  return builder;
}

void
strbuilder_free_all( void ) {
  cache_destroy( strbuilder_cache );
  strbuilder_cache = NULL;
}

char *
strbuilder_get_buffer( struct strbuilder *builder, size_t * length ) {
  *length = builder->position - builder->buffer;
  return builder->buffer;
}

void
strbuilder_destroy( const struct strbuilder *builder ) {
  cache_free( strbuilder_cache, builder );
}

struct strbuilder *
strbuilder_new( void ) {
  struct strbuilder *builder;
  size_t size;

  if( !strbuilder_cache ) {
    strbuilder_cache = cache_new( sizeof( *builder ),
                                  strbuilder_init,
                                  strbuilder_teardown );

    if( !strbuilder_cache ) {
      goto fail;
    }
  }

  builder = cache_alloc( strbuilder_cache );
  if( !builder ) {
    goto fail;
  }


  if( !builder->buffer ) {
    size = config_getpagesize(  );

    builder->buffer = alloc_mem( size );
    if( !builder->buffer ) {
      goto fail_buffer;
    }

    builder->buffer_end = builder->buffer + size;
  }

  builder->position = builder->buffer;
  return builder;

fail_buffer:
  cache_free( strbuilder_cache, builder );
fail:
  return NULL;
}

char *
strbuilder_to_string( const struct strbuilder *builder ) {
  size_t string_length;
  char *string;

  if( !builder ) {
    goto fail;
  }

  string_length = builder->position - builder->buffer;
  string = alloc_mem( string_length + 1 );
  if( !string ) {
    goto fail;
  }

  memcpy( string, builder->buffer, string_length );
  string[string_length] = '\0';

  return string;

fail:
  return NULL;
}
