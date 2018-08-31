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
#include <time.h>
#include <stumpless/entry.h>
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/strbuilder.h"
#include "private/formatter.h"

struct strbuilder *
format_entry( struct stumpless_entry *entry ) {
  struct strbuilder *builder;

  builder = strbuilder_new(  );
  builder = strbuilder_append_char( builder, '<' );
  builder = strbuilder_append_int( builder, entry->prival );
  builder = strbuilder_append_string( builder, ">1 " );
  builder = strbuilder_append_rfc5424_timestamp( builder );
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

struct strbuilder *
strbuilder_append_rfc5424_timestamp( struct strbuilder *builder ) {
  struct strbuilder *result_builder;
  char buffer[RFC_5424_WHOLE_TIME_BUFFER_SIZE];
  struct tm now_tm;
  struct timespec now_ts;
  size_t written;
  int get_now_result;
  int microseconds_fraction;

  get_now_result = config_get_now( &now_tm, &now_ts );
  if( get_now_result != 0 ) {
    return NULL;
  }

  written = strftime( buffer, RFC_5424_WHOLE_TIME_BUFFER_SIZE, "%FT%T", &now_tm );
  result_builder = strbuilder_append_buffer( builder, buffer, written );
  result_builder = strbuilder_append_char( result_builder, '.' );

  microseconds_fraction = ( now_ts.tv_nsec / 1000 ) % 1000000;
  result_builder = strbuilder_append_int( result_builder, microseconds_fraction );

  return strbuilder_append_char( result_builder, 'Z' );
}
