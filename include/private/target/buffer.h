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

#ifndef __STUMPLESS_PRIVATE_TARGET_BUFFER_H
#  define __STUMPLESS_PRIVATE_TARGET_BUFFER_H

#  include <stddef.h>
#  include <stumpless/config.h>
#  include "private/config/wrapper/thread_safety.h"

/**
 * Internal representation of a buffer target.
 *
 * Buffer targets use a ring buffer approach, wrapping around when the end
 * of the buffer is reached, and writing over older messages.
 */
struct buffer_target {
/** The buffer logged messages are written into. */
  char *buffer;
/** The size of buffer. */
  size_t size;
/** The index to start reading from. */
  size_t read_position;
/** The index to start writing to. */
  size_t write_position;
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects updates to buffer and the position counters. This mutex must be
 * locked by a thread before it can read from or write to the buffer.
 *
 * Size is _not_ protected by this mutex, as it must not change over the life
 * of the buffer target.
 */
  config_mutex_t buffer_mutex;
#  endif
};

/**
 * @brief Cleans up and deallocates a buffer target structure.
 *
 * This function is responsible for releasing the resources associated with
 * a `buffer_target` structure. Specifically, it destroys the mutex protecting
 * the buffer and frees the memory occupied by the `buffer_target` instance.
 *
 * **Thread Safety: MT-Unsafe**
 * The caller must ensure that no other threads are accessing the buffer_target 
 * while this function is executed.
 * 
 * **Async Signal Safety: AS-Unsafe*
 * The function destroys a mutex, which is not safe to use in a signal handler context.
 * 
 * **Async Cancel Safety: AC-Unsafe**
 * The function is not safe to call from threads that may be asynchronously canceled.
 * If a thread is canceled while destroying the mutex or freeing memory, it might leave
 * the program in an inconsistent state.
 * 
 * @param target A pointer to the `buffer_target` structure to be destroyed.
 *               Must not be `NULL`.
 */
void
destroy_buffer_target( const struct buffer_target *target );

/**
 * @brief Creates and initializes a new buffer target structure.
 *
 * This function allocates memory for a `buffer_target` structure and initializes
 * its fields. The buffer target is designed to manage a pre-allocated buffer
 * with specified size, enabling read and write operations.
 *
 * **Thread Safety: MT-Safe**
 * The function is thread-safe because it initializes a mutex (buffer_mutex)
 * specifically for the buffer_target. This ensures that subsequent operations on
 * the buffer_target can be performed in a thread-safe manner.
 * 
 * **Async Signal Safety: AS-Unsafe*
 * It uses dynamic memory allocation (e.g., malloc or similar), which is not signal-safe. 
 * 
 * **Async Cancel Safety: AC-Unsafe**
 * The function is not safe to call from threads that may be asynchronously canceled
 * because the memory allocation (or its failure) might not handle thread cancellation properly
 * 
 * @param buffer A pointer to the pre-allocated memory buffer that this target
 *               will manage. This buffer must be valid for the lifetime of the
 *               `buffer_target` structure.
 * @param size The size of the buffer in bytes.
 *
 * @return A pointer to the newly allocated and initialized `buffer_target`
 *         structure, or `NULL` if memory allocation fails.
 */
struct buffer_target *
new_buffer_target( char *buffer, size_t size );

/**
 * @brief Writes a message to a buffer target, wrapping around if needed.
 *
 * This function writes a message to the buffer target, ensuring that the buffer
 * does not overflow. If the message is too large to fit in the buffer, an error
 * is raised. The function also ensures thread safety by locking a mutex during
 * the write operation.
 * 
 * **Thread Safety: MT-Safe**
 * The function is thread-safe because it uses a mutex (config_lock_mutex) to
 * synchronize access to the shared buffer and its associated read/write positions
 * 
 * **Async Signal Safety: AS-Unsafe*
 * It uses a non-reentrant lock (mutex) to coordinate access to the buffer.
 * Mutex operations are not safe in signal handler contexts.
 * 
 * **Async Cancel Safety: AC-Unsafe**
 * The function is not safe to call from threads that may be asynchronously canceled. 
 * If a thread is canceled while holding the mutex, the mutex might not be released,
 * potentially leading to deadlocks or inconsistent state
 * 
 * @param target A pointer to the `buffer_target` where the message will be written.
 *               Must not be `NULL`.
 * @param msg A pointer to the message to be written.
 * @param msg_length The length of the message, including a newline character.
 *
 * @return The number of characters written to the buffer, or `-1` if the
 *         message is too large to fit in the buffer.
 */
int
sendto_buffer_target( struct buffer_target *target,
                      const char *msg,
                      size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_BUFFER_H */
