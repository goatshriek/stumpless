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

#  include <pthread.h>
#  include <stddef.h>

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
/**
 * Protects updates to buffer and the position counters. This mutex must be
 * locked by a thread before it can read from or write to the buffer.
 *
 * Size is _not_ protected by this mutex, as it must not change over the life
 * of the buffer target.
 */
  pthread_mutex_t buffer_mutex;
};

void
destroy_buffer_target( const struct buffer_target *target );

struct buffer_target *
new_buffer_target( char *buffer, size_t size );

int
sendto_buffer_target( struct buffer_target *target,
                      const char *msg,
                      size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_BUFFER_H */
