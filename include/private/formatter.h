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

#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#  define __STUMPLESS_PRIVATE_FORMATTER_H

#  include <stumpless/entry.h>
#  include "private/strbuilder.h"

#  define RFC_5424_FULL_DATE_BUFFER_SIZE 11
#  define RFC_5424_FULL_TIME_BUFFER_SIZE 10
#  define RFC_5424_MAX_PRI_LENGTH 5
#  define RFC_5424_MAX_TIMESTAMP_LENGTH 32
#  define RFC_5424_MAX_HOSTNAME_LENGTH 255
#  define RFC_5424_MAX_PROCID_LENGTH 128
#  define RFC_5424_TIME_SECFRAC_BUFFER_SIZE 8
#  define RFC_5424_TIMESTAMP_BUFFER_SIZE 33
#  define RFC_5424_WHOLE_TIME_BUFFER_SIZE 20

/**
 * Creates a new strbuilder with the formatted message.
 *
 * A newline is added to the end of the message - it is up to functions that use
 * this to decide whether they want to include this newline or not.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to ensure that the entry does
 * not change while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to prevent changes during the read.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked.
 *
 * @param entry The entry to format.
 *
 * @return A strbuilder with the formatted version of the entry, with a newline
 * character added to the end.
 */
struct strbuilder *
format_entry( const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_FORMATTER_H */
