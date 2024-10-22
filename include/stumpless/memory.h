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
#  include <stumpless/config.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes the default target if it has been opened, frees all memory allocated
 * internally, and performs any other necessary cleanup.
 *
 * This function serves as a final exit function, which should be called when
 * an application using the library is preparing to exit or when the library is
 * no longer needed. Before this function is called, all targets explicitly
 * opened must be closed (with the exception of the default target, which is
 * opened implicitly) and no pointers to any structs should be retained. Failing
 * to do this will result in undefined behavior.
 *
 * Calling other functions after a call to this function is acceptable, however
 * execution times may be longer than usual as memory used to cache objects may
 * need to be allocated. If other functions are called, this function should be
 * called again before exit to ensure a memory leak does not exist.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * might be using.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of the
 * memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_free_all( void );

/**
 * Frees all memory allocated internally to the calling thread, and performs
 * any other thread-specific cleanup.
 *
 * This function should be called in any thread that has used stumpless
 * functions before it exits so that caches and other structures can be cleaned
 * up. It is not a substitute for stumpless_free_all, but is called by it and
 * can be left out if stumpless_free_all will be called later in the same
 * thread.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as it only operates on thread-local resources.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of the
 * memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_free_thread( void );

/**
 * Sets the function used by the library to allocate memory.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it changes the memory allocation
 * scheme, which could cause an operation to use the old function for some
 * allocation and the new function for others. If you need to set any of the
 * memory management functions, it should be done before starting multiple
 * threads with access to shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers for the same reason
 * as it is not thread safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the assignment is not guaranteed to be atomic.
 *
 * @param malloc_func A pointer to the allocation function that is desired. This
 * function must have the same signature as the standard library \c malloc
 * function (which is the default if this is not called).
 *
 * @return The new allocation function.
 */
STUMPLESS_PUBLIC_FUNCTION
void *
( *stumpless_set_malloc( void * ( *malloc_func )( size_t ) ) )
( size_t );

/**
 * Sets the function used by the library to free memory.
 *
 * The provided free function must be able to handle a NULL pointer as the
 * provided argument.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it changes the memory allocation
 * scheme, which could cause an operation to use the old function for some
 * allocation and the new function for others. If you need to set any of the
 * memory management functions, it should be done before starting multiple
 * threads with access to shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers for the same reason
 * as it is not thread safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the assignment is not guaranteed to be atomic.
 *
 * @param free_func A pointer to the memory deallocation function that is
 * desired. This function must have the same signature as the standard library
 * \c free function (which is the default if this is not called).
 *
 * @return The new deallocation function.
 */
STUMPLESS_PUBLIC_FUNCTION
void
( *stumpless_set_free( void ( *free_func )( void *) ) )
( void * );

/**
 * Sets the function used by the library to reallocate memory.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it changes the memory allocation
 * scheme, which could cause an operation to use the old function for some
 * allocation and the new function for others. If you need to set any of the
 * memory management functions, it should be done before starting multiple
 * threads with access to shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers for the same reason
 * as it is not thread safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the assignment is not guaranteed to be atomic.
 *
 * @param realloc_func A pointer to the memory reallocation function that is
 * desired. This function must have the same signature as the standard library
 * \c realloc function (which is the default if this is not called).
 *
 * @return The new reallocation function.
 */
STUMPLESS_PUBLIC_FUNCTION
void *
( *stumpless_set_realloc( void * ( *realloc_func ) ( void *, size_t) ) )
( void *, size_t );

/**
 * Retrieves the current malloc function used by the library.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it does not modify any global state.
 * It simply retrieves a pointer to the current memory allocation function.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers since it does not
 * cause any side effects or modify state.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled as it does not perform any blocking operations.
 *
 * @return A pointer to the current malloc function.
 */
STUMPLESS_PUBLIC_FUNCTION
void *(*stumpless_get_malloc(void))(size_t size);

/**
 * Retrieves the current free function used by the library.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it does not modify any global state.
 * It simply retrieves a pointer to the current memory deallocation function.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers since it does not
 * cause any side effects or modify state.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled as it does not perform any blocking operations.
 *
 * @return A pointer to the current free function.
 */
STUMPLESS_PUBLIC_FUNCTION
void (*stumpless_get_free(void))(void *ptr);

/**
 * Retrieves the current realloc function used by the library.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it does not modify any global state.
 * It simply retrieves a pointer to the current memory reallocation function.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers since it does not
 * cause any side effects or modify state.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled as it does not perform any blocking operations.
 *
 * @return A pointer to the current realloc function.
 */
STUMPLESS_PUBLIC_FUNCTION
void *(*stumpless_get_realloc(void))(void *ptr, size_t size);

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_MEMORY_H */
