/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2022 Joel E. Anderson
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
 *
 * **Thread Safety: MT-Safe**
 * Logging to stream targets is thread safe. A mutex is used to coordinate
 * writes to the stream.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to stream targets is not signal safe, as a non-reentrant lock is used
 * to coordinate writes to the stream.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to stream targets is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock may not be completed.
 */

#ifndef __STUMPLESS_TARGET_STREAM_H
#  define __STUMPLESS_TARGET_STREAM_H

#  include <stdio.h>
#  include <stumpless/config.h>
#  include <stumpless/target.h>
#  include <stumpless/severity.h>

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
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @param target The stream target to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_stream_target( const struct stumpless_target *target );

/**
 * Opens a stream target for the stderr stream.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not modified by
 * any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_stderr_target( const char *name );

/**
 * Opens a stream target for the stdout stream.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not modified by
 * any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_stdout_target( const char *name );

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
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not modified by
 * any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param stream The stream to log events to.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_stream_target( const char *name, FILE *stream );

/**
 * Sets the ANSI escape code (https://en.wikipedia.org/wiki/ANSI_escape_code) to 
 * be printed in a specific target when a log is made at some severity.
 *
 * It should be used with stdout or stderr as targets, since it is only for aesthetic purposes.
 *
 * **Thread Safety: MT-Safe race:escape_code**
 * This function is thread safe, of course assuming that escape_code is not modified by
 * any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed.
 *
 * @param target The name of the target for which to set the colors.
 *
 * @param severity The severity code (LOG_ERR etc.) to which we set the specific color.
 *
 * @param escape_code The ANSI escape code representing the color.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_set_severity_color( struct stumpless_target *target, enum stumpless_severity severity, const char *escape_code );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_STREAM_H */
