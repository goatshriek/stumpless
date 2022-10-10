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
#  include "private/config.h"

void
destroy_target( const struct stumpless_target *target );

void
lock_target( const struct stumpless_target *target );

struct stumpless_target *
new_target( enum stumpless_target_type type, const char *name );

COLD_FUNCTION
struct stumpless_target *
open_unsupported_target( struct stumpless_target *target );

/**
 * Ignores all parameters and raises a target unsupported error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
 *
 * @param target The target that the entry was to be sent to.
 *
 * @param entry The entry that was to be sent.
 *
 * @param msg The formatted message string that was to be sent, as a UTF-8
 * string.
 *
 * @param msg_size The size of the formatted message in bytes.
 *
 * @return Always returns -1.
 */
COLD_FUNCTION
int
send_entry_and_msg_to_unsupported_target( const struct stumpless_target *target,
                                          const struct stumpless_entry *entry,
                                          const char *msg,
                                          size_t msg_size );

COLD_FUNCTION
int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry );

COLD_FUNCTION
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

COLD_FUNCTION
int
unsupported_target_is_open( const struct stumpless_target *target );

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
