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
#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>
#  include <stumpless/target.h>
#  include "private/config/wrapper/thread_safety.h"

/**
 * The extra fields needed in an entry to provide information for Windows Event
 * Log messages.
 */
struct wel_data {
  /** The type of this entry, for use with Windows Event Log calls. */
  WORD type;
  /** The category of this entry, for use with Windows Event Log calls. */
  WORD category;
  /** The event id of this entry, for use with Windows Event Log calls. */
  DWORD event_id;
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

struct stumpless_entry *
copy_wel_data( struct stumpless_entry *destination,
               const struct stumpless_entry *source );

void
destroy_wel_data( const struct stumpless_entry *entry );

void
destroy_insertion_params( const struct stumpless_entry *entry );

void
destroy_insertion_string_param( const struct stumpless_param *param );

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

struct stumpless_target *
wel_open_default_target( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H */
