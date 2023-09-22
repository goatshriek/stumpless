/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_JOURNALD_H
#  define __STUMPLESS_PRIVATE_TARGET_JOURNALD_H

#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>

/**
 * Gets a journald-compliant field name from a given UTF-8 string.
 *
 * **Thread Safety: MT-Safe race:raw**
 * This function is thread safe, of course assuming that the raw name is not
 * changed by another thread during execution.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param flattened A buffer to write the flattened name to.
 *
 * @param raw The raw field name.
 *
 * @param size The number of bytes in the raw name.
 *
 * @return the number of bytes written to the flattened buffer.
 */
size_t
get_journald_field_name( char *flattened, const char *raw, size_t size );

/**
 * Allocates the memory for the fields buffer.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as it operates only on the active thread's
 * resources.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * the memory allocation function to allocate memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @since release v2.1.0
 *
 * @param field_count The number of fields the buffer must have.
 */
void
init_fields( size_t field_count );

/**
 * Allocates the memory for the buffer to hold the fixed fields.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as it operates only on the active thread's
 * resources.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * the memory allocation function to allocate memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @since release v2.1.0
 */
void
init_fixed_fields( void );

/**
 * Destroys all thread-specific resources created to support journald.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as it operates only on the active thread's
 * resources.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * the memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 *
 * @since release v2.1.0
 */
void
journald_free_thread( void );

/**
 * Loads the facility field according to an entry's facility.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the facility from.
 */
void
load_facility( const struct stumpless_entry *entry );

/**
 * Loads the identifier field according to an entry's app name.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the identifier from.
 */
void
load_identifier( const struct stumpless_entry *entry );

/**
 * Loads the message field according to an entry.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the message from.
 *
 * @return A pointer to the buffer holding the message, or NULL if an error
 * was encountered.
 */
char *
load_message( const struct stumpless_entry *entry );

/**
 * Loads the msgid field according to an entry's msgid.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the msgid from.
 */
void
load_msgid( const struct stumpless_entry *entry );

/**
 * Loads the pid field with the current pid.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not signal safe due to the use of a thread-local buffer.
 *
 * **Async Cancel Safety: AC-Safe**
 * Logging to journald targets is async cancellation safe.
 *
 * @since release v2.1.0
 *
 * @return The size of the loaded pid, including the field prefix.
 */
size_t
load_pid( void );

/**
 * Loads the priority field according to an entry's severity.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the priority from.
 */
void
load_priority( const struct stumpless_entry *entry );

/**
 * Loads the structured data fields according to those in the entry.
 *
 * **Thread Safety: MT-Safe race:entry**
 * This function is thread safe, asssuming that the entry is already locked
 * by the caller. Elements and params within the entry are locked/unlocked
 * as needed.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to journald targets is not signal safe due to the use of
 * non-reentrant locks.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to journald targets is not async cancellation safe as it uses locks
 * that may not be released if a thread is cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to load the fields from.
 *
 * @return The total number of fields that will be logged with this entry,
 * including the structured data fields, or 0 if an error was encountered. Note
 * that a successful call will always be at least 6 as this number includes the
 * fixed fields.
 */
size_t
load_sd_fields( const struct stumpless_entry *entry );

/**
 * Loads the timestamp field with the current field.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not signal safe due to the use of a thread-local buffer.
 *
 * **Async Cancel Safety: AC-Safe**
 * Logging to journald targets is async cancellation safe.
 *
 * @since release v2.1.0
 *
 * @return The size of the loaded timestamp, including the field prefix.
 */
size_t
load_timestamp( void );

/**
 * Sends the given entry to the given target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Logging to journald targets is not signal safe due to the use of a
 * thread-local buffer.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Logging to journald targets is not async cancellation safe as it relies on
 * sd_journal_sendv which is not documented as such.
 *
 * @since release v2.1.0
 *
 * @param target Where to send the entry.
 *
 * @param entry The message to log.
 *
 * @return The result of sd_journald_sendv, or -1 if an error is encountered
 * before it can be called.
 */
int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry );

/**
 * Sets the base of each iovec in the fixed fields to the correct member of
 * the fixed_fields structure.
 *
 * No NULL checks are performed on either buffer.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not signal safe due as it operates on a thread-local buffer.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not async cancellation safe as it may leave the buffers in
 * an inconsistent state.
 *
 * @since release v2.1.0
 */
void
set_field_bases( void );

#endif /* __STUMPLESS_PRIVATE_TARGET_JOURNALD_H */
