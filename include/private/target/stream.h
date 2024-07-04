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

#ifndef __STUMPLESS_PRIVATE_TARGET_STREAM_H
#  define __STUMPLESS_PRIVATE_TARGET_STREAM_H

#  include <stddef.h>
#  include <stdio.h>
#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include "private/config/wrapper/thread_safety.h"

/**
 * Internal representation of a stream target.
 */
struct stream_target {
/** The stream this target writes to. */
  FILE *stream;
/** ANSI colors for different severities (when using ansi terminal) */
  char escape_codes[8][32];
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects stream. This mutex must be locked by a thread before it can write
 * to the stream.
 */
  config_mutex_t stream_mutex;
#  endif
};

void
destroy_stream_target( const struct stream_target *target );

struct stream_target *
new_stream_target( FILE *stream );

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The stream_mutex is used to coordinate updates
 * to the stream.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate writes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 */
int
sendto_stream_target( struct stream_target *target,
                      const char *msg,
                      size_t msg_length,
		      const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_STREAM_H */
