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
#include <string.h>
#include "private/memory.h"
#include "private/strhelper.h"

char *
cstring_to_sized_string( const char *str, size_t *length ){
  char *sized_string;

  *length = strlen( str );
  sized_string = alloc_mem( *length );
  if( !sized_string ) {
    return NULL;
  }

  memcpy( sized_string, str, *length );

  return sized_string;
}
