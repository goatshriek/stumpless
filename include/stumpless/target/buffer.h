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

/** @file
 * Buffer targets provide the simple capability to write logs into a character
 * buffer.
 *
 * The interface for buffer targets is based on the Linux kernel log buffer
 * interface. Interacting with the buffer should only be done using the provided
 * functions, or corruption or loss of log messages may occur.
 *
 * The contents of the buffer itself may be modified at any time, and should not
 * be read directly with any expectation of consistency or coherence.
 *
 * **Thread Safety: MT-Safe**
 * Logging to buffer targets is thread safe. A mutex is used to coordinate
 * changes to the buffer with each other and reads.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to buffer targets is not signal safe, as a non-reentrant lock is used
 * to coordinate accesses to the buffer.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to buffer targets is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock may not be completed.
 */

#ifndef __STUMPLESS_TARGET_BUFFER_H
#  define __STUMPLESS_TARGET_BUFFER_H

#  include <stddef.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes a buffer target.
 *
 * Note that this will not release the buffer it was dynamically allocated. This
 * must be done after the buffer target is closed to avoid invalid memory
 * accesses.
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
 * @param target The buffer target to close.
 */
void
stumpless_close_buffer_target( const struct stumpless_target *target );

/**
 * Creates a buffer target for the given buffer.
 *
 * Buffer targets will write messages to the given buffer, wrapping around when
 * the end is reached. A NULL character will be written to the end of each
 * message. Note that callers must handle the wrap-around case, and not assume
 * that each read will end in a NULL character, in case a wrap-around occurs.
 *
 * Messages that are too large to fit into the buffer will be discarded.
 *
 * Messages are overwritten as new messages come in. If the user of the buffer
 * target is not reading these, they will be lost.
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
 * @param buffer The buffer to write messages to.
 *
 * @param size The number of characters the provided buffer can hold.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them. This should be a \c STUMPLESS_FACILITY value.
 *
 * @return The new target if no error is encountered. In the event of an error,
 * NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_buffer_target( const char *name,
                              char *buffer,
                              size_t size,
                              int options,
                              int default_facility );

/**
 * Reads the next message from the provided buffer target and writes it into the
 * given buffer.
 *
 * If the buffer has not been read from before messages have wrapped around,
 * then you may only get the end of a message. To avoid this situation, you will
 * need to read the buffer often enough to stay ahead of the written messages.
 * Making sure that the log buffer is sufficiently sized may help with this.
 *
 * A terminating NULL character will always be written at the end of the output.
 * Note that this means that if the read operation was successful but there was
 * no message to read, the result will be 1 with a single NULL character being
 * written to the read buffer.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate reads and writes
 * of the message buffer.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock to coordinate accesses.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as a lock may be left locked when a thread exits prematurely.
 *
 * @param target The buffer target to read from.
 *
 * @param buffer The buffer to write the message in to.
 *
 * @param max_length The maximum number of bytes to write into the provided
 * buffer. If this is zero, then the read buffer will be considered an
 * empty argument and an error will be raised.
 *
 * @return The number of bytes written into buffer, including the terminating
 * NULL character. In the event of an error, 0 is returned and an error code
 * is set appropriately.
 */
size_t
stumpless_read_buffer( struct stumpless_target *target,
                       char *buffer,
                       size_t max_length );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_BUFFER_H */
