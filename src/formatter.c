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

#include <stumpless/target.h>
#include "private/formatter.h"
#include "private/memory.h"

char *format_entry(const struct stumpless_target *target, const char *message){
  char *buffer;

  // todo make the size configurable or smarter
  buffer = alloc_mem(1024);
  buffer[0] = '<';
  buffer[1] = '1';
  buffer[2] = '7';
  buffer[3] = '>';
  buffer[4] = '3';
  buffer[5] = ' ';
  buffer[6] = '2';
  buffer[7] = '0';
  buffer[8] = '1';
  buffer[9] = '4';
  buffer[10] = '-';
  buffer[11] = '0';
  buffer[12] = '2';
  buffer[13] = '-';
  buffer[14] = '2';
  buffer[15] = '2';
  buffer[16] = 'T';
  buffer[17] = '1';
  buffer[18] = '2';
  buffer[19] = ':';
  buffer[20] = '2';
  buffer[21] = '2';
  buffer[22] = ':';
  buffer[23] = '5';
  buffer[24] = '9';
  buffer[25] = '.';
  buffer[26] = '1';
  buffer[27] = '2';
  buffer[28] = '3';
  buffer[29] = 'Z';
  buffer[30] = ' ';
  buffer[31] = '\0';

  // fill in fields

  return buffer;
}
