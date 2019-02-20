/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2019 Joel E. Anderson
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
 * @param name The name of the logging target, as well as the name of the file
 * to open.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them. This should be a \c STUMPLESS_FACILITY value.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_file_target( const char *name,
                            int options,
                            int default_facility );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_FILE_H */
