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
