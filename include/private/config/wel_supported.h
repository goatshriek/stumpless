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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H

/* this must be included first to avoid errors */
#  include "private/windows_wrapper.h"

#  include <stdbool.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>
#  include <stumpless/target.h>

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
   * length of both the wel_insertion_strings array and the wel_insertion_params
   * array.
   */
  WORD insertion_count;
  /**
   * A buffer to hold insertion strings during the process of sending this entry
   * to an Event log. This field should not be referred to for insertion string
   * values as it is not updated until an event is logged: the actual values are
   * stored as the values of params in wel_insertion_params.
   */
  LPCSTR* insertion_strings;
  /**
   * An array of params of which the values can be used as insertion strings with
   * Windows Event Log calls. Params in this list may not have name fields and
   * should not be used with other functions for using params. They should only
   * be interacted with using the Windows Event Log stumpless functions.
   */
  struct stumpless_param** insertion_params;
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

struct stumpless_param **
resize_insertion_params( struct stumpless_entry *entry, WORD max_index );

void
set_entry_wel_type( struct stumpless_entry *entry, int severity );

struct stumpless_target *
wel_open_default_target( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H */
