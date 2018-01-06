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

#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#define __STUMPLESS_PRIVATE_FORMATTER_H

#include <stddef.h>
#include <sys/types.h>
#include <stumpless/target.h>

#define RFC_5424_MAX_PRI_LENGTH 5
#define RFC_5424_MAX_TIMESTAMP_LENGTH 32
#define RFC_5424_MAX_HOSTNAME_LENGTH 255

char *format_entry(const struct stumpless_target *target, const char *entry);

ssize_t get_hostname(char *destination, size_t size);

/*
 * Gets the current timestamp and writes it to the character buffer provided in
 * destination. The time reflected by the timestamp will be as close to the time
 * of the function invocation as feasible.
 *
 * A NULL teriminating character will NOT be written to destination.
 *
 * If sufficient space is not available in the destination according to the size
 * provided, nothing will be written to the destination.
 *
 * Upon success the return value is the number of bytes written into
 * destination. If there is an error, the return value is -1. If there is not
 * enough space in the destination as deterimined by size, the return value will
 * be a negative number indicating how many bytes were actually needed.
 */
ssize_t get_rfc5424_timestamp(char *destination, size_t size);

#endif /* __STUMPLESS_PRIVATE_FORMATTER_H */
