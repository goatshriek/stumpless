// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/strbuilder.h"
#include "private/formatter.h"

struct strbuilder *
format_entry( struct stumpless_entry *entry ) {
  char timestamp[RFC_5424_TIMESTAMP_BUFFER_SIZE];
  struct strbuilder *builder;
  size_t written;

  written = config_get_now( timestamp );

  builder = strbuilder_new(  );
  builder = strbuilder_append_char( builder, '<' );
  builder = strbuilder_append_int( builder, entry->prival );
  builder = strbuilder_append_string( builder, ">1 " );
  builder = strbuilder_append_buffer( builder, timestamp, written );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_hostname( builder );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_app_name( builder, entry );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_procid( builder );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_msgid( builder, entry );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_structured_data( builder, entry );
  builder = strbuilder_append_char( builder, ' ' );
  builder = strbuilder_append_message( builder, entry );

  return builder;
}
