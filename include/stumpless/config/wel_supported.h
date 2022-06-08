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
 * @file
 * Functions necessary when using Windows Event Log targets.
 */

#ifndef __STUMPLESS_CONFIG_WEL_SUPPORTED_H
#  define __STUMPLESS_CONFIG_WEL_SUPPORTED_H

/*
 * TODO citation needed
 * According to Microsoft, windows.h should be included first in any sources, as
 * it sets up definitions that need to be first.
 */
#  include <windows.h>

#  include <stdarg.h>
#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Creates the registry entries for default WEL entries.
 *
 * Specifically, the following registry subkey is created, or modified if it
 * already exists:
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Stumpless
 *
 * This key is given the following registry values:
 * Sources: "Stumpless" as an entry, assuming it is a REG_MULTI_SZ.
 *
 * If Sources is not correctly formatted with NULL terminating characters as
 * required by a MULTI_SZ, then this call fails and returns
 * ERROR_INVALID_PARAMETER.
 *
 * A subkey is also created within this key named "Stumpless", with the
 * following values set in it:
 * CategoryCount: 8 (one category is present for each severity in RFC 5424)
 * CategoryMessageFile: Points to the executing stumpless DLL.
 * EventMessageFile: Points to the executing stumpless DLL.
 * TypesSupported: 0x1f (all event types are allowed)
 *
 * Any existing keys are opened and existing values are overwritten.
 *
 * Because the current path to the Stumpless DLL is used during installation,
 * this function should only be used by an installed library. Moving the library
 * afterwards will invalidate the paths and cause problems in the Event Viewer.
 *
 * See https://docs.microsoft.com/en-us/windows/win32/eventlog/event-sources and
 * https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-even/ac5ffa75-d036-4302-b008-ce9e0bcd60e3
 * for more information on the event source registration process this function
 * follows.
 *
 * If the Event Viewer does not have an entry for the application or message or
 * category descriptions are not displayed properly, you may need to restart the
 * Event Viewer for this to take effect. Also, be aware that permissions set on
 * the folder where the DLL resides may have an effect; see
 * https://stackoverflow.com/questions/29029025/no-categories-in-windows-event-log
 * for one such issue.
 *
 * @return ERROR_SUCCESS if the operation was successful, or a Windows error
 * code result if an error was encountered. Note that the error code may not
 * necessarily correspond to a call to GetLastError after this, for example in
 * the case where a registry value was not correctly formed.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_add_default_wel_event_source( void );

/**
 * Gets the category of an entry used with Windows Event Log targets.
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
 * @param entry The entry to get the category from.
 *
 * @return The entry category. In the event of an error, then zero is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
WORD
stumpless_get_wel_category( const struct stumpless_entry *entry );

/**
 * Gets the event id of an entry used with Windows Event Log targets.
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
 * @param entry The entry to get the event id from.
 *
 * @return The entry event id. In the event of an error, then zero is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_get_wel_event_id( const struct stumpless_entry *entry );

/**
 * Gets an insertion param from a Windows Event Log entry.
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
 * @param entry The entry to retrieve the insertion param from.
 *
 * @param index The index of the insertion param to retrieve.
 *
 * @return The specified insertion param. If the provided index is in range
 * but has not yet been assigned a param, then NULL is returned. In the event
 * of an error, then NULL will be returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_get_wel_insertion_param( const struct stumpless_entry *entry,
                                   WORD index );

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
 * @return The specified insertion string. If the provided index is in range
 * but has not yet been assigned, then NULL is returned. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 * The returned string will be a UTF-8 multibyte string.
 *
 * Because insertion strings are stored as wide character strings, they are
 * converted to multibyte for this return value. If you assign an insertion
 * string or param and then call this function, the result may not have the
 * exact same bytes as the original depending on the original value due to
 * changes made during the encoding conversions. If this is a problem, consider
 * using the `_w` variants of functions in this header.
 */
STUMPLESS_PUBLIC_FUNCTION
LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index );

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
 * @return 
 *
 * @return The specified insertion string. If the provided index is in range
 * but has not yet been assigned, then NULL is returned. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 * The returned string will be a wide character string.
 */
STUMPLESS_PUBLIC_FUNCTION
LPCWSTR
stumpless_get_wel_insertion_string_w( const struct stumpless_entry *entry,
                                      WORD index );

/**
 * Gets the type of an entry used with Windows Event Log targets.
 *
 * The type is used by a Windows Event Log target. Entries that are going to
 * be sent to a Windows Event Log target must have the type specified before
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
 * @param entry The entry to get the type from.
 *
 * @return The entry type. In the event of an error, then zero is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
WORD
stumpless_get_wel_type( const struct stumpless_entry *entry );

/**
 * Removes the registry entries for default WEL entries.
 *
 * Specifically, the following registry subkey and all subkeys are deleted:
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Stumpless
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_remove_default_wel_event_source( void );

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
STUMPLESS_PUBLIC_FUNCTION
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
STUMPLESS_PUBLIC_FUNCTION
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
 * Insertion params always take precedence over a insertion string. If an
 * insertion string was set at the same index as a param when it is set, it will
 * effectively be removed and the param value used from then on. If the param
 * value is removed, then the insertion string will be unset, and the previous
 * string will _not_ be restored.
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
 * param will be used during logging. Prior to version v2.1.0, this parameter
 * was not const. If this is NULL, then the insertion string will be cleared
 * at the given index.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_insertion_param( struct stumpless_entry *entry,
                                   WORD index,
                                   const struct stumpless_param *param );

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
 * This function performs a multibyte to wide character conversion in order to
 * support unicode characters. If you have a wide character string already, use
 * stumpless_set_wel_insertion_string_w to avoid this unnecessary conversion.
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
 * @param str The string to use for the insertion string. This must be a
 * NULL-terminated UTF-8 multibyte string.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_insertion_string( struct stumpless_entry *entry,
                                    WORD index,
                                    LPCSTR str );

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
 * This function avoids a multibyte to wide conversion that must be performed by
 * stumpless_set_wel_insertion_string. If you already have a wide character
 * string, use this function as it will be more performant. Otherwise, use the
 * non-wide version as it will perform the conversion for you.
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
 * @param str The string to use for the insertion string. This must be a
 * NULL-terminated wide char string.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_insertion_string_w( struct stumpless_entry *entry,
                                      WORD index,
                                      LPCWSTR str );

/**
 * Sets the insertion strings of a Windows Event Log entry.
 *
 * Instead of setting each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * This function performs multibyte to wide character conversions in order to
 * support unicode characters. If you have wide character strings already, use
 * stumpless_set_wel_insertion_strings_w to avoid these unnecessary conversions.
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
 * NULL-terminated UTF-8 multibyte strings in the same order as they appear in
 * the message.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                     WORD count,
                                     ... );

/**
 * Sets the insertion strings of a Windows Event Log entry.
 *
 * Instead of setting each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * This function avoids multibyte to wide conversions that must be performed by
 * stumpless_set_wel_insertion_strings. If you already have a wide character
 * string, use this function as it will be more performant. Otherwise, use the
 * non-wide version as it will perform the conversion for you.
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
 * NULL-terminated wide character strings in the same order as they appear in
 * the message.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
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
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_wel_type( struct stumpless_entry *entry, WORD type );

/**
 * Sets the insertion strings of a Windows Even Log entry.
 *
 * Instead of setting the each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * This function performs multibyte to wide character conversions in order to
 * support unicode characters. If you have wide character strings already, use
 * vstumpless_set_wel_insertion_strings_w to avoid these unnecessary
 * conversions.
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
 * NULL-terminated UTF-8 multibyte strings in the same order as they appear in
 * the message. This list must be started via \c va_start before being used,
 * and \c va_end should be called afterwards, as this function does not call
 * them.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
vstumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                      WORD count,
                                      va_list insertions );

/**
 * Sets the insertion strings of a Windows Even Log entry.
 *
 * Instead of setting the each insertion string separately via
 * \c stumpless_set_wel_insertion_string this function can set the insertion
 * strings all at the same time.
 *
 * This function avoids multibyte to wide conversions that must be performed by
 * vstumpless_set_wel_insertion_strings. If you already have a wide character
 * string, use this function as it will be more performant. Otherwise, use the
 * non-wide version as it will perform the conversion for you.
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
 * NULL-terminated wide character strings in the same order as they appear in
 * the message. This list must be started via \c va_start before being used,
 * and \c va_end should be called afterwards, as this function does not call
 * them.
 *
 * @return The modified entry if no error is encountered. In the event of an
 * error, then NULL will be returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
vstumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
                                        WORD count,
                                        va_list insertions );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_CONFIG_WEL_SUPPORTED_H */
