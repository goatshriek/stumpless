/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2025 Joel E. Anderson
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
#define __STUMPLESS_PRIVATE_TARGET_BUFFER_H

#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/target.h>
#include "private/config/wrapper/thread_safety.h"

/**
 * Internal representation of a buffer target.
 *
 * Buffer targets use a ring buffer approach, wrapping around when the end
 * of the buffer is reached, and writing over older messages.
 */
struct buffer_target {
/** The base target structure. */
  struct stumpless_target target;
/** The buffer logged messages are written into. */
  char *buffer;
/** The size of buffer. */
  size_t size;
/** The index to start reading from. */
  size_t read_position;
/** The index to start writing to. */
  size_t write_position;
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects updates to buffer and the position counters. This mutex must be
 * locked by a thread before it can read from or write to the buffer.
 *
 * The size field is _not_ protected by this mutex, as it must not change over
 * the life of the buffer target.
 */
  config_mutex_t buffer_mutex;
#endif
};

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
