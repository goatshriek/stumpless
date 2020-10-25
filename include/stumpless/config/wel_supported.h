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

/**
 * @file
 * Functions necessary when using Windows Event Log targets.
 */

#ifndef __STUMPLESS_CONFIG_WEL_SUPPORTED_H
#  define __STUMPLESS_CONFIG_WEL_SUPPORTED_H

/*
 * According to Microsoft, windows.h should be included first in any sources, as
 * it sets up definitions that need to be first.
 */
#  include <windows.h>

#  include <stdarg.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Gets an insertion string from a Windows Event Log entry. The character buffer
 * returned must be freed by the caller when it is no longer needed to avoid
 * memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the string and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * entry's WEL data with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to retrieve the insertion string from.
 *
 * @param index The index of the insertion string to retrieve.
 *
 * @return The specified insertion string if no error is encountered. In the
 * event of an error, then NULL will be returned and an error code is set
 * appropriately.
 */
LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index );

/**
 * Sets the category of an entry for use with a Windows Event Log target.
 *
 * The category is used by a Windows Event Log target. Entries that are going to
 * be sent to a Windows Event Log target must have the category specified before
 * they are sent.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry's WEL data while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param category The category to assign. This should be a category defined
 * in a header generated using the Windows Message Compiler.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set
 * appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_category( struct stumpless_entry *entry, WORD category );

/**
 * Sets the event id of an entry for use with a Windows Event Log target.
 *
 * The event id is used by a Windows Event Log target. Entries that are going to
 * be sent to a Windows Event Log target must have the event id specified before
 * they are sent.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry's WEL data while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param event_id The event id to assign. This should be a event id defined
 * in a header generated using the Windows Message Compiler.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_event_id( struct stumpless_entry *entry, DWORD event_id );

/**
 * Sets a param to use for string insertion in a Windows Event Log entry.
 *
 * Windows Events may include insertion strings that are replaced with a
 * specific value provided when logged. This function maps a specific insertion
 * string to a param. The value of the param will then be substituted for that
 * insertion string when an event is logged. If the windows event does not have
 * an insertion string correlating to the given index, it will simply be
 * ignored.
 *
 * Note that insertion strings use the value of the param at log time. If the
 * value changes between log entries, it will reflect these changes in the log
 * itself as well. This also means that you should not destroy a param unless
 * you are sure that no entries exist that are using it.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry's WEL data with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param index The index of the insertion string to use the param for. Valid
 * values are greater than or equal to 0, with 0 being the first string in a
 * message.
 *
 * @param param The param to use for the insertion strings. The value of the
 * param will be used during logging.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_insertion_param( struct stumpless_entry *entry,
                                   WORD index,
                                   struct stumpless_param *param );

/**
 * Sets a string to use for string insertion in a Windows Event Log entry.
 *
 * Windows Events may include insertion strings such as %1 or %3 that are
 * replaced with a specific value provided when logged. This function maps a
 * specific insertion string to a given string. The string will then be
 * substituted for that insertion string when an event is logged. If the windows
 * event does not have an insertion string correlating to the given index, it
 * will simply be ignored.
 *
 * Note that the provided string is copied by the library, and therefore will
 * always hold the value that was in str when this function was called, even
 * if the string changes or is destroyed later.
 *
 * **Thread Safety: MT-Safe race:str**
 * This function is thread safe, of course assuming that the str is not changed
 * by any other threads during execution. A mutex is used to coordinate changes
 * to the entry's WEL data with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param index The index of the insertion string to use the param for. Valid
 * values are greater than or equal to 0, with 0 being the first string in a
 * message.
 *
 * @param str The string to use for the insertion string.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_insertion_string( struct stumpless_entry *entry,
                                    WORD index,
                                    LPCSTR str );

/**
 * Sets the insertion strings of a Windows Event Log entry.
 *
 * Instead of setting each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * **Thread Safety: MT-Safe race:...**
 * This function is thread safe, of course assuming that none of the supplied
 * insertion strings are changed by any other threads during execution. A
 * mutex is used to coordinate changes to the entry's WEL data with other
 * accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param count The number of insertion strings that will be provided.
 *
 * @param ... The insertion strings to set on the entry. These must be
 * NULL-terminated strings in the same order as they appear in the message.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                     WORD count,
                                     ... );

/**
 * Sets the type of an entry for use with a Windows Event Log target.
 *
 * The type is used by a Windows Event Log target. Entries that are going to be
 * sent to a Windows Event Log target must have the type specified before
 * they are sent.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry's WEL data while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param type The type to assign. This should be a type defined
 * in a header generated using the Windows Message Compiler.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_wel_type( struct stumpless_entry *entry, WORD type );

/**
 * Sets the insertion strings of a Windows Even Log entry.
 *
 * Instead of setting the each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * **Thread Safety: MT-Safe race:...**
 * This function is thread safe, of course assuming that none of the supplied
 * insertion strings are changed by any other threads during execution. A
 * mutex is used to coordinate changes to the entry's WEL data with other
 * accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param entry The entry to modify.
 *
 * @param count The number of insertion strings that will be provided.
 *
 * @param insertions The insertion strings to set on the entry. These must be
 * NULL-terminated strings in the same order as they appear in the message. This
 * list must be started via \c va_start before being used, and \c va_end should
 * be called afterwards, as this function does not call them.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
struct stumpless_entry *
vstumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                      WORD count,
                                      va_list insertions );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_CONFIG_WEL_SUPPORTED_H */
