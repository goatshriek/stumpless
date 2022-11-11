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

#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/option.h>
#include <stumpless/target.h>
#include "private/entry.h"
#include "private/strbuilder.h"
#include "private/formatter.h"
#include "private/config/wrapper/get_now.h"

struct strbuilder *
format_entry( const struct stumpless_entry *entry,
              const struct stumpless_target *target ) {
  char timestamp[RFC_5424_TIMESTAMP_BUFFER_SIZE];
  struct strbuilder *builder;
  size_t timestamp_size;

  // do this as soon as possible to be closer to invocation
  timestamp_size = config_get_now( timestamp );

  lock_entry( entry );

  builder = strbuilder_new(  );
  builder = strbuilder_append_char( builder, '<' );
  builder = strbuilder_append_positive_int( builder, entry->prival );
  builder = strbuilder_append_string( builder, ">1 " );
  builder = strbuilder_append_buffer( builder, timestamp, timestamp_size );
  builder = strbuilder_append_char( builder, ' ' );

  if( entry->hostname_length > 0 ) {
    builder = strbuilder_append_buffer( builder,
                                        entry->hostname,
                                        entry->hostname_length );
  } else {
    builder = strbuilder_append_hostname( builder );
  }

  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_app_name( builder, entry );
  builder = strbuilder_append_char( builder, ' ' );
  if( target->options & STUMPLESS_OPTION_PID ) {
    if( entry->procid_length > 0 ) {
      builder = strbuilder_append_buffer( builder,
                                          entry->procid,
                                          entry->procid_length );
    } else {
      builder = strbuilder_append_procid( builder );
    }
  } else {
    builder = strbuilder_append_char( builder, RFC_5424_NILVALUE );
  }
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_msgid( builder, entry );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_structured_data( builder, entry );

  if( entry->message_length > 0 ) {
    builder = strbuilder_append_char( builder, ' ' );
    builder = strbuilder_append_message( builder, entry );
  }

  builder = strbuilder_append_char( builder, '\n' );

  unlock_entry( entry );

  return builder;
}
