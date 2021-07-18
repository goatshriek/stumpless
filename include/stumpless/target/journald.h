/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021 Joel E. Anderson
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
 * Journald targets send messages to a systemd journald service.
 *
 * Journald supports structured logging but does not use the same hierarchy as
 * RFC 5424, instead providing a simple key/value pairing. To compensate for
 * this, these targets perform a number of transformations to map the elements
 * and params into the flatter structure. Element and param names are converted
 * to uppercase and are joined together using underscores. The value of the
 * param is then passed as the value of the field.
 *
 * Because RFC 5424 allows most printable ASCII characters while journald only
 * allows letters and numbers, incompatible characters of the generated field
 * name will be replaced with an underscore to comply with journald
 * requirements.
 *
 * **Thread Safety: MT-Safe**
 * Logging to journald targets is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * Logging to journald targets is signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Logging to journald targets is not async signal safe as it relies on
 * sd_journal_sendv which is not documented as such.
 */

#ifndef __STUMPLESS_TARGET_JOURNALD_H
#  define __STUMPLESS_TARGET_JOURNALD_H

#  include <stdbool.h>
#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes a journald target.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * the memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 *
 * @since v2.1.0
 *
 * @param target The journald target to close.
 */
void
stumpless_close_journald_target( const struct stumpless_target *target );

/**
 * Creates a name for the param by combining the element and param name. Both
 * names are converted to all upper case and combined using underscore
 * characters.
 *
 * **Thread Safety: MT-Safe race:dest race:length**
 * This function is thread safe. It uses other thread-safe functions to
 * access the element and param names it needs. This assumes that dest and
 * length are not modified during the call.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since v2.1.0
 *
 * @param entry The entry that the param is part of.
 *
 * @param element_index The index of the element the param is part of.
 *
 * @param param_index The index of the param within the element.
 *
 * @param dest The buffer to write the name to. The buffer must be of at least
 * size 1, to receive a NULL character.
 *
 * @param length On input, the size of the destination buffer. On output, the
 * size of the string written to the buffer. If dest was too small, then this
 * will instead have the size needed for the buffer, and dest will have a single
 * NULL character written to it.
 *
 * @return True if the call succeeded, false if not.
 */
bool
stumpless_flatten_param_name( const struct stumpless_entry *entry,
                              size_t element_index,
                              size_t param_index,
                              char *dest,
                              size_t *length );

/**
 * Opens a journald target.
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
 * @since v2.1.0
 *
 * @param name The name of the logging target.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_journald_target( const char *name );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_JOURNALD_H */
