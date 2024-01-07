/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2023 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_ENTRY_H
#define __STUMPLESS_PRIVATE_ENTRY_H

#include <stdbool.h>
#include <stddef.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/facility.h>
#include <stumpless/severity.h>
#include "private/strbuilder.h"

/**
 * Frees entry cache
 *stumpless_entry
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources(entry cache)
 * that other threads can use.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to destroying
 * resources(entry cache) that might be used within a function.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to leaving memory in an undefined state.
 *
 */
void
entry_free_all( void );

/**
 * Gets the priority value from facility and severity parameters.
 * 
 * Priority value is calculated by left shifting the facility value by 3 
 * and adding it to the severity value which is according to the 
 * RFC 5424 Section 6.2.1. The shift operation is done prior to get_prival()
 * function with macros in "facility.h"
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe **
 * This function must be safe to call from signal handlers
 *
 * **Async Cancel Safety: AC-Safe**
 * This function must be safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param facility Facility value. This should be a \c STUMPLESS_FACILITY value.
 * 
 * @param severity Severity value. This should be a \c STUMPLESS_SEVERITY value
 *
 * @return Priority value
 */
int
get_prival( enum stumpless_facility facility,
            enum stumpless_severity severity );

/**
 * Locks the mutex within the entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe **
 * This function is not safe to call from signal handlers due to the use of
 * mutexes that are not guarenteed to be async signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of lock that could be left in undefined state. 
 *
 * @param entry The entry to be locked.
 *
 */
void
lock_entry( const struct stumpless_entry *entry );

/**
 * Adds the element to the entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization 
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * memory functions.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory functions that could leave the 
 * memory in undefined state.
 *
 * @param entry The entry to add the new element.
 *
 * @param element The new element to add to entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered NULL is returned.
 */
struct stumpless_entry *
locked_add_element( struct stumpless_entry *entry,
                    struct stumpless_element *element );

/**
 * Returns the element located at index within the entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization 
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to use of
 * thread global structrues.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously 
 * canceled due to use of thread-global structure that may left in a
 * undefined state when cancelled.
 *
 * @param entry The entry to get the element from.
 *
 * @param index The index of element within the entry.
 *
 * @return The element if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_element *
locked_get_element_by_index( const struct stumpless_entry *entry,
                             size_t index );

struct stumpless_element *
locked_get_element_by_name( const struct stumpless_entry *entry,
                            const char *name );

/**
 * Creates a new entry with the given parameters.
 *
 * @since release v2.1.0.
 */
struct stumpless_entry *
new_entry( enum stumpless_facility facility,
           enum stumpless_severity severity,
           const char *app_name,
           const char *msgid,
           char *message,
           size_t message_length );

struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder );

struct strbuilder *
strbuilder_append_msgid( struct strbuilder *builder,
                         const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_message( struct strbuilder *builder,
                           const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_procid( struct strbuilder *builder );

/**
 * Adds the structured data of an entry to the given strbuilder, in the format
 * specified in RFC 5424.
 *
 * Assumes that the entry has already been locked.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it accesses the entry's element list
 * without any coordination.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * strbuilder functions which may allocate memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param entry The entry to extract the structured data from.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_structured_data( struct strbuilder *builder,
                                   const struct stumpless_entry *entry );

void
unchecked_destroy_entry( const struct stumpless_entry *entry );

bool
unchecked_entry_has_element( const struct stumpless_entry *entry,
                             const char *name );

/**
 * Loads an entry with the given parameters.
 *
 * **Thread Safety: MT-Safe race:app_name race:msgid race:message**
 * This function is thread safe, of course assuming that the string arguments
 * are not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the possible
 * use of memory management functions to create parts of the new entry, as well
 * as the use of a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions and a mutex
 * initialization routine.
 *
 * @since release v2.2.0
 *
 * @param entry The struct to load.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The app name length is restricted
 * to be 48 characters or less.
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The string must be in the
 * ASCII printable range 33 <= character <= 126 as specified in RFC5424.
 *
 * @param message The message in the entry. This string will be owned by the
 * entry if (and only if) this call is successful.
 *
 * @param message_length The length of the message in bytes, without the NULL
 * terminator.
 *
 * @return The loaded entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
unchecked_load_entry( struct stumpless_entry *entry,
                      enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      char *message,
                      size_t message_length );

/**
 * Unloads the provided entry, without performing a NULL check.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to unload. Must not be NULL.
 */
void
unchecked_unload_entry( const struct stumpless_entry *entry );

/**
 * Note (to delete before merge) : i'm concern this comment is not 100% accurate,
 * i have some difficulties to understand the config_unlock_mutex macro
 * if it does something or not
 * 
 * Unlocks the mutex of a given entry.
 * 
 * This function is used internally to ensure that the mutex of an entry
 * is properly unlocked after operations that required synchronization are
 * completed. It uses the config_unlock_mutex macro to perform the actual
 * unlocking.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it directly manipulates the mutex
 * of the entry. The caller must ensure that this function is not called
 * concurrently with other functions that might be modifying the same entry.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers as it
 * involves lock manipulation which is not async-signal-safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed if a cancellation
 * request is received during execution.
 * 
 * @since release v2.0.0
 * 
 * @param entry The entry whose mutex is to be unlocked. The entry must not
 *              be NULL, and it must have a valid mutex initialized.
 */
void
unlock_entry( const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_ENTRY_H */