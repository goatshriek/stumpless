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

#ifndef __STUMPLESS_PRIVATE_TARGET_FILE_H
#  define __STUMPLESS_PRIVATE_TARGET_FILE_H

#  include <pthread.h>
#  include <stddef.h>
#  include <stdio.h>
#  include <stumpless/target.h>

/**
 * Internal representation of a file target.
 */
struct file_target {
/** A stream for the file this target writes to. */
  FILE *stream;
/**
 * Protects stream. This mutex must be locked by a thread before it can write
 * to the stream.
 */
  pthread_mutex_t stream_mutex;
};

void
destroy_file_target( struct file_target *target );

struct stumpless_target *
file_open_default_target( void );

struct file_target *
new_file_target( const char *filename );

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The stream_mutex is used to coordinate updates
 * to the logged file.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate file writes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 */
int
sendto_file_target( struct file_target *target,
                    const char *msg,
                    size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_FILE_H */
