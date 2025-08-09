/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_MEMORY_H
#  define __STUMPLESS_PRIVATE_MEMORY_H

#  include <stddef.h>

/**
 * Allocates a block of memory of the specified size.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it relies on `stumpless_malloc`, which is
 * presumed to be thread-safe. It does not share or modify any global state.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Memory allocation functions such as `stumpless_malloc` may use non-reentrant
 * system calls, making this function unsafe for use in signal handlers.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * The function is unsafe for asynchronous cancellation. If a thread is
 * cancelled during memory allocation, the resultant state is undefined.
 *
 * @param size The size of the block of memory to be allocated, in bytes.
 *
 * @return A pointer to the allocated memory block, or NULL if the allocation
 *         fails. If allocation fails, it triggers a memory allocation failure
 *         error.
 */
void *alloc_mem( size_t size );

/**
 * Frees a previously allocated block of memory.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it relies on `stumpless_free`, which is
 * presumed to be thread-safe. It does not share or modify any global state.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Freeing memory is not generally safe in signal handlers due to possible use of
 * non-reentrant system calls, making this function unsafe for asynchronous signal
 * handling.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * The function is unsafe for asynchronous cancellation. If a thread is
 * cancelled during memory deallocation, the memory may not be properly freed.
 *
 * @param mem A pointer to the memory block to be freed. This must have been
 *            allocated by a corresponding alloc_mem or similar function.
 */
void free_mem( const void *mem );

/**
 * Computes the next power-of-two greater than or equal to the specified size.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it only performs arithmetic operations and
 * retrieves page size through `config_getpagesize`, assumed to be a thread-safe
 * function.
 *
 * **Async Signal Safety: AS-Safe**
 * This function performs only safe arithmetic and read-only operations, making
 * it safe to use in signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * The function's arithmetical nature ensures it is not susceptible to issues
 * from asynchronous cancellation.
 *
 * @param size The size for which the next power-of-two page size is to be
 *             calculated.
 *
 * @return The next power-of-two page size greater than or equal to the specified
 *         size.
 */
size_t get_paged_size( size_t size );

/**
 * Reallocates a block of memory to a new size.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it relies on `stumpless_realloc`, which is
 * presumed to be thread-safe. It does not share or modify any global state.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Memory reallocation functions such as `stumpless_realloc` may use non-reentrant
 * system calls, making this function unsafe for use in signal handlers.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * The function is unsafe for asynchronous cancellation. If a thread is
 * cancelled during memory reallocation, the resultant state is undefined.
 *
 * @param mem A pointer to the memory block to be reallocated. This must have been
 *            allocated by a corresponding alloc_mem or similar function.
 *
 * @param size The new size for the memory block, in bytes.
 *
 * @return A pointer to the newly allocated memory block, or NULL if the
 *         reallocation fails. If reallocation fails, it triggers a memory
 *         allocation failure error.
 */
void *realloc_mem( const void *mem, size_t size );

// A wrapper for alloc_mem that checks for overflow before proper allocation
void *alloc_array( size_t item_count, size_t item_size );

// A wrapper for realloc_mem that checks for overflow before proper allocation
void *realloc_array( const void *mem, size_t item_count, size_t item_size );

#endif /* __STUMPLESS_PRIVATE_MEMORY_H */
