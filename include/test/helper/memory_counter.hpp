/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP
#  define __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP

#include <gtest/gtest.h>
#include <stddef.h>
#include <stdlib.h>
#include <stumpless.h>

struct memory_counter {
  size_t malloc_count;
  size_t alloc_total;
  size_t realloc_count;
  size_t free_count;
  size_t free_total;
};

#define INIT_MEMORY_COUNTER(PREFIX)                                            \
PREFIX##_memory_counter.malloc_count = 0;                                      \
PREFIX##_memory_counter.alloc_total = 0;                                       \
PREFIX##_memory_counter.realloc_count = 0;                                     \
PREFIX##_memory_counter.free_count = 0;                                        \
PREFIX##_memory_counter.free_total = 0;                                        \
stumpless_set_malloc( PREFIX##_memory_counter_malloc );                        \
stumpless_set_realloc( PREFIX##_memory_counter_realloc );                      \
stumpless_set_free( PREFIX##_memory_counter_free );


#define NEW_MEMORY_COUNTER(PREFIX)                                             \
static struct memory_counter PREFIX##_memory_counter;                          \
static std::map<void *, size_t> PREFIX##_memory_counter_map;                   \
                                                                               \
static void *                                                                  \
PREFIX##_memory_counter_malloc( size_t size ) {                                \
  void *mem;                                                                   \
                                                                               \
  PREFIX##_memory_counter.malloc_count++;                                      \
  PREFIX##_memory_counter.alloc_total += size;                                 \
  mem = malloc( size );                                                        \
                                                                               \
  if( mem != NULL ) {                                                          \
    PREFIX##_memory_counter_map[mem] = size;                                   \
  }                                                                            \
                                                                               \
  return mem;                                                                  \
}                                                                              \
                                                                               \
static void *                                                                  \
PREFIX##_memory_counter_realloc( void *mem, size_t new_size ) {                \
  void *new_mem;                                                               \
  size_t old_size;                                                             \
                                                                               \
  PREFIX##_memory_counter.realloc_count++;                                     \
  new_mem = realloc( mem, new_size );                                          \
  if( new_mem != NULL ) {                                                      \
    old_size = PREFIX##_memory_counter_map[mem];                               \
    PREFIX##_memory_counter_map[mem] = 0;                                      \
    PREFIX##_memory_counter_map[new_mem] = new_size;                           \
    PREFIX##_memory_counter.alloc_total += new_size - old_size;                \
  }                                                                            \
                                                                               \
  return new_mem;                                                              \
}                                                                              \
                                                                               \
static void                                                                    \
PREFIX##_memory_counter_free( void *mem ) {                                    \
  PREFIX##_memory_counter.free_count++;                                        \
  PREFIX##_memory_counter.free_total += PREFIX##_memory_counter_map[mem];      \
  free( mem );                                                                 \
}

#define SET_STATE_COUNTERS( S, P )                                             \
(S).counters["CallsToAlloc"] = ( double ) P##_memory_counter.malloc_count;     \
(S).counters["MemoryAllocated"] = ( double ) P##_memory_counter.alloc_total;   \
(S).counters["CallsToRealloc"] = ( double ) P##_memory_counter.realloc_count;  \
(S).counters["CallsToFree"] = ( double ) P##_memory_counter.free_count;        \
(S).counters["MemoryFreed"] = ( double ) P##_memory_counter.free_total;

#define ASSERT_NO_LEAK( PREFIX )                                               \
ASSERT_EQ( PREFIX##_memory_counter.alloc_total,                                \
           PREFIX##_memory_counter.free_total )

#endif /* __STUMPLESS_TEST_HELPER_MEMORY_COUNTER_HPP */
