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
 * File targets allow logs to be sent to a specified file. Files are created
 * as needed, and logs are appended to any existing contents.
 *
 * **Thread Safety: MT-Safe**
 * Logging to file targets is thread safe. A mutex is used to coordinate
 * writes to the file.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to file targets is not signal safe, as a non-reentrant lock is used
 * to coordinate writes to the file.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to file targets is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock may not be completed.
 */

#ifndef __STUMPLESS_TARGET_FILE_H
#  define __STUMPLESS_TARGET_FILE_H

#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Closes a file target.
 *
 * This function closes the file target, as well as the stream opened to the
 * file.
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
 * @param target The file target to close.
 */
void
stumpless_close_file_target( struct stumpless_target *target );

/**
 * Opens a file target.
 *
 * File targets send logs to a file on the system. Note that this will open the
 * specified file, and it will remain open while the file target is open. If you
 * need to control the file stream yourself, then you should consider using a
 * stream target instead.
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
 * @param name The name of the logging target, as well as the name of the file
 * to open.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_file_target( const char *name );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_FILE_H */
