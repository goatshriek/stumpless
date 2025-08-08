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

/**
 * Allocates an array of `item_count` elements, each of size `item_size`.
 *
 * This is a thin wrapper around `alloc_mem` that checks for integer
 * overflow in the multiplication `item_count * item_size` before calling
 * through to the underlying allocator.
 *
 * **Thread Safety: MT-Safe**  
 * Relies on `alloc_mem` (and the C heap), which is assumed thread-safe.
 *
 * **Async Signal Safety: AS-Unsafe**  
 * Allocation may invoke non-reentrant calls (e.g. `malloc`), so this
 * cannot be used in signal handlers.
 *
 * **Async Cancel Safety: AC-Unsafe**  
 * If cancellation occurs during allocation, the heap state may become
 * inconsistent.
 *
 * @param item_count  Number of elements to allocate.
 * @param item_size   Size in bytes of each element.
 * @return A pointer to the newly allocated zero-initialized array,
 *         or NULL if overflow is detected or allocation fails.
 */
void *alloc_array( size_t item_count, size_t item_size );

/**
 * Reallocates an array previously allocated with `alloc_array` (or
 * another `realloc_array`) to hold `item_count` elements of size
 * `item_size`, with overflow checking.
 *
 * If `mem` is NULL, behaves like `alloc_array`. If `item_count * item_size`
 * would overflow, no reallocation is attempted and NULL is returned.
 *
 * **Thread Safety: MT-Safe**  
 * Depends on `realloc_mem`, which is assumed to be thread-safe.
 *
 * **Async Signal Safety: AS-Unsafe**  
 * May call non-reentrant routines; unsafe in signal contexts.
 *
 * **Async Cancel Safety: AC-Unsafe**  
 * Cancellation during the call may leave the heap in an undefined state.
 *
 * @param mem         Pointer to an existing block (from `alloc_array`),
 *                    or NULL.
 * @param item_count  New number of elements.
 * @param item_size   Size in bytes of each element.
 * @return A pointer to the resized block, or NULL if overflow is
 *         detected or reallocation fails. In case of failure with
 *         non-NULL `mem`, the original block remains valid.
 */
void *realloc_array( const void *mem, size_t item_count, size_t item_size );

#endif /* __STUMPLESS_PRIVATE_MEMORY_H */