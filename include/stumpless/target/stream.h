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

/** @file
 * Functions for working with stream targets (that is, FILE pointers).
 */

#ifndef __STUMPLESS_TARGET_STREAM_H
#  define __STUMPLESS_TARGET_STREAM_H

#  include <stdio.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes a stream target.
 *
 * This function does NOT close the stream associated with the target. It does
 * destroy all memory allocated for the target, including the target struct
 * itself.
 *
 * @param target The stream target to close.
 */
void
stumpless_close_stream_target( struct stumpless_target *target );

/**
 * Opens a stream target for the stderr stream.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_stderr_target( const char *name,
                              int options,
                              int default_facility );

/**
 * Opens a stream target for the stdout stream.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_stdout_target( const char *name,
                              int options,
                              int default_facility );

/**
 * Opens a stream target for the given stream.
 *
 * Events logged to this target will be separated by a newline, just as with a
 * file target. In fact, a stream target is equivalent to a file target with the
 * difference being that the file must be opened and closed by the caller.
 *
 * A stream target can also be useful for logging to other streams, such as
 * stdout and stderr, which is not possible with a file target.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param stream The stream to log events to.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_stream_target( const char *name,
                              FILE *stream,
                              int options,
                              int default_facility );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_STREAM_H */
