/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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
#  include <stumpless/config.h>
#  include "private/config/wrapper/thread_safety.h"

struct cache {
  void ( *entry_init ) ( void * );
  void ( *entry_teardown ) ( void * );
  size_t entry_size;
  char **pages;
  size_t page_count;
  size_t page_size;
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
  config_mutex_t mutex;
#  endif
};

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to ensure that the cache is
 * accessed safely.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock and possibly memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked and the possible
 * use of memory management functions.
 */
void *
cache_alloc( struct cache *c );

/**
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other
 * threads may be using.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions and the destruction of a lock that may be held
 * by another thread.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked/not destroyed
 * and the possible use of memory management functions.
 */
void
cache_destroy( const struct cache *c );

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to ensure that the cache is
 * accessed safely.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock and possibly memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked and the possible
 * use of memory management functions.
 */
void
cache_free( const struct cache *c, const void *entry );

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe as it does not expose resources that need to
 * be coordinated on until it is finished.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of memory management functions.
 */
struct cache *
cache_new( size_t size,
           void ( *entry_init ) ( void * ),
           void ( *entry_destroy ) ( void * ) );

#endif /* __STUMPLESS_PRIVATE_CACHE_H */
