/* SPDX-License-Identifier: Apache-2.0 */

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
#  define __STUMPLESS_PRIVATE_FORMATTER_H

#  include <stumpless/entry.h>
#  include <stumpless/target.h>
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

struct strbuilder *
format_entry( struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_FORMATTER_H */
