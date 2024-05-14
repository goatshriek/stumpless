/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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
 * We always include windows.h first, as it sets up definitions that often cause
 * problems if they aren't first.
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
 * Creates the registry entries for displaying default entries in the Windows
 * Event Log.
 *
 * Specifically, the following registry subkey is created, or modified if it
 * already exists:
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog\\Stumpless
 *
 * The "Sources" subkey of this entry has "Stumpless" added to it, assuming it
 * is a \c REG_MULTI_SZ type if it already exists.
 *
 * If an existing Sources key is already present and is not correctly formatted
 * with NULL terminating characters as required by a MULTI_SZ, then this call
 * fails and returns ERROR_INVALID_PARAMETER.
 *
 * A subkey is also created within this key named "Stumpless", with the
 * following values set in it:
 *  - CategoryCount: 8 (one category is present for each severity in RFC 5424)
 *  - CategoryMessageFile: Points to the image containing stumpless.
 *  - EventMessageFile: Points to the image containing stumpless.
 *  - TypesSupported: 0x1f (all event types are allowed).
 *
 * This call is semantically equivalent to stumpless_add_wel_event_source_w(
 * L"Stumpless", L"Stumpless", 8, L"stumpless.dll", L"stumpless.dll", NULL,
 * EVENTLOG_AUDIT_FAILURE | EVENTLOG_AUDIT_SUCCESS | EVENTLOG_ERROR_TYPE |
 * EVENTLOG_INFORMATION_TYPE | EVENTLOG_WARNING_TYPE) where
 * L"stumpless.dll" is the full path to the current stumpless module loaded.
 * Note that this may be a DLL or EXE, depending on how the library was compiled
 * in the currently running process.
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
 * @since release v2.1.0.
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
 * Creates or updates the registry entries for displaying log entries in the
 * Windows Event Log for a new event source. Any existing keys are opened and
 * existing values are overwritten.
 *
 * For Microsoft documentation on each of the parameters listed below, see
 * https://docs.microsoft.com/en-us/windows/win32/eventlog/event-sources and
 * https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-even/ac5ffa75-d036-4302-b008-ce9e0bcd60e3
 * which describe the semantics these registry values.
 *
 * If the Event Viewer does not have an entry for the application or message or
 * category descriptions are not displayed properly, you may need to restart the
 * Event Viewer for this to take effect. Also, be aware that permissions set on
 * the folder where the DLL resides may have an effect; see
 * https://stackoverflow.com/questions/29029025/no-categories-in-windows-event-log
 * for one such issue.
 *
 * **Thread Safety: MT-Safe race:subkey_name race:source_name race:category_file
 * race:event_file race:parameter:file**
 * This function is thread safe, of course assuming that the string parameters
 * are not changed during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors, as well as memory management
 * functions to create wide strings for unicode support.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors, as
 * well as memory management functions.
 *
 * @since release v2.1.0.
 *
 * @param subkey_name The name of the subkey that the source should be added to,
 * as a UTF-8 NULL terminated string. This subkey will be created under
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog. This name
 * may contain backslashes to nest the key under other subkeys.
 *
 * @param source_name The name of the event source, as a UTF-8 NULL terminated
 * string. This will be added to the "Sources" value of the subkey, and created
 * as a subkey under it as well. An error is raised if this is NULL. If the
 * value "Sources" already exists and is not a properly formatted MULTI_SZ
 * value, then this function fails and returns ERROR_INVALID_PARAMETER.
 *
 * @param category_count The number of categories present in the message file.
 * This is used for the CategoryCount registry value.
 *
 * @param category_file A path to the resource file containing the categories
 * used for this source, as a UTF-8 NULL terminated string. If NULL, then the
 * CategoryMessageFile registry value will not be created.
 *
 * @param event_file A path to the resource file containing the messages used
 * for this source, as a UTF-8 NULL terminated string. If NULL, then the
 * EventMessageFile registry value will not be created.
 *
 * @param param_file A path to the resource file containing the messages
 * used as parameters for this source, as a UTF-8 NULL terminated string. If
 * NULL, then the ParameterMessageFile registry value will not be created.
 *
 * @param types_supported A set of flags designating the event types that are
 * supported by this source. This is used for the TypesSupported registry value.
 *
 * @return ERROR_SUCCESS if the operation was successful, or a Windows error
 * code result if an error was encountered. Note that the error code may not
 * necessarily correspond to a call to GetLastError after this, for example in
 * the case where a registry value was not correctly formed.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_add_wel_event_source( LPCSTR subkey_name,
                                LPCSTR source_name,
                                DWORD category_count,
                                LPCSTR category_file,
                                LPCSTR event_file,
                                LPCSTR param_file,
                                DWORD types_supported );

/**
 * Creates or updates the registry entries for displaying log entries in the
 * Windows Event Log for a new event source. Any existing keys are opened and
 * existing values are overwritten.
 *
 * For Microsoft documentation on each of the parameters listed below, see
 * https://docs.microsoft.com/en-us/windows/win32/eventlog/event-sources and
 * https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-even/ac5ffa75-d036-4302-b008-ce9e0bcd60e3
 * which describe the semantics these registry values.
 *
 * If the Event Viewer does not have an entry for the application or message or
 * category descriptions are not displayed properly, you may need to restart the
 * Event Viewer for this to take effect. Also, be aware that permissions set on
 * the folder where the DLL resides may have an effect; see
 * https://stackoverflow.com/questions/29029025/no-categories-in-windows-event-log
 * for one such issue.
 *
 * **Thread Safety: MT-Safe race:subkey_name race:source_name race:category_file
 * race:event_file race:parameter:file**
 * This function is thread safe, of course assuming that the string parameters
 * are not changed during execution.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
 *
 * @since release v2.1.0.
 *
 * @param subkey_name The name of the subkey that the source should be added to,
 * as a wide char NULL terminated string. This subkey will be created under
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog. This name
 * may contain backslashes to nest the key under other subkeys.
 *
 * @param source_name The name of the event source, as a wide char NULL
 * terminated string. This will be added to the "Sources" value of the subkey,
 * and created as a subkey under it as well. An error is raised if this is NULL.
 * If the value "Sources" already exists and is not a properly formatted
 * MULTI_SZ value, then this function fails and returns ERROR_INVALID_PARAMETER.
 *
 * @param category_count The number of categories present in the message file.
 * This is used for the CategoryCount registry value.
 *
 * @param category_file A path to the resource file containing the categories
 * used for this source, as a wide char NULL terminated string. If NULL, then
 * the CategoryMessageFile registry value will not be created.
 *
 * @param event_file A path to the resource file containing the messages used
 * for this source, as a wide char NULL terminated string. If NULL, then the
 * EventMessageFile registry value will not be created.
 *
 * @param param_file A path to the resource file containing the messages
 * used as parameters for this source, as a wide char NULL terminated string. If
 * NULL, then the ParameterMessageFile registry value will not be created.
 *
 * @param types_supported A set of flags designating the event types that are
 * supported by this source. This is used for the TypesSupported registry value.
 *
 * @return ERROR_SUCCESS if the operation was successful, or a Windows error
 * code result if an error was encountered. Note that the error code may not
 * necessarily correspond to a call to GetLastError after this, for example in
 * the case where a registry value was not correctly formed.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_add_wel_event_source_w( LPCWSTR subkey_name,
                                  LPCWSTR source_name,
                                  DWORD category_count,
                                  LPCWSTR category_file,
                                  LPCWSTR event_file,
                                  LPCWSTR param_file,
                                  DWORD types_supported );

/**
 * Gets the category of an entry used with Windows Event Log targets.
 *
 * The category is used by a Windows Event Log target. Entries that are going to
 * be sent to a Windows Event Log target must have the category specified before
 * they are sent.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry and its WEL data while it is being modified.
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
 * entry and its WEL data while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0.
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
 * @since release v2.1.0.
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
 * @since release v2.1.0.
 *
 * @param entry The entry to retrieve the insertion string from.
 *
 * @param index The index of the insertion string to retrieve.
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
 * entry and its WEL data while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0.
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
 * Removes the registry entries for the event source for default WEL entries.
 *
 * Specifically, the following registry subkey and all subkeys are deleted:
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog\\Stumpless
 *
 * This call is semantically equivalent to
 * stumpless_remove_wel_event_source_w( L"Stumpless", L"Stumpless" ).
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
 * @since release v2.1.0.
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_remove_default_wel_event_source( void );

/**
 * Removes the registry entries for an event source for the Windows Event Log.
 *
 * **Thread Safety: MT-Safe race:subkey_name race:source_name**
 * This function is thread safe, of course assuming that the string parameters
 * are not changed during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors, as well as memory management
 * functions to create wide strings for unicode support.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors, as
 * well as memory management functions.
 *
 * @since release v2.1.0.
 *
 * @param subkey_name The name of the subkey that the source is installed in,
 * as a UTF-8 NULL terminated string. This subkey will be looked for under
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog. This name
 * may contain backslashes to nest the key under other subkeys.
 *
 * @param source_name The name of the event source, as a UTF-8 NULL terminated
 * string. This will be removed from the "Sources" value of the subkey, and then
 * a the subkey of the same name under the provided subkey is deleted.
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_remove_wel_event_source( LPCSTR subkey_name,
                                   LPCSTR source_name );

/**
 * Removes the registry entries for an event source for the Windows Event Log.
 *
 * **Thread Safety: MT-Safe race:subkey_name race:source_name**
 * This function is thread safe, of course assuming that the string parameters
 * are not changed during execution.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
 *
 * @since release v2.1.0.
 *
 * @param subkey_name The name of the subkey that the source is installed in,
 * as a wide char NULL terminated string. This subkey will be looked for under
 * HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\EventLog. This name
 * may contain backslashes to nest the key under other subkeys.
 *
 * @param source_name The name of the event source, as a wide char NULL
 * terminated string. This will be removed from the "Sources" value of the
 * subkey, and then a the subkey of the same name under the provided subkey is
 * deleted.
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
STUMPLESS_PUBLIC_FUNCTION
DWORD
stumpless_remove_wel_event_source_w( LPCWSTR subkey_name,
                                     LPCWSTR source_name );

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
 * @since release v2.1.0.
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
 * @since release v2.1.0.
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
