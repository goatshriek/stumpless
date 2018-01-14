/*
 * Copyright 2017, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include "private/entry.h"
#include "private/formatter.h"
#include "private/memory.h"

char *format_entry(const struct stumpless_target *target, struct stumpless_entry *entry){
  char *buffer, *position;
  int prival;

  // todo make the size configurable or smarter
  buffer = alloc_mem(1024);
  if( !buffer ){
    return NULL;
  }

  prival = target->facility*8 + target->severity;
  position = buffer + snprintf(buffer, RFC_5424_MAX_PRI_LENGTH+3, "<%d>1 ", prival);
  position += get_rfc5424_timestamp(position, 1024-(position-buffer));
  *(position++) = ' ';
  position += get_hostname(position, 1024-(position-buffer));
  *(position++) = ' ';
  position += get_app_name(entry, position, 1024-(position-buffer));
  *(position++) = ' ';
  position += get_procid(position, 1024-(position-buffer));
  *(position++) = ' ';
  position += get_msgid(entry, position, 1024-(position-buffer));
  *(position++) = ' ';
  position += get_structured_data(position, 1024-(position-buffer));
  *(position++) = ' ';
  get_message(entry, position, 1024-(position-buffer));

  return buffer;
}

ssize_t get_rfc5424_timestamp(char *destination, size_t size){
  char buffer[RFC_5424_MAX_TIMESTAMP_LENGTH];
  struct tm *now;
  time_t now_timer;
  size_t written;

  now_timer = time(NULL);
  now = gmtime(&now_timer);
  // todo add support for fractional times
  written = strftime(buffer, RFC_5424_MAX_TIMESTAMP_LENGTH, "%FT%TZ", now);

  if(written > size){
    return -((ssize_t)written);
  } else {
    memcpy(destination, buffer, written);
    return written;
  }
}
