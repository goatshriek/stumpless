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

/** @file
 * Functions for controlling memory allocation during execution.
 */

#ifndef __STUMPLESS_MEMORY_H
#  define __STUMPLESS_MEMORY_H

#  include <stddef.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Frees all memory allocated internally by library calls.
 *
 * This function serves as a final exit function, which should be called when
 * an application using the library is preparing to exit or when the library is
 * no longer needed. Before this function is called, all targets must be closed
 * and no pointers to any structs should be retained. Failing to do this will
 * result in undefined behavior.
 *
 * Calling other functions after a call to this function is acceptable, however
 * execution times may be longer than usual as memory used to cache objects may
 * need to be allocated. If other functions are called, this function should be
 * called again before exit to ensure a memory leak does not exist.
 */
void
stumpless_free_all( void );

void *
( *stumpless_set_malloc( void * ( *malloc_func )( size_t ) ) )
( size_t );

void
( *stumpless_set_free( void ( *free_func )( void *) ) )
( void * );

void *
( *stumpless_set_realloc( void * ( *realloc_func ) ( void *, size_t) ) )
( void *, size_t );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_MEMORY_H */
