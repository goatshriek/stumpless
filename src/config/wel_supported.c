// SPDX-License-Identifier: Apache-2.0

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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <ktmw32.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/config/wel_supported.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include <wchar.h>
#include "private/config/have_windows.h"
#include "private/config/locale/wrapper.h"
#include "private/config/wel_supported.h"
#include "private/config/wrapper/wel.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/config/wrapper/wstring.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/param.h"
#include "private/severity.h"
#include "private/validate.h"

/* static definitions */

/** The base subkey used for event sources, including a trailing backslash. */
static LPCWSTR base_source_subkey = L"SYSTEM\\CurrentControlSet\\Services\\" \
                                      L"EventLog";

/** The size of the base subkey in bytes, including the NULL terminator. */
static DWORD base_source_subkey_size = 86;

/** The full base subkey used for the default source installation. */
static LPCWSTR default_source_subkey = L"SYSTEM\\CurrentControlSet\\" \
                                         L"Services\\EventLog\\Stumpless";

/**
 * Converts a size_t to a DWORD, returning the maximum value if the size_t is
 * higher than the DWORD can hold.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param val The size_t to convert.
 *
 * @return The provided val as a DWORD.
 */
DWORD
cap_size_t_to_dword( size_t val ){
  if( val > MAXDWORD ) {
    return MAXDWORD;
  } else {
    return ( DWORD ) val;
  }
}

/**
 * Returns a Windows error code for the current Stumpless error. This may not
 * be equivalent to the result of GetLastError, for example if a memory
 * allocation failure occurred.
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
 * @return A Windows error code reflecting the last error, or ERROR_SUCCESS
 * if there is not one.
 */
static
DWORD
get_windows_error_code( void ) {
  const struct stumpless_error *error;
  enum stumpless_error_id id;

  error = stumpless_get_error(  );
  if( !error ) {
    return ERROR_SUCCESS;
  }

  id = stumpless_get_error_id( error );
  if( id == STUMPLESS_MEMORY_ALLOCATION_FAILURE ) {
    return ERROR_NOT_ENOUGH_MEMORY;
  } else {
    return GetLastError(  );
  }
}

/**
 * Creates a copy of a NULL terminated wide character string.
 *
 * **Thread Safety: MT-Safe race:str**
 * This function is thread safe, of course assuming that str is not changed
 * during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the copy of string.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param str A wide character string to copy.
 *
 * @return A copy of the given wide character string, or NULL if an error is
 * encountered.
 */
static
LPWSTR
copy_lpcwstr( LPCWSTR str ) {
  size_t str_len;
  size_t str_size;
  LPWSTR str_copy;

  str_len = wcslen( str );
  str_size = ( str_len + 1 ) * sizeof( WCHAR );
  str_copy = alloc_mem( str_size );
  if( !str_copy ) {
    return NULL;
  }

  memcpy( str_copy, str, str_size );
  return str_copy;
}

/**
 * Joins two provided registry keys together with a backslash character in a
 * new string. The result must be freed when it is no longer needed.
 *
 * **Thread Safety: MT-Safe race:base_key race:subkey**
 * This function is thread safe, of course assuming that base_key and subkey
 * are not changed during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the joined key.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param base_key The base key.
 *
 * @param base_key_size The size of the base key in bytes, including the
 * terminating NULL character.
 *
 * @param subkey The subkey of the base key.
 *
 * @param subkey_size The size of the subkey in bytes, including the
 * terminating NULL character.
 *
 * @return A new string with the joined registry key, or NULL if memory could
 * not be allocated for it.
 */
static
LPWSTR
join_keys( LPCWSTR base_key,
           size_t base_key_size,
           LPCWSTR subkey,
           size_t subkey_size ) {
  char *key;

  key = alloc_mem( base_key_size + subkey_size );
  if( !key ) {
      return NULL;
  }
  memcpy( key, base_key, base_key_size - sizeof( WCHAR ) );
  *( ( LPWSTR ) ( key + base_key_size - sizeof( WCHAR ) ) ) = L'\\';
  memcpy( key + base_key_size, subkey, subkey_size );

  return ( LPWSTR ) key;
}

/**
 * Creates the values for an event source in the provided subkey.
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
 * @param subkey A handle to the subkey to populate.
 *
 * @param category_count The number of categories included in the category file.
 *
 * @param category_file A path to the resource file containing the categories
 * used for this source, as a wide string. If NULL, then the CategoryMessageFile
 * registry value will not be created.
 *
 * @param category_file_size The size of category_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param event_file A path to the resource file containing the messages used
 * for this source, as a wide string. If NULL, then the EventMessageFile
 * registry value will not be created.
 *
 * @param event_file_size The size of event_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param parameter_file A path to the resource file containing the messages
 * used as parameters for this source, as a wide string. If NULL, then the
 * ParameterMessageFile registry value will not be created.
 *
 * @param parameter_file_size The size of parameter_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param types_supported The flags used for the TypesSupported value.
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
static
DWORD
populate_event_source_subkey( HKEY subkey,
                              DWORD category_count,
                              LPCWSTR category_file,
                              DWORD category_file_size,
                              LPCWSTR event_file,
                              DWORD event_file_size,
                              LPCWSTR parameter_file,
                              DWORD parameter_file_size,
                              DWORD types_supported ) {
  DWORD result;

  result = RegSetValueExW( subkey,
                           L"CategoryCount",
                           0,
                           REG_DWORD,
                           ( const BYTE * ) &category_count,
                           sizeof( category_count ) );
  if( result != ERROR_SUCCESS ) {
    raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    return result;
  }

  if( category_file ) {
    result = RegSetValueExW( subkey,
                             L"CategoryMessageFile",
                             0,
                             REG_EXPAND_SZ,
                             ( const BYTE * ) category_file,
                             category_file_size );
    if( result != ERROR_SUCCESS ) {
      raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      return result;
    }
  }

  if( event_file ) {
    result = RegSetValueExW( subkey,
                             L"EventMessageFile",
                             0,
                             REG_EXPAND_SZ,
                             ( const BYTE * ) event_file,
                             event_file_size );
    if( result != ERROR_SUCCESS ) {
      raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      return result;
    }
  }

  if( parameter_file ) {
    result = RegSetValueExW( subkey,
                             L"ParameterMessageFile",
                             0,
                             REG_EXPAND_SZ,
                             ( const BYTE * ) parameter_file,
                             parameter_file_size );
    if( result != ERROR_SUCCESS ) {
      raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      return result;
    }
  }

  result = RegSetValueExW( subkey,
                           L"TypesSupported",
                           0,
                           REG_DWORD,
                           ( const BYTE * ) &types_supported,
                           sizeof( types_supported ) );
  if( result != ERROR_SUCCESS ) {
    raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    return result;
  }

  return ERROR_SUCCESS;
}

/**
 * Creates the given event source registry subkey, under the assumption that
 * it does not currently exist. The source will be put in the registry under
 * SYSTEM\CurrentControlSet\Services\EventLog.
 *
 * The key is created an populated as part of a single transaction, and
 * therefore will either succeed in all of this or fail entirely. That is, a
 * partially populated subkey will not be created.
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
 * @param subkey_name The complete name of the registry subkey that the source
 * should be created under, as a NULL terminated wide character string.
 *
 * @param source_name The event source to create as a NULL terminated wide
 * character string.
 *
 * @param source_name_size The size of source_name in bytes, including the
 * terminating NULL character. This must not be greater than 512, which is the
 * maximum registry key name size including a NULL terminator. Must be greater
 * than 2.
 *
 * @param category_count The number of categories present in the message file.
 * This is used for the CategoryCount registry value.
 *
 * @param category_file A path to the resource file containing the categories
 * used for this source, as a wide string. If NULL, then the CategoryMessageFile
 * registry value will not be created.
 *
 * @param category_file_size The size of category_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param event_file A path to the resource file containing the messages used
 * for this source, as a wide string. If NULL, then the EventMessageFile
 * registry value will not be created.
 *
 * @param event_file_size The size of event_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param parameter_file A path to the resource file containing the messages
 * used as parameters for this source, as a wide string. If NULL, then the
 * ParameterMessageFile registry value will not be created.
 *
 * @param parameter_file_size The size of parameter_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param types_supported A set of flags designating the event types that are
 * supported by this source. This is used for the TypesSupported registry value.
 *
 * @return ERROR_SUCCESS if the operation was successful, or the result of
 * GetLastError if an error was encountered.
 */
static
DWORD
create_event_source_subkey( LPCWSTR subkey_name,
                            LPCWSTR source_name,
                            DWORD source_name_size,
                            DWORD category_count,
                            LPCWSTR category_file,
                            DWORD category_file_size,
                            LPCWSTR event_file,
                            DWORD event_file_size,
                            LPCWSTR parameter_file,
                            DWORD parameter_file_size,
                            DWORD types_supported ) {
  BYTE *sources_value;
  HANDLE transaction;
  LPWSTR transaction_desc = L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W;
  DWORD result  = ERROR_SUCCESS;
  LSTATUS reg_result;
  HKEY subkey_handle;
  HKEY source_key_handle;
  BOOL bool_result;

  sources_value = alloc_mem( source_name_size + sizeof( WCHAR ) );
  if( !sources_value ) {
    result = ERROR_NOT_ENOUGH_MEMORY;
    return result;
  }
  memcpy( sources_value, source_name, source_name_size );
  *( ( LPWSTR ) ( sources_value + source_name_size ) ) = L'\0';

  transaction = CreateTransaction( NULL,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   transaction_desc );
  if( transaction == INVALID_HANDLE_VALUE ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
    goto cleanup_sources;
  }

  reg_result = RegCreateKeyTransactedW( HKEY_LOCAL_MACHINE,
                                        subkey_name,
                                        0,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_CREATE_SUB_KEY | KEY_SET_VALUE,
                                        NULL,
                                        &subkey_handle,
                                        NULL,
                                        transaction,
                                        NULL );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    goto cleanup_transaction;
  }

  reg_result = RegSetValueExW( subkey_handle,
                               L"Sources",
                               0,
                               REG_MULTI_SZ,
                               sources_value,
                               source_name_size + sizeof( WCHAR ) );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    goto cleanup_key;
  }

  reg_result = RegCreateKeyTransactedW( subkey_handle,
                                        source_name,
                                        0,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_SET_VALUE,
                                        NULL,
                                        &source_key_handle,
                                        NULL,
                                        transaction,
                                        NULL );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    goto cleanup_key;
  }

  result = populate_event_source_subkey( source_key_handle,
                                         category_count,
                                         category_file,
                                         category_file_size,
                                         event_file,
                                         event_file_size,
                                         parameter_file,
                                         parameter_file_size,
                                         types_supported );
  if( result != ERROR_SUCCESS ) {
    goto cleanup_source;
  }

  bool_result = CommitTransaction( transaction );
  if( bool_result == 0 ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
  }

cleanup_source:
  RegCloseKey( source_key_handle );
cleanup_key:
  RegCloseKey( subkey_handle );
cleanup_transaction:
  CloseHandle( transaction );
cleanup_sources:
  free_mem( sources_value );
  return result;
}

/**
 * Gets the values of the Sources subkey from the provided handle.
 *
 * The returned buffer must be freed by the caller when it is no longer needed.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors, as well as the use of memory
 * management functions to create the new buffer.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors as
 * well as memory management functions.
 *
 * @param subkey_handle A handle to the subkey to get the Sources value of.
 *
 * @param value_size A pointer to a DWORD that will hold the size of the value.
 *
 * @param result A pointer to a DWORD which is updated with a failure result in
 * the case of a failure.
 *
 * @return A buffer holding the value of the sources key, or NULL upon failure.
 */
static
LPWSTR
get_sources_value( HKEY subkey_handle, LPDWORD value_size, LPDWORD result ) {
  DWORD value_type;
  LPWSTR sources_value;
  LSTATUS reg_result;

  *value_size = 256;
  sources_value = alloc_mem( *value_size );
  if( !sources_value ) {
    return NULL;
  }

  reg_result = RegGetValueW( subkey_handle,
                             NULL,
                             L"Sources",
                             RRF_RT_REG_MULTI_SZ,
                             &value_type,
                             sources_value,
                             value_size );

  if( reg_result == ERROR_MORE_DATA ) {
    // allocate a new buffer and call again
    free_mem( sources_value );
    sources_value = alloc_mem( *value_size );
    if( !sources_value ) {
      *result = ERROR_NOT_ENOUGH_MEMORY;
      return NULL;
    }

    reg_result = RegGetValueW( subkey_handle,
                               NULL,
                               L"Sources",
                               RRF_RT_REG_MULTI_SZ,
                               &value_type,
                               sources_value,
                               value_size );
  }

  if( reg_result != ERROR_SUCCESS ) {
    free_mem( sources_value );
    *result = reg_result;
    raise_windows_failure( L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE,
                           reg_result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    return NULL;
  }

  if( sources_value[0] != L'\0' &&
      !( sources_value[(*value_size / sizeof( WCHAR) ) - 2] == L'\0' &&
         sources_value[(*value_size / sizeof( WCHAR) ) - 1] == L'\0' ) ) {
    free_mem( sources_value );
    *result = ERROR_INVALID_PARAMETER;
    raise_invalid_encoding( L10N_INVALID_MULTI_SZ_ERROR_MESSAGE );
    return NULL;
  }

  return sources_value;
}

/**
 * Detects if a given string is in a MULTI_SZ registry value.
 *
 * **Thread Safety: MT-Safe race:value race:str**
 * This function is thread safe, of course assuming that value and str are not
 * changed during execution.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param val The MULTI_SZ registry key value.
 *
 * @param str The string to search for in the entry.
 *
 * @return true if the string is present, false otherwise.
 */
static
bool
multi_sz_contains( LPCWSTR value, LPCWSTR str ){
  LPCWSTR current = value;
  size_t str_size;

  str_size = wcslen( str ) + 1;

  while( *current != L'\0' ) {
    if( wcsncmp(current, str, str_size ) == 0 ) {
      return true;
    }

    current += wcslen( current ) + 1;
  }

  return false;
}

/**
 * Sets the insertion string at the given index to the provided wide string,
 * freeing the previous one if it existed.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The lock of the wel data structure is
 * acquired (and later released) during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to expand the insertion string array if needed,
 * and free an existing insertion string. If neither of these cases occurs, then
 * this function can be considered AS-Safe.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the possible use of memory management functions. If both
 * of the cases outlined in the Async Signal Safety section are guaranteed not
 * to happen, then this function may be considered AC-Safe.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The wide string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
swap_wel_insertion_string( struct stumpless_entry *entry,
                           WORD index,
                           LPCWSTR str ) {
  struct wel_data *data;
  struct stumpless_entry *result;

  data = entry->wel_data;
  lock_wel_data( data );

  result = locked_swap_wel_insertion_string( entry, index, str );

  unlock_wel_data( data );

  return result;
}

/**
 * Sets the insertion string at the given index to the provided UTF-8 string.
 *
 * A copy of the string is created in wide character format.
 *
 * If the index is higher than the current max, then the insertion string arrays
 * are expanded to accomodate it.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The lock of the wel data structure must be held
 * during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of
 * non-reentrant locks to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The UTF-8 string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
locked_set_wel_insertion_string( struct stumpless_entry *entry,
                                 WORD index,
                                 LPCSTR str ) {
  LPCWSTR str_copy;

  str_copy = windows_copy_cstring_to_lpwstr( str, NULL );
  if( !str_copy ) {
    return NULL;
  }

  return locked_swap_wel_insertion_string( entry, index, str_copy );
}

/**
 * Sets the insertion string at the given index to the provided UTF-8 string.
 *
 * A copy of the string is created in wide character format.
 *
 * If the index is higher than the current max, then the insertion string arrays
 * are expanded to accomodate it.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The lock of the wel data structure are acquired
 * (and later released) during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of
 * non-reentrant locks to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The UTF-8 string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
set_wel_insertion_string( struct stumpless_entry *entry,
                          WORD index,
                          LPCSTR str ) {
  LPCWSTR str_copy;

  str_copy = windows_copy_cstring_to_lpwstr( str, NULL );
  if( !str_copy ) {
    return NULL;
  }

  return swap_wel_insertion_string( entry, index, str_copy );
}

/**
 * Sets the insertion string at the given index to the provided wide string.
 *
 * A copy of the string is created in wide character format.
 *
 * If the index is higher than the current max, then the insertion string arrays
 * are expanded to accomodate it.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe. The locks of the wel data structure must be
 * held during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The wide string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
locked_set_wel_insertion_string_w( struct stumpless_entry *entry,
                                   WORD index,
                                   LPCWSTR str ) {
  LPCWSTR str_copy;

  str_copy = copy_lpcwstr( str );
  if( !str_copy ) {
    return NULL;
  }

  return locked_swap_wel_insertion_string( entry, index, str_copy );
}

/**
 * Sets the insertion string at the given index to the provided wide string.
 *
 * A copy of the string is created in wide character format.
 *
 * If the index is higher than the current max, then the insertion string arrays
 * are expanded to accomodate it.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The locks of the entry and the wel data
 * structure are acquired (and later released) during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of
 * non-reentrant locks to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The wide string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
set_wel_insertion_string_w( struct stumpless_entry *entry,
                            WORD index,
                            LPCWSTR str ) {
  LPCWSTR str_copy;

  str_copy = copy_lpcwstr( str );
  if( !str_copy ) {
    return NULL;
  }

  return swap_wel_insertion_string( entry, index, str_copy );
}

/**
 * Creates the registry entries to install an event source with the given
 * specifications.
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
 * @param subkey_name The name of the subkey that the source should be added to,
 * as a wide char string. This subkey will be created under
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog.
 *
 * @param subkey_name_size The size of the subkey_name string in bytes,
 * including the terminating NULL character.
 *
 * @param source_name The name of the event source, as a NULL terminated
 * wide char string. This will be added to the "Sources" value of the subkey,
 * and created as a subkey under it as well. An error is raised if this is NULL.
 * If the value "Sources" already exists and is not a properly formatted
 * MULTI_SZ value, then this function fails and returns ERROR_INVALID_PARAMETER.
 *
 * @param source_name_size The size of the source_name string in bytes,
 * including the terminating NULL character.
 *
 * @param category_count The number of categories present in the message file.
 * This is used for the CategoryCount registry value.
 *
 * @param category_file A path to the resource file containing the categories
 * used for this source, as a wide char string. If NULL, then the
 * CategoryMessageFile registry value will not be created.
 *
 * @param category_file_size The size of category_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param event_file A path to the resource file containing the messages used
 * for this source, as a wide char string. If NULL, then the
 * EventMessageFile registry value will not be created.
 *
 * @param event_file_size The size of event_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param parameter_file A path to the resource file containing the messages
 * used as parameters for this source, as a wide char string. If
 * NULL, then the ParameterMessageFile registry value will not be created.
 *
 * @param parameter_file_size The size of parameter_file path string in bytes,
 * including the terminating NULL character.
 *
 * @param types_supported A set of flags designating the event types that are
 * supported by this source. This is used for the TypesSupported registry value.
 *
 * @return ERROR_SUCCESS if the operation was successful, or a Windows error
 * code result if an error was encountered. Note that the error code may not
 * necessarily correspond to a call to GetLastError after this, for example in
 * the case where a registry value was not correctly formed.
 */
static
DWORD
add_event_source( LPCWSTR subkey_name,
                  DWORD subkey_name_size,
                  LPCWSTR source_name,
                  DWORD source_name_size,
                  DWORD category_count,
                  LPCWSTR category_file,
                  DWORD category_file_size,
                  LPCWSTR event_file,
                  DWORD event_file_size,
                  LPCWSTR parameter_file,
                  DWORD parameter_file_size,
                  DWORD types_supported ) {
  LPWSTR complete_subkey;
  HKEY subkey_handle;
  LSTATUS reg_result;
  DWORD result = ERROR_SUCCESS;
  DWORD value_size;
  LPWSTR sources_value;
  BYTE *new_sources_value;
  DWORD new_sources_size;
  HKEY source_subkey_handle;
  HANDLE transaction;
  LPWSTR transaction_desc = L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W;
  BOOL bool_result;

  // build the complete source subkey
  complete_subkey = join_keys( base_source_subkey,
                               base_source_subkey_size,
                               subkey_name,
                               subkey_name_size );
  if( !complete_subkey ) {
      result = ERROR_NOT_ENOUGH_MEMORY;
      goto cleanup;
  }

  // before the modification transaction starts, we open the main key to see if it exists
  reg_result = RegOpenKeyExW( HKEY_LOCAL_MACHINE,
                              complete_subkey,
                              0,
                              KEY_QUERY_VALUE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY,
                              &subkey_handle );
  if( reg_result != ERROR_SUCCESS ) {
    if( reg_result == ERROR_FILE_NOT_FOUND ) {
      // if the key doesn't exist at all, we can simply create it
      return create_event_source_subkey( complete_subkey,
                                         source_name,
                                         source_name_size,
                                         category_count,
                                         category_file,
                                         category_file_size,
                                         event_file,
                                         event_file_size,
                                         parameter_file,
                                         parameter_file_size,
                                         types_supported );
    } else {
      result = reg_result;
      raise_windows_failure( L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      goto cleanup_complete_subkey;
    }
  }

  // if the key already exists, we need to check the sources list to see if the
  // source name already exists
  sources_value = get_sources_value( subkey_handle, &value_size, &result );
  if( !sources_value ) {
    goto cleanup_subkey;
  }

  if( !multi_sz_contains( sources_value, source_name ) ) {
    new_sources_size = value_size + source_name_size;

    new_sources_value = alloc_mem( new_sources_size );
    if( !new_sources_value ) {
      result = ERROR_NOT_ENOUGH_MEMORY;
      goto cleanup_sources;
    }

    memcpy( new_sources_value, source_name, source_name_size );
    memcpy( new_sources_value + source_name_size, sources_value, value_size );

    reg_result = RegSetValueExW( subkey_handle,
                                 L"Sources",
                                 0,
                                 REG_MULTI_SZ,
                                 new_sources_value,
                                 new_sources_size );

    free_mem( new_sources_value ); // candidate for alloca

    if( reg_result != ERROR_SUCCESS ) {
      result = reg_result;
      raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      goto cleanup_sources;
    }
  }

  transaction = CreateTransaction( NULL,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   transaction_desc );
  if( transaction == INVALID_HANDLE_VALUE ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
    return result;
  }

  reg_result = RegCreateKeyTransactedW( subkey_handle,
                                        source_name,
                                        0,
                                        NULL,
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_SET_VALUE,
                                        NULL,
                                        &source_subkey_handle,
                                        NULL,
                                        transaction,
                                        NULL );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    goto cleanup_trans;
  }

  result = populate_event_source_subkey( source_subkey_handle,
                                         category_count,
                                         category_file,
                                         category_file_size,
                                         event_file,
                                         event_file_size,
                                         parameter_file,
                                         parameter_file_size,
                                         types_supported );
  if( result != ERROR_SUCCESS ) {
    goto cleanup_source_subkey;
  }

  bool_result = CommitTransaction( transaction );
  if( bool_result == 0 ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
  }

cleanup_source_subkey:
  RegCloseKey( source_subkey_handle );
cleanup_trans:
  CloseHandle( transaction );
cleanup_sources:
  free_mem( sources_value );
cleanup_subkey:
  RegCloseKey( subkey_handle );
cleanup_complete_subkey:
  free_mem( complete_subkey );
cleanup:
  return result;
}

/* public definitions */

DWORD
stumpless_add_default_wel_event_source( void ) {
  HMODULE this_module;
  // this array does not support long path names (`//?/`) as is
  WCHAR library_path[MAX_PATH];
  DWORD library_path_size;
  DWORD result = ERROR_SUCCESS;
  LPCWSTR source_name = L"Stumpless";
  DWORD source_name_size = 20;
  BOOL bool_result;

  clear_error(  );

  // get the path to this library
  bool_result = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                      GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    ( LPCWSTR ) &stumpless_add_default_wel_event_source,
                                    &this_module ) ;
  if( bool_result == 0 ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
    return result;
  }

  library_path_size = GetModuleFileNameW( this_module, library_path, MAX_PATH );
  if( library_path_size == 0 ) {
    result = GetLastError(  );
    raise_windows_failure( L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_GETLASTERROR_ERROR_CODE_TYPE );
    goto cleanup_module;
  }

  if( library_path_size != MAX_PATH ) {
    library_path_size += 1;
  }
  library_path_size *= sizeof( WCHAR );

  result = add_event_source( source_name,
                             source_name_size,
                             source_name,
                             source_name_size,
                             8,
                             library_path,
                             library_path_size,
                             library_path,
                             library_path_size,
                             NULL,
                             0,
                             EVENTLOG_AUDIT_FAILURE |
                               EVENTLOG_AUDIT_SUCCESS |
                               EVENTLOG_ERROR_TYPE |
                               EVENTLOG_INFORMATION_TYPE |
                               EVENTLOG_WARNING_TYPE );

cleanup_module:
  FreeLibrary( this_module );
  return result;
}

DWORD
stumpless_add_wel_event_source( LPCSTR subkey_name,
                                LPCSTR source_name,
                                DWORD category_count,
                                LPCSTR category_file,
                                LPCSTR event_file,
                                LPCSTR param_file,
                                DWORD types_supported ) {
  DWORD result = ERROR_SUCCESS;
  int subkey_name_length = 0;
  LPCWSTR subkey_name_w;
  int source_name_length = 0;
  LPWSTR source_name_w;
  int category_file_length = 0;
  LPCWSTR category_file_w = NULL;
  int event_file_length = 0;
  LPCWSTR event_file_w = NULL;
  int param_file_length = 0;
  LPCWSTR param_file_w = NULL;

  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( subkey_name );
  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( source_name );

  clear_error(  );

  subkey_name_w = windows_copy_cstring_to_lpwstr( subkey_name,
                                                  &subkey_name_length );
  if( !subkey_name_w ) {
    result = get_windows_error_code(  );
    goto finish;
  }

  source_name_w = windows_copy_cstring_to_lpwstr( source_name,
                                                  &source_name_length );
  if( !source_name_w ) {
    result = get_windows_error_code(  );
    goto cleanup_subkey;
  }

  if( category_file ) {
    category_file_w = windows_copy_cstring_to_lpwstr( category_file,
                                                      &category_file_length );
    if( !category_file_w ) {
      result = get_windows_error_code(  );
      goto cleanup_source;
    }
  }

  if( event_file ) {
    event_file_w = windows_copy_cstring_to_lpwstr( event_file,
                                                   &event_file_length );
    if( !event_file_w ) {
      result = get_windows_error_code(  );
      goto cleanup_category;
    }
  }

  if( param_file ) {
    param_file_w = windows_copy_cstring_to_lpwstr( param_file,
                                                   &param_file_length );
    if( !param_file_w ) {
      result = get_windows_error_code(  );
      goto cleanup_event;
    }
  }

  result = add_event_source( subkey_name_w,
                             subkey_name_length * sizeof( WCHAR ),
                             source_name_w,
                             source_name_length * sizeof( WCHAR ),
                             category_count,
                             category_file_w,
                             category_file_length * sizeof( WCHAR ),
                             event_file_w,
                             event_file_length * sizeof( WCHAR ),
                             param_file_w,
                             param_file_length * sizeof( WCHAR ),
                             types_supported );

  free_mem( param_file_w );
cleanup_event:
  free_mem( event_file_w );
cleanup_category:
  free_mem( category_file_w );
cleanup_source:
  free_mem( source_name_w );
cleanup_subkey:
  free_mem( subkey_name_w );
finish:
  return result;
}

DWORD
stumpless_add_wel_event_source_w( LPCWSTR subkey_name,
                                  LPCWSTR source_name,
                                  DWORD category_count,
                                  LPCWSTR category_file,
                                  LPCWSTR event_file,
                                  LPCWSTR param_file,
                                  DWORD types_supported ) {
  size_t subkey_name_size;
  size_t source_name_size;
  size_t category_file_size = 0;
  size_t event_file_size = 0;
  size_t param_file_size = 0;

  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( subkey_name );
  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( source_name );

  clear_error(  );

  subkey_name_size = ( wcslen( subkey_name ) + 1 ) * sizeof( WCHAR );
  source_name_size = ( wcslen( source_name ) + 1 ) * sizeof( WCHAR );

  if( category_file ) {
    category_file_size = ( wcslen( category_file ) + 1 ) * sizeof( WCHAR );
  }

  if( event_file ) {
    event_file_size = ( wcslen( event_file ) + 1 ) * sizeof( WCHAR );
  }

  if( param_file ) {
    param_file_size = ( wcslen( param_file ) + 1 ) * sizeof( WCHAR );
  }

  return add_event_source( subkey_name,
                           cap_size_t_to_dword( subkey_name_size ),
                           source_name,
                           cap_size_t_to_dword( source_name_size ),
                           category_count,
                           category_file,
                           cap_size_t_to_dword( category_file_size ),
                           event_file,
                           cap_size_t_to_dword( event_file_size ),
                           param_file,
                           cap_size_t_to_dword( param_file_size ),
                           types_supported );
}

WORD
stumpless_get_wel_category( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  WORD category;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );
  clear_error(  );

  data = entry->wel_data;
  lock_entry( entry );
  lock_wel_data( data );

  if( data->category_set ) {
    category = data->category;
    unlock_wel_data( data );
  } else {
    unlock_wel_data( data );
    category = get_category( entry->prival );
  }

  unlock_entry( entry );
  return category;
}

DWORD
stumpless_get_wel_event_id( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  DWORD event_id;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );
  clear_error(  );

  data = entry->wel_data;
  lock_entry( entry );
  lock_wel_data( data );

  if( data->event_id_set ) {
    event_id = data->event_id;
    unlock_wel_data( data );
  } else {
    unlock_wel_data( data );
    event_id = get_event_id( entry->prival );
  }
  
  unlock_entry( entry );
  return event_id;
}

struct stumpless_param *
stumpless_get_wel_insertion_param( const struct stumpless_entry *entry,
                                   WORD index ) {
  const struct wel_data *data;
  struct stumpless_param *param = NULL;

  VALIDATE_ARG_NOT_NULL( entry );
  clear_error(  );

  data = entry->wel_data;
  lock_wel_data( data );

  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = ( struct stumpless_param * ) data->insertion_params[index];

cleanup_and_return:
  unlock_wel_data( data );
  return param;
}

LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index ) {
  struct wel_data *data;
  const struct stumpless_param *param;
  char *str_copy = NULL;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = data->insertion_params[index];
  if( param ) {
    str_copy = alloc_mem( param->value_length + 1 );
    if( !str_copy ) {
      goto cleanup_and_return;
    }
    memcpy( str_copy, param->value, param->value_length );
    str_copy[param->value_length] = '\0';

  } else if( data->insertion_strings[index] ) {
    str_copy = config_copy_wstring_to_cstring( data->insertion_strings[index],
                                               NULL );
  }

cleanup_and_return:
  unlock_wel_data( data );
  return str_copy;
}

LPCWSTR
stumpless_get_wel_insertion_string_w( const struct stumpless_entry *entry,
                                      WORD index ) {
  struct wel_data *data;
  const struct stumpless_param *param;
  LPCWSTR str_copy = NULL;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = data->insertion_params[index];
  if( param ) {
    str_copy = copy_param_value_to_lpwstr( param );

  } else if( data->insertion_strings[index] ) {
    str_copy = copy_lpcwstr( data->insertion_strings[index] );
  }

cleanup_and_return:
  unlock_wel_data( data );
  return str_copy;
}

WORD
stumpless_get_wel_type( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  WORD type;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );
  clear_error(  );

  data = entry->wel_data;
  lock_entry( entry );
  lock_wel_data( data );

  if( data->type_set ) {
    type = data->type;
    unlock_wel_data( data );
  } else {
    unlock_wel_data( data );
    type = get_type( entry->prival );
  }

  unlock_entry( entry );
  return type;
}

DWORD
stumpless_remove_default_wel_event_source( void ) {
  return stumpless_remove_wel_event_source_w( L"Stumpless", L"Stumpless" );
}

DWORD
stumpless_remove_wel_event_source( LPCSTR subkey_name,
                                   LPCSTR source_name ) {
  LPCWSTR subkey_name_w;
  LPCWSTR source_name_w;
  DWORD result = ERROR_SUCCESS;

  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( subkey_name );
  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( source_name );

  clear_error(  );

  subkey_name_w = windows_copy_cstring_to_lpwstr( subkey_name, NULL );
  if( !subkey_name_w ) {
    result = get_windows_error_code(  );
    goto finish;
  }

  source_name_w = windows_copy_cstring_to_lpwstr( source_name, NULL );
  if( !source_name_w ) {
    result = get_windows_error_code(  );
    goto cleanup_subkey;
  }

  result = stumpless_remove_wel_event_source_w( subkey_name_w,
                                                source_name_w );

  free_mem( source_name_w );
cleanup_subkey:
  free_mem( subkey_name_w );
finish:
  return result;
}

DWORD
stumpless_remove_wel_event_source_w( LPCWSTR subkey_name,
                                     LPCWSTR source_name ) {
  size_t subkey_name_size;
  LPCWSTR complete_subkey;
  HKEY subkey_handle;
  size_t source_name_size;
  DWORD result = ERROR_SUCCESS;
  LSTATUS reg_result;
  DWORD value_size;
  LPWSTR sources_value;
  LPWSTR new_sources_value;
  size_t new_sources_size;
  LPCWSTR sources_current;
  LPWSTR current;
  size_t source_len;

  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( subkey_name );
  VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( source_name );

  clear_error(  );

  // build the complete source subkey
  subkey_name_size = ( wcslen( subkey_name ) + 1 ) * sizeof( WCHAR );
  complete_subkey = join_keys( base_source_subkey,
                               base_source_subkey_size,
                               subkey_name,
                               cap_size_t_to_dword( subkey_name_size ) );
  if( !complete_subkey ) {
      result = ERROR_NOT_ENOUGH_MEMORY;
      goto finish;
  }

  reg_result = RegOpenKeyExW( HKEY_LOCAL_MACHINE,
                              complete_subkey,
                              0,
                              KEY_QUERY_VALUE |
                                KEY_SET_VALUE |
                                DELETE |
                                KEY_ENUMERATE_SUB_KEYS,
                              &subkey_handle );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    goto cleanup_complete_subkey;
  }

  sources_value = get_sources_value( subkey_handle, &value_size, &result );
  if( !sources_value ) {
    goto cleanup_subkey_handle;
  }

  // if Sources only contains the specified Source or is empty, simply remove the whole tree
  source_name_size = ( wcslen( source_name ) + 1 ) * sizeof( WCHAR );
  if( sources_value[0] == L'\0' ||
      ( value_size == ( source_name_size + sizeof( WCHAR ) ) &&
        wcscmp( sources_value, source_name ) == 0 ) ) {

    reg_result = RegDeleteTreeW( HKEY_LOCAL_MACHINE, complete_subkey );
    if( reg_result != ERROR_SUCCESS ) {
      result = reg_result;
      raise_windows_failure( L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
    }

    goto cleanup_sources;
  }

  // otherwise, modify the Sources value to remove this one and delete only the
  // given Source
  if( multi_sz_contains( sources_value, source_name ) ) {
    new_sources_size = value_size - source_name_size;

    new_sources_value = alloc_mem( new_sources_size );
    if( !new_sources_value ) {
      result = ERROR_NOT_ENOUGH_MEMORY;
      goto cleanup_sources;
    }

    sources_current = sources_value;
    current = new_sources_value;
    while( *sources_current != L'\0' ) {
      if( wcsncmp( sources_current,
                   source_name,
                   source_name_size / sizeof( WCHAR ) ) != 0 ) {
        source_len = wcslen( sources_current );
        memcpy( current, sources_current, source_len * sizeof( WCHAR ) );
        current += source_len;
        *current = L'\0';
        current++;
      }

      sources_current += wcslen( sources_current ) + 1;
    }
    *current = L'\0';

    reg_result = RegSetValueExW( subkey_handle,
                                 L"Sources",
                                 0,
                                 REG_MULTI_SZ,
                                 ( const BYTE * ) new_sources_value,
                                 cap_size_t_to_dword( new_sources_size ) );

    free_mem( new_sources_value ); // candidate for alloca

    if( reg_result != ERROR_SUCCESS ) {
      result = reg_result;
      raise_windows_failure( L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE,
                             result,
                             L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
      goto cleanup_sources;
    }
  }

  // delete source subkey
  reg_result = RegDeleteTreeW( subkey_handle, source_name );
  if( reg_result != ERROR_SUCCESS ) {
    result = reg_result;
    raise_windows_failure( L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_RETURN_ERROR_CODE_TYPE );
  }

cleanup_sources:
  free_mem( sources_value );
cleanup_subkey_handle:
  CloseHandle( subkey_handle );
cleanup_complete_subkey:
  free_mem( complete_subkey );
finish:
  return result;
}

struct stumpless_entry *
stumpless_set_wel_category( struct stumpless_entry *entry, WORD category ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->category = category;
  data->category_set = TRUE;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_event_id( struct stumpless_entry *entry, DWORD event_id ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->event_id = event_id;
  data->event_id_set = TRUE;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_param( struct stumpless_entry *entry,
                                   WORD index,
                                   const struct stumpless_param *param ) {
  struct wel_data *data;
  LPCWSTR old_str;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      unlock_wel_data( data );
      return NULL;
    }
  }

  clear_error();

  data->insertion_params[index] = param;
  old_str = data->insertion_strings[index];
  data->insertion_strings[index] = NULL;
  unlock_wel_data( data );

  free_mem( old_str );
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_string( struct stumpless_entry *entry,
                                    WORD index,
                                    LPCSTR str ) {
  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( str );

  clear_error(  );
  return set_wel_insertion_string( entry, index, str );
}

struct stumpless_entry *
stumpless_set_wel_insertion_string_w( struct stumpless_entry *entry,
                                      WORD index,
                                      LPCWSTR str ) {
  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( str );

  clear_error(  );
  return set_wel_insertion_string_w( entry, index, str );
}

struct stumpless_entry *
stumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                     WORD count,
                                     ... ) {
  va_list insertions;
  struct stumpless_entry *result;

  va_start( insertions, count );
  result = vstumpless_set_wel_insertion_strings( entry, count, insertions );
  va_end( insertions );

  return result;
}

struct stumpless_entry *
  stumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
                                         WORD count,
                                         ... ) {
  va_list insertions;
  struct stumpless_entry *result;

  va_start( insertions, count );
  result = vstumpless_set_wel_insertion_strings_w( entry, count, insertions );
  va_end( insertions );

  return result;
}

struct stumpless_entry *
stumpless_set_wel_type( struct stumpless_entry *entry, WORD type ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->type = type;
  data->type_set = TRUE;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
vstumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                      WORD count,
                                      va_list insertions ) {
  struct wel_data *data;
  struct stumpless_entry *result;
  WORD i;
  const char *arg;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );

  for( i = 0; i < count; i++ ) {
    arg = va_arg( insertions, char * );

    if( !arg ) {
      raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "insertion string" ) );
      goto fail;
    }

    result = locked_set_wel_insertion_string( entry, i, arg );
    if( !result ) {
      goto fail;
    }
  }

  unlock_wel_data( data );
  clear_error(  );
  return entry;

fail:
  unlock_wel_data( data );
  return NULL;
}

struct stumpless_entry *
vstumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
                                        WORD count,
                                        va_list insertions ) {
  struct wel_data *data;
  struct stumpless_entry *result;
  WORD i;
  LPCWSTR arg;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );

  for( i = 0; i < count; i++ ) {
    arg = va_arg( insertions, LPCWSTR );

    if( !arg ) {
      raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "insertion string" ) );
      goto fail;
    }

    result = locked_set_wel_insertion_string_w( entry, i, arg );
    if( !result ) {
      goto fail;
    }
  }

  unlock_wel_data( data );
  clear_error(  );
  return entry;

fail:
  unlock_wel_data( data );
  return NULL;
}

/* private definitions */

LPCWSTR
copy_param_value_to_lpwstr( const struct stumpless_param *param ) {
  LPWSTR str_copy;
  int needed_wchar_length;
  size_t needed_wchar_count;
  int value_length_int;
  int conversion_result;

  lock_param( param );
  value_length_int = cap_size_t_to_int( param->value_length );

  needed_wchar_length = MultiByteToWideChar( CP_UTF8,
                                             MB_ERR_INVALID_CHARS |
                                               MB_PRECOMPOSED,
                                             param->value,
                                             value_length_int,
                                             NULL,
                                             0 );

  if( needed_wchar_length == 0 ) {
    raise_mb_conversion_failure( GetLastError(  ) );
    goto fail;
  }

  needed_wchar_count = ( ( size_t ) needed_wchar_length ) + 1;
  str_copy = alloc_mem( needed_wchar_count * sizeof( WCHAR ) );
  if( !str_copy ) {
    goto fail;
  }

  conversion_result = MultiByteToWideChar( CP_UTF8,
                                           MB_ERR_INVALID_CHARS |
                                             MB_PRECOMPOSED,
                                           param->value,
                                           value_length_int,
                                           str_copy,
                                           needed_wchar_length );

  if( conversion_result == 0 ) {
    raise_mb_conversion_failure( GetLastError(  ) );
    goto fail_second_conversion;
  }

  unlock_param( param );
  str_copy[needed_wchar_length] = L'\0';

  return str_copy;

fail_second_conversion:
  free_mem( str_copy );
fail:
  unlock_param( param );
  return NULL;
}

struct stumpless_entry *
copy_wel_data( struct stumpless_entry *destination,
               const struct stumpless_entry *source ) {
  struct wel_data *dest_data;
  struct wel_data* source_data;
  WORD i;

  if( !config_initialize_wel_data( destination ) ) {
    return NULL;
  }

  source_data = source->wel_data;
  dest_data = destination->wel_data;
  lock_wel_data( source_data );

  dest_data->type = source_data->type;
  dest_data->type_set = source_data->type_set;
  dest_data->category = source_data->category;
  dest_data->category_set = source_data->category_set;
  dest_data->event_id = source_data->event_id;
  dest_data->event_id_set = source_data->event_id_set;


  if( source_data->insertion_count > 0 ) {
    dest_data->insertion_params = alloc_mem( sizeof( struct stumpless_param * ) * source_data->insertion_count );
    if( !dest_data->insertion_params) {
      goto fail;
    }

    dest_data->insertion_strings = alloc_mem( sizeof( LPCSTR ) * source_data->insertion_count );
    if( !dest_data->insertion_strings) {
      goto fail_strings;
    }

    for( i = 0; i < source_data->insertion_count; i++ ) {
      dest_data->insertion_params[i] = source_data->insertion_params[i];
      if( source_data->insertion_strings[i] ){
        dest_data->insertion_strings[i] = copy_lpcwstr( source_data->insertion_strings[i] );
        if( !dest_data->insertion_strings[i] ) {
          goto fail_set_strings;
        }
      } else {
        dest_data->insertion_strings[i] = NULL;
      }
    }

    dest_data->insertion_count = source_data->insertion_count;
  }

  unlock_wel_data( source_data );
  clear_error(  );
  return destination;

fail_set_strings:
  while( i > 0 ) {
    i -= 1;
    free_mem( dest_data->insertion_strings[i] );
  }
  free_mem( dest_data->insertion_strings );
fail_strings:
  free_mem( dest_data->insertion_params );
fail:
  unlock_wel_data( source_data );
  return NULL;
}

void
destroy_wel_data(const struct stumpless_entry* entry) {
  struct wel_data *data;
  WORD i;

  data = ( struct wel_data * ) entry->wel_data;
  config_destroy_mutex( &data->mutex );

  for( i = 0; i < data->insertion_count; i++ ) {
    free_mem( data->insertion_strings[i] );
  }

  free_mem( data->insertion_strings );
  free_mem( data->insertion_params );
  free_mem( data );
}

WORD
get_category( int prival ) {
  return get_severity( prival ) + 1;
}

DWORD
get_event_id( int prival ) {
  int type_index;
  int facility;
  int wel_severity;

  type_index =  get_type_index( prival );
  switch( type_index ) {
      case 0:
        wel_severity = 0;
        break;
      case 2:
        wel_severity = 2;
      case 3:
        wel_severity = 1;
        break;
      case 1:
      default:
        wel_severity = 3;
  }
  facility =  get_facility( prival );

  return ( wel_severity << 30 ) |
           0x1000000 |
           ( ( facility ) << 13 ) |
           ( ( facility >> 3 ) + (type_index * 24 ) + 0x11 );
}

WORD
get_type( int prival ) {
  switch( get_type_index( prival ) ){
    case 0:
      return EVENTLOG_SUCCESS;

    case 2:
      return EVENTLOG_WARNING_TYPE;

    case 3:
      return EVENTLOG_INFORMATION_TYPE;

    case 1:
    default:
      return EVENTLOG_ERROR_TYPE;
  }
}

WORD
get_type_index( int prival ) {
  switch( get_severity( prival ) ) {
    case STUMPLESS_SEVERITY_DEBUG_VALUE:
      return 0;

    case STUMPLESS_SEVERITY_NOTICE_VALUE:
    case STUMPLESS_SEVERITY_INFO_VALUE:
      return 3;

    case STUMPLESS_SEVERITY_WARNING_VALUE:
      return 2;

    case STUMPLESS_SEVERITY_EMERG_VALUE:
    case STUMPLESS_SEVERITY_ALERT_VALUE:
    case STUMPLESS_SEVERITY_CRIT_VALUE:
    case STUMPLESS_SEVERITY_ERR_VALUE:
    default:
      return 1;
  }
}

bool
initialize_wel_data( struct stumpless_entry *entry ) {
  struct wel_data *data;

  data = alloc_mem( sizeof( *data ) );
  if( !data ){
    return false;
  }


  data->category_set = FALSE;
  data->event_id_set = FALSE;
  data->type_set = FALSE;
  data->insertion_strings = NULL;
  data->insertion_params = NULL;
  data->insertion_count = 0;
  config_init_mutex( &data->mutex );

  entry->wel_data = data;
  return true;
}

void
lock_wel_data( const struct wel_data *data ) {
  config_lock_mutex( &data->mutex );
}

struct stumpless_entry *
resize_insertion_params( struct stumpless_entry *entry, WORD max_index ) {
  size_t new_max_index;
  size_t new_size;
  struct wel_data *data;
  const struct stumpless_param **new_params;
  LPCWSTR *new_strings;
  WORD i;

  new_max_index = ( ( size_t ) max_index ) + 1;
  new_size = sizeof( *new_params ) * new_max_index;
  data = entry->wel_data;
  new_params = realloc_mem( data->insertion_params, new_size );
  if( !new_params ) {
    return NULL;

  } else {
    for( i = data->insertion_count; i <= max_index; i++ ) {
      new_params[i] = NULL;
    }

    data->insertion_params = new_params;

  }

  new_size = sizeof( LPCSTR ) * new_max_index;
  new_strings = realloc_mem( ( void * ) data->insertion_strings, new_size );
  if( !new_strings ) {
    return NULL;

  } else {
    for( i = data->insertion_count; i <= max_index; i++ ) {
      new_strings[i] = NULL;
    }

    data->insertion_strings = new_strings;

  }

  data->insertion_count = max_index + 1;
  return entry;
}

void
set_entry_wel_type( struct stumpless_entry *entry, int severity ) {
  struct wel_data *data;

  data = entry->wel_data;

  switch ( severity ) {
    case STUMPLESS_SEVERITY_ERR:
      data->type = EVENTLOG_ERROR_TYPE;
      break;

    case STUMPLESS_SEVERITY_INFO:
      data->type = EVENTLOG_INFORMATION_TYPE;
      break;

    case STUMPLESS_SEVERITY_WARNING:
      data->type = EVENTLOG_WARNING_TYPE;
      break;

    default:
      data->type = EVENTLOG_SUCCESS;
  }
}

void
unlock_wel_data( const struct wel_data *data ) {
  config_unlock_mutex( &data->mutex );
}

struct stumpless_entry *
locked_swap_wel_insertion_string( struct stumpless_entry *entry,
                                  WORD index,
                                  LPCWSTR str ) {
  struct wel_data *data;

  data = entry->wel_data;
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      return NULL;
    }
  } else {
    free_mem( data->insertion_strings[index] );
  }

  data->insertion_strings[index] = str;

  return entry;
}

struct stumpless_target *
wel_open_default_target( void ) {
  return stumpless_open_local_wel_target( "Stumpless" );
}
