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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H

/* this must be included first to avoid errors */
#  include "private/windows_wrapper.h"

#  include <stdbool.h>
#  include <stddef.h>
#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>
#  include <stumpless/target.h>
#  include "private/config.h"
#  include "private/config/locale/wrapper.h"
#  include "private/config/wrapper/thread_safety.h"
#  include "private/error.h"

/**
 * Checks to see if the variable with the provided name is NULL, and if it is
 * then raises an argument empty error and returns ERROR_BAD_ARGUMENTS.
 *
 * This is nearly identical to VALIDATE_ARG_NOT_NULL, but is suitable for use in
 * functions where the return value needs to be resolved as a Windows error
 * code.
 */
#  define VALIDATE_ARG_NOT_NULL_WINDOWS_RETURN( ARG_NAME )                     \
if( unlikely( ARG_NAME == NULL ) ) {                                           \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) );            \
  return ERROR_BAD_ARGUMENTS;                                                  \
}

/**
 * The extra fields needed in an entry to provide information for Windows Event
 * Log messages.
 */
struct wel_data {
  /** The type of this entry, for use with Windows Event Log calls. */
  WORD type;
  /**
   * TRUE if the type has been set manually, FALSE if a default should be
   * calculated.
   */
  BOOL type_set;
  /** The category of this entry, for use with Windows Event Log calls. */
  WORD category;
  /**
   * TRUE if the category has been set manually, FALSE if a default should be
   * calculated.
   */
  BOOL category_set;
  /** The event id of this entry, for use with Windows Event Log calls. */
  DWORD event_id;
  /**
   * TRUE if the event_id has been set manually, FALSE if a default should be
   * calculated.
   */
  BOOL event_id_set;
  /**
   * The number of insertion strings this entry has. This can be used as the
   * length of both the wel_insertion_strings and wel_insertion_params arrays.
   */
  WORD insertion_count;
  /**
   * An array of insertion strings used during the process of sending this entry
   * to an Event log. Items in this array are only guaranteed to be non-NULL
   * for insertion strings that have been set with
   * `stumpless_set_wel_insertion_string`. For insertion strings that were set
   * with `stumpless_set_wel_insertion_param`, the authoritative place to check
   * is the corresponding index in the insertion_params field instead.
   *
   * In versions prior to 2.1.0, this was an array of LPCSTR instead.
   */
  LPCWSTR* insertion_strings;
  /**
   * An array of params of which the values can be used as insertion strings
   * with Windows Event Log calls. The value of the param will be used for the
   * insertion string in the same index.
   *
   * The value will be converted to a wide character string at the time of the
   * logging call, as parameter values are stored as UTF-8 multibyte strings.
   */
  struct stumpless_param const ** insertion_params;
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
  /**
   * Protects all of the data in this structure. This mutex must be locked
   * before reading or writing any of the fields.
   */
  config_mutex_t mutex;
#  endif
};

/**
 * Creates a new wide character string from the param value.
 *
 * @param param The param to copy the value from.
 *
 * @return a copy of the param value as a NULL terminated wide character string.
 */
LPCWSTR
copy_param_value_to_lpwstr( const struct stumpless_param *param );

struct stumpless_entry *
copy_wel_data( struct stumpless_entry *destination,
               const struct stumpless_entry *source );

void
destroy_wel_data( const struct stumpless_entry *entry );

/**
 * Gets the category that should be used for the given prival.
 *
 * @param prival The prival to calculate the category for.
 *
 * @return The category that should be used for a message of the given prival.
 */
WORD
get_category( int prival );

/**
 * Gets the event id that should be used for the given prival.
 *
 * @param prival The prival to calculate the event ID for.
 *
 * @return The event id that should be used for a message of the given prival.
 */
DWORD
get_event_id( int prival );

/**
 * Gets the type that should be used for the given prival.
 *
 * @param prival The prival to calculate the type for.
 *
 * @return The type that should be used for a message of the given prival.
 */
WORD
get_type( int prival );

/**
 * Gets the index of the type that should be used for the given prival.
 *
 * The index of a type is used to calculate the message id.
 *
 * @param prival The prival to calculate the type for.
 *
 * @return The index of the type that should be used for a message of the
 * given prival.
 */
WORD
get_type_index( int prival );

/**
 * Sets the Windows Event Log data structures to initial values.
 *
 * Assumes that the entry has not yet been provided for multithreaded
 * operations and therefore does not need to be locked.
 *
 * @param entry The entry to initialize.
 *
 * @return true if initialization succeeded, false if not.
 */
bool
initialize_wel_data( struct stumpless_entry *entry );

void
lock_wel_data( const struct wel_data *data );

struct stumpless_param **
resize_insertion_params( struct stumpless_entry *entry, WORD max_index );

void
set_entry_wel_type( struct stumpless_entry *entry, int severity );

void
unlock_wel_data( const struct wel_data *data );

/**
 * Sets the insertion string at the given index to the provided wide string,
 * freeing the previous one if it existed.
 *
 * Does not lock the entry or wel data structures. They need to be locked
 * separately before calling this function.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The wide string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
struct stumpless_entry *
unsafe_swap_wel_insertion_string( struct stumpless_entry *entry,
                                  WORD index,
                                  LPCWSTR str );

struct stumpless_target *
wel_open_default_target( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H */
