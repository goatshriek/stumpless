// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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
#include "private/config/thread_safety_supported.h"
#include "private/config/wrapper/thread_safety.h"

static struct cache *mutex_cache = NULL;

void
thread_safety_destroy_mutex( const config_mutex_t *mutex ) {
  config_destroy_mutex( mutex );
  cache_free( mutex_cache, mutex );
}

void
thread_safety_free_all( void ) {
  cache_destroy( mutex_cache );
  mutex_cache = NULL;
}

config_mutex_t *
thread_safety_new_mutex( void ) {
  config_mutex_t *mutex;

  if( !mutex_cache ) {
    mutex_cache = cache_new( CONFIG_MUTEX_T_SIZE, NULL, NULL );
    if( !mutex_cache ) {
      return NULL;
    }
  }

  mutex = cache_alloc( mutex_cache );
  if( !mutex ) {
    return NULL;
  }

  config_init_mutex( mutex );
  return mutex;
}
