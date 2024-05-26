/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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
 * Functions for working with Windows Event Log (WEL) targets.
 *
 * WEL targets submit events using ReportEvent to a Windows system. By default,
 * the category, message id, and type will use values based on the severity and
 * facility of the logged event for messages included in Stumpless itself. If
 * you need to use your own message files, use the functions in
 * stumpless/config/wel_supported.h to specifically set these values. The
 * formatted syslog message is included as the event binary data.
 *
 * Note that if the event source is not installed the Event Viewer will not be
 * able to display the messages or category text for received events. If you'd
 * like to use the default messages included in Stumpless, use the
 * stumpless_add_default_wel_event_source function to install it on the calling
 * system.
 *
 * This header will not be available in builds where Windows Event Log targets
 * are not supported.
 *
 * **Thread Safety: MT-Safe**
 * Logging to WEL targets is thread safe by virtue of using the `ReportEvent`
 * function which is thread-safe itself.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to WEL targets is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the entry's WEL data with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to WEL targets is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock used for entry's WEL
 * data may not be completed.
 */

#ifndef __STUMPLESS_TARGET_WEL_H
#  define __STUMPLESS_TARGET_WEL_H

#  include <stumpless/config.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes a Windows Event Log target.
 *
 * In addition to closing the target, this function also destroys all memory
 * allocated for the target, including the target struct itself.
 *
 * If there is a problem while closing the target, then an error code will be
 * set appropriately, the target will NOT be closed, and no memory will be
 * released. To avoid a memory leak, check for errors using
 * `stumpless_has_error` and resolve any errors that arise before calling this
 * function again.
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
 * @param target The Windows Event Log target to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_wel_target( struct stumpless_target *target );

/**
 * Opens a Windows Event Log target on the local machine.
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
 * @param name The name of the target to open. This should match the name of the
 * Windows Event Source that the logs will be added to.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_local_wel_target( const char *name );

/**
 * Opens a Windows Event Log target on a remote machine.
 *
 * **Thread Safety: MT-Safe race:server race:name**
 * This function is thread safe, of course assuming that server and name are
 * not modified by any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @param server The remote server to log to. This should use the Universal
 * Naming Convention (UNC) of the remote end. If this parameter is set to NULL,
 * then the local machine is used. This is equivalent to a call to
 * stumpless_open_local_wel_target().
 *
 * @param name The name of the target to open. This should match the name of the
 * Windows Event Source that the logs will be added to.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_remote_wel_target( const char *server, const char *name );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_WEL_H */
