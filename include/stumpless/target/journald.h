/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021-2022 Joel E. Anderson
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
 * this these targets perform a number of transformations to map the elements
 * and params into the flat hierarchy. By default element and param names are
 * converted to uppercase and are joined together using underscores, but this
 * behavior can be customized as needed.
 *
 * Because RFC 5424 allows most printable ASCII characters while journald only
 * allows letters and numbers, incompatible characters of the generated field
 * name will be replaced with an underscore to comply with journald
 * requirements.
 *
 * **Thread Safety: MT-Safe**
 * Logging to journald targets is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Logging to journald targets is not signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Logging to journald targets is not async cancellation safe as it relies on
 * sd_journal_sendv which is not documented as such.
 */

#ifndef __STUMPLESS_TARGET_JOURNALD_H
#  define __STUMPLESS_TARGET_JOURNALD_H

#  include <stddef.h>
#  include <stumpless/config.h>
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
 * @since release v2.1.0
 *
 * @param target The journald target to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_journald_target( const struct stumpless_target *target );

/**
 * Creates a journald-compliant name for the element. All lower case letters are
 * converted to upper case. Characters that are not alphanumeric are replaced
 * with an underscore character. This includes any UTF-8 characters.
 *
 * If the destination buffer is too small to hold the complete name, then
 * nothing is done. Callers can detect this by comparing the return value to
 * the value provided in the size argument. If the return value is larger,
 * then nothing was done.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe. It reads fields of the entry and element
 * without any synchronization.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry that the param is part of.
 *
 * @param element_index The index of the element in the entry.
 *
 * @param destination The buffer to write the name to.
 *
 * @param size The maximum number of bytes to write to the destination
 * buffer.
 *
 * @return The number of bytes needed to write the complete flattened name, not
 * including a NULL terminating character. If this is greater than size, then
 * it signifies that nothing was done.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_flatten_element_name( const struct stumpless_entry *entry,
                                size_t element_index,
                                char *destination,
                                size_t size );

/**
 * Creates a name for the param by combining the element and param name. Both
 * names are converted to all upper case and combined with an underscore
 * character between them.
 *
 * Characters that are not alphanumeric are replaced with an underscore
 * character. This includes any UTF-8 characters.
 *
 * If the destination buffer is too small to hold the complete name, then
 * nothing is done. Callers can detect this by comparing the return value to
 * the value provided in the size argument. If the return value is larger,
 * then nothing was done by the call.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe. It reads fields of the entry, element,
 * and param without any synchronization.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry that the param is part of.
 *
 * @param element_index The index of the element the param is part of.
 *
 * @param param_index The index of the param within the element.
 *
 * @param destination The buffer to write the name to.
 *
 * @param size The maximum number of bytes to write to the destination
 * buffer.
 *
 * @return The number of bytes needed to write the complete flattened name, not
 * including a NULL terminating character. If this is greater than size, then
 * it signifies that nothing was done.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_flatten_param_name( const struct stumpless_entry *entry,
                              size_t element_index,
                              size_t param_index,
                              char *destination,
                              size_t size );

/**
 * Opens a journald target. This target will send log entries to the local
 * service.
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
 * @since release v2.1.0
 *
 * @param name The name of the logging target.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_journald_target( const char *name );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_JOURNALD_H */
