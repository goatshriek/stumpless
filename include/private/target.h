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

/**
 * @file private_target.h
 * @brief Internal target management functions for the Stumpless logging library.
 *
 * This file defines private helper functions used for creating, locking,
 * unlocking, and managing logging targets internally within Stumpless.
 */

#ifndef __STUMPLESS_PRIVATE_TARGET_H
#  define __STUMPLESS_PRIVATE_TARGET_H

#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>
#  include "private/config.h"

/**
 * @brief Destroys the specified target.
 *
 * Frees all internal resources associated with the target.
 *
 * @param target The target to destroy.
 */
void
destroy_target( const struct stumpless_target *target );

/**
 * @brief Locks the specified target for thread-safe access.
 *
 * Prevents concurrent modifications by other threads.
 *
 * @param target The target to lock.
 */
void
lock_target( const struct stumpless_target *target );

/**
 * @brief Creates a new target object of the specified type and name.
 *
 * Allocates and initializes a new target.
 *
 * @param type The type of target to create.
 * @param name The name of the target.
 *
 * @return A pointer to the new target, or NULL on failure.
 */
struct stumpless_target *
new_target( enum stumpless_target_type type, const char *name );

/**
 * @brief Opens an unsupported target type.
 *
 * Used internally when a target type is not implemented on the platform.
 *
 * @param target The target to open.
 *
 * @return The same target pointer, unmodified.
 */
COLD_FUNCTION
struct stumpless_target *
open_unsupported_target( struct stumpless_target *target );

/**
 * @brief Handles attempts to send an entry and formatted message to an unsupported target.
 *
 * Ignores all parameters and raises a "target unsupported" error.
 *
 * **Thread Safety:** MT-Safe  
 * **Async Signal Safety:** AS-Unsafe  
 * **Async Cancel Safety:** AC-Unsafe
 *
 * @param target The target the entry was to be sent to.
 * @param entry The entry that was to be sent.
 * @param msg The formatted UTF-8 message string.
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

/**
 * @brief Handles attempts to send an entry to an unsupported target.
 *
 * Always raises a "target unsupported" error.
 *
 * @param target The target the entry was to be sent to.
 * @param entry The entry that was to be sent.
 *
 * @return Always returns -1.
 */
COLD_FUNCTION
int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry );

/**
 * @brief Handles attempts to send raw message data to an unsupported target.
 *
 * Always raises a "target unsupported" error.
 *
 * @param target The target the message was to be sent to.
 * @param msg The message string.
 * @param msg_length The length of the message string.
 *
 * @return Always returns -1.
 */
COLD_FUNCTION
int
sendto_unsupported_target( const struct stumpless_target *target,
                           const char *msg,
                           size_t msg_length );

/**
 * @brief Frees global memory used by targets.
 *
 * Should be called during library shutdown to release all target-related
 * global resources.
 */
void
target_free_global( void );

/**
 * @brief Frees thread-local memory used by targets.
 *
 * Should be called when a thread that used target functions exits.
 */
void
target_free_thread( void );

/**
 * @brief Gets the value of a target option without validation.
 *
 * Internal use only — assumes the target pointer is valid.
 *
 * @param target The target to query.
 * @param option The option identifier.
 *
 * @return The value of the specified option.
 */
int
unchecked_get_option( const struct stumpless_target *target, int option );

/**
 * @brief Unlocks the specified target.
 *
 * Releases the lock previously acquired by @ref lock_target.
 *
 * @param target The target to unlock.
 */
void
unlock_target( const struct stumpless_target *target );

/**
 * @brief Checks whether an unsupported target is open.
 *
 * Always returns 0 (false).
 *
 * @param target The target to check.
 *
 * @return Always returns 0.
 */
COLD_FUNCTION
int
unsupported_target_is_open( const struct stumpless_target *target );

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
