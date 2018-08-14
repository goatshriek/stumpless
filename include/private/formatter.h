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

#  define RFC_5424_MAX_PRI_LENGTH 5
#  define RFC_5424_MAX_TIMESTAMP_LENGTH 32
#  define RFC_5424_MAX_HOSTNAME_LENGTH 255
#  define RFC_5424_MAX_PROCID_LENGTH 128

struct strbuilder *
format_entry( const struct stumpless_target *target,
              struct stumpless_entry *entry );

/*
 * Gets the current timestamp and writes it to the string builder. The time
 * reflected by the timestamp will be as close to the time of the function
 * invocation as feasible.
 */
struct strbuilder *
strbuilder_append_rfc5424_timestamp( struct strbuilder *builder );

#endif /* __STUMPLESS_PRIVATE_FORMATTER_H */
