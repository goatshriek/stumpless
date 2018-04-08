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
#include <stumpless/target.h>
#include "private/entry.h"
#include "private/strbuilder.h"
#include "private/formatter.h"

char *format_entry(const struct stumpless_target *target, struct stumpless_entry *entry){
  char *str;
  struct strbuilder *builder, *first_builder;
  int prival;

  first_builder = strbuilder_new();

  builder = strbuilder_append_char(first_builder, '<');

  prival = target->facility*8 + target->severity;
  builder = strbuilder_append_int(builder, prival);

  builder = strbuilder_append_string(builder, ">1 ");
  builder = strbuilder_append_rfc5424_timestamp(builder);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_hostname(builder);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_app_name(builder, entry);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_procid(builder);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_msgid(builder, entry);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_structured_data(builder, entry);
  builder = strbuilder_append_char(builder, ' ');
  builder = strbuilder_append_message(builder, entry);

  str = strbuilder_to_string(builder);
  strbuilder_destroy(first_builder);

  return str;
}

struct strbuilder *strbuilder_append_rfc5424_timestamp(struct strbuilder *builder){
  char buffer[RFC_5424_MAX_TIMESTAMP_LENGTH];
  struct tm *now;
  time_t now_timer;
  size_t written;

  now_timer = time(NULL);
  now = gmtime(&now_timer);
  // todo add support for fractional times
  written = strftime(buffer, RFC_5424_MAX_TIMESTAMP_LENGTH, "%FT%TZ", now);
  return strbuilder_append_buffer(builder, buffer, written);
}
