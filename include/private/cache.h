/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_CACHE_H
#  define __STUMPLESS_PRIVATE_CACHE_H

#  include <stddef.h>

struct cache {
  void ( *entry_init ) ( void * );
  size_t entry_size;
  char *mem;
  size_t size;
  char locks[500];
};

void *
cache_alloc( struct cache *c );

void
cache_free( struct cache *c, void *entry );

struct cache *
cache_new( size_t size, void ( *entry_init ) ( void * ) );

#endif /* __STUMPLESS_PRIVATE_CACHE_H */
