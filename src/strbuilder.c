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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private/config/wrapper.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strbuilder.h"

static size_t
increase_size( struct strbuilder *builder ) {
  char *old_buffer, *new_buffer;
  size_t old_size, new_size;

  old_buffer = builder->buffer;
  old_size = builder->buffer_end - old_buffer;
  new_size = old_size * 2;
  new_buffer = realloc( old_buffer, new_size );
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
  size_t size_added, size_left;

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
  if( !builder ) {
    return NULL;
  }

  if( builder->position == builder->buffer_end ) {
    if( increase_size( builder ) == 0 ) {
      return NULL;
    }
  }

  *( builder->position ) = c;
  ( builder->position )++;

  return builder;
}

struct strbuilder *
strbuilder_append_int( struct strbuilder *builder, int i ) {
  char buffer[100];             // todo need to make more precise

  if( !builder ) {
    return NULL;
  }

  snprintf( buffer, 100, "%d", i );
  return strbuilder_append_string( builder, buffer );
}

struct strbuilder *
strbuilder_append_string( struct strbuilder *builder, const char *str ) {
  const char *curr;

  if( !builder ) {
    return NULL;
  }

  curr = str;
  while ( *curr != '\0' ) {
    if( builder->position == builder->buffer_end ) {
      if( increase_size( builder ) == 0 ) {
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
strbuilder_destroy( struct strbuilder *builder ) {
  free_mem( builder );
}

char *
strbuilder_to_string( struct strbuilder *builder ) {
  if( strbuilder_append_char( builder, '\0' ) == NULL ) {
    return NULL;
  } else {
    return builder->buffer;
  }
}

struct strbuilder *
strbuilder_new( void ) {
  struct strbuilder *builder;
  char *buffer;
  size_t size;

  builder = alloc_mem( sizeof( *builder ) );
  if( !builder ) {
    goto fail;
  }

  size = config_getpagesize(  );

  buffer = alloc_mem( size );
  if( !buffer ) {
    goto fail_buffer;
  }

  builder->buffer = buffer;
  builder->position = buffer;
  builder->buffer_end = buffer + size;

  return builder;

fail_buffer:
  free_mem( builder );
fail:
  return NULL;
}
