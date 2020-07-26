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

struct stream_target {
  FILE *stream;
};

void
destroy_stream_target( const struct stream_target *target );

struct stream_target *
new_stream_target( FILE *stream );

int
sendto_stream_target( struct stream_target *target,
                      const char *msg,
                      size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_FILE_H */
