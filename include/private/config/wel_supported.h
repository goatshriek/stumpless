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

#  include <stumpless/entry.h>
#  include <stumpless/param.h>
#  include <stumpless/target.h>
#  include <windows.h>

struct stumpless_entry *
copy_wel_fields( struct stumpless_entry *destination,
                 const struct stumpless_entry *source );

void
destroy_insertion_params( const struct stumpless_entry *entry );

void
destroy_insertion_string_param( const struct stumpless_param *param );

void
initialize_insertion_params( struct stumpless_entry *entry );

struct stumpless_param **
resize_insertion_params( struct stumpless_entry *entry, WORD max_index );

void
set_entry_wel_type( struct stumpless_entry *entry, int severity );

struct stumpless_target *
wel_open_default_target( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_WEL_SUPPORTED_H */
