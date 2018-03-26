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

#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#define __STUMPLESS_PRIVATE_FORMATTER_H

#include <stddef.h>
#include <sys/types.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>

#define RFC_5424_MAX_PRI_LENGTH 5
#define RFC_5424_MAX_TIMESTAMP_LENGTH 32
#define RFC_5424_MAX_HOSTNAME_LENGTH 255
#define RFC_5424_MAX_PROCID_LENGTH 128

char *format_entry(const struct stumpless_target *target, struct stumpless_entry *entry);

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
