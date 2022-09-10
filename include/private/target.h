/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_H
#  define __STUMPLESS_PRIVATE_TARGET_H

#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>

void
destroy_target( const struct stumpless_target *target );

void
lock_target( const struct stumpless_target *target );

struct stumpless_target *
new_target( enum stumpless_target_type type, const char *name );

struct stumpless_target *
open_unsupported_target( struct stumpless_target *target );

int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry );

int
sendto_unsupported_target( const struct stumpless_target *target,
                           const char *msg,
                           size_t msg_length );

void
target_free_global( void );

void
target_free_thread( void );

void
unlock_target( const struct stumpless_target *target );

int
unsupported_target_is_open( const struct stumpless_target *target );

/**
 * Writes a message to the error stream. This is ignored if the error stream
 * is NULL.
 *
 * This function does not update or modify the per-thread error code. Failures
 * are silently ignored.
 * 
 * **Thread Safety: MT-Safe race:prefix**
 * This function is thread safe. A lock is used to coordinate writes to the
 * error stream.
*
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers, as it uses a
 * non-reentrant lock to synchronize access to the error stream.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the lock used to control access to the error stream may not
 * be released after a cancellation.
 *
 * @since v2.1.0.
 *
 * @param msg The message to be written to the error stream.
 *
 * @param msg_size The size of the message to be written in bytes.
 */
void
write_to_error_stream( const char *msg, size_t msg_size );

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
