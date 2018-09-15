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

struct stumpless_entry *
stumpless_add_wel_insertion_string( struct stumpless_entry *entry,
                                    LPCSTR str ) {
  LPSTR *new_strings;
  LPSTR str_copy;
  size_t str_length;
  size_t old_size;
  size_t new_size;

  clear_error(  );

  if( !entry || !str ) {
    raise_argument_empty(  );
    goto fail;
  }

  str_length = strlen( str );
  str_copy = alloc_mem( str_length );
  if( !str_copy ) {
    goto fail;
  }

  old_size = sizeof( LPCSTR ) * entry->wel_insertion_count;
  new_size = old_size + sizeof( LPCSTR );

  new_strings = realloc_mem( entry->wel_insertion_strings, new_size );
  if( !new_strings ) {
    goto fail_realloc;
  }

  memcpy( str_copy, str, str_length );
  str_copy[str_length] = '\0';
  new_strings[entry->wel_insertion_count] = str_copy;

  entry->wel_insertion_strings = new_strings;
  entry->wel_insertion_count++;
  return entry;


fail_realloc:
  free_mem( str_copy );
fail:
  return NULL;
}
