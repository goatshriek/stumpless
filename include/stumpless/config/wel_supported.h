/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2019 Joel E. Anderson
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

#  include <stdarg.h>
#  include <stumpless/entry.h>
#  include <windows.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Gets an insertion string from a Windows Event Log entry.
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
 * Sets the insertion strings of a Windows Even Log entry.
 *
 * Instead of setting each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
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
