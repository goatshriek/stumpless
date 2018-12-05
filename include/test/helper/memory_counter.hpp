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

#ifndef __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP
#  define __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP

#include <stddef.h>
#include <stdlib.h>

struct memory_counter {
  size_t malloc_count;
  size_t malloc_total;
  size_t realloc_count;
  size_t realloc_total;
  size_t free_count;
};

#define INIT_MEMORY_COUNTER(PREFIX)                                            \
PREFIX##_memory_counter.malloc_count = 0;                                      \
PREFIX##_memory_counter.malloc_total = 0;                                      \
PREFIX##_memory_counter.realloc_count = 0;                                     \
PREFIX##_memory_counter.realloc_total = 0;                                     \
PREFIX##_memory_counter.free_count = 0;


#define NEW_MEMORY_COUNTER(PREFIX)                                             \
static struct memory_counter PREFIX##_memory_counter;                          \
                                                                               \
static void *                                                                  \
PREFIX##_memory_counter_malloc( size_t size ) {                                \
  PREFIX##_memory_counter.malloc_count++;                                      \
  PREFIX##_memory_counter.malloc_total += size;                                \
  return malloc( size );                                                       \
}                                                                              \
                                                                               \
static void *                                                                  \
PREFIX##_memory_counter_realloc( void *mem, size_t new_size ) {                \
  PREFIX##_memory_counter.realloc_count++;                                     \
  PREFIX##_memory_counter.realloc_total += new_size;                           \
  return realloc( mem, new_size );                                             \
}                                                                              \
                                                                               \
static void                                                                    \
PREFIX##_memory_counter_free( void *mem ) {                                    \
  PREFIX##_memory_counter.free_count++;                                        \
  free( mem );                                                                 \
}

#endif /* __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP */
