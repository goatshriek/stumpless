/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2019 Joel E. Anderson
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
 *
 * Some of these functions allow memory allcoation to use custom functions. This
 * might be useful if you have your own memory allocation routines or want to
 * lay down your own controls over memory used by the library. For example,
 * this capability is used extensively to test for error handling in memory
 * allocation failure scenarios, as well as to ensure that the same amount of
 * memory is freed as is allocated.
 */

#ifndef __STUMPLESS_MEMORY_H
#  define __STUMPLESS_MEMORY_H

#  include <stddef.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Frees all memory allocated internally, and performs any other necessary
 * cleanup.
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
 *
 * In a windows environment, this function will call WSACleanup.
 */
void
stumpless_free_all( void );

/**
 * Sets the function used by the library to allocate memory.
 *
 * @param malloc_func A pointer to the allocation function that is desired. This
 * function must have the same signature as the standard library \c malloc
 * function (which is the default if this is not called).
 *
 * @return The new allocation function.
 */
void *
( *stumpless_set_malloc( void * ( *malloc_func )( size_t ) ) )
( size_t );

/**
 * Sets the function used by the library to free memory.
 *
 * @param free_func A pointer to the memory deallocation function that is
 * desired. This function must have the same signature as the standard library
 * \c free function (which is the default if this is not called).
 *
 * @return The new deallocation function.
 */
void
( *stumpless_set_free( void ( *free_func )( void *) ) )
( void * );

/**
 * Sets the function used by the library to reallocate memory.
 *
 * @param realloc_func A pointer to the memory reallocation function that is
 * desired. This function must have the same signature as the standard library
 * \c realloc function (which is the default if this is not called).
 *
 * @return The new reallocation function.
 */
void *
( *stumpless_set_realloc( void * ( *realloc_func ) ( void *, size_t) ) )
( void *, size_t );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_MEMORY_H */
