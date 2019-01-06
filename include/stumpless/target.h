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

#ifndef __STUMPLESS_TARGET_H
#  define __STUMPLESS_TARGET_H

#  include <stddef.h>
#  include <stumpless/entry.h>
#  include <stumpless/id.h>

#  ifdef __cplusplus
extern "C" {
#  endif

enum stumpless_target_type {
  STUMPLESS_BUFFER_TARGET,
  STUMPLESS_FILE_TARGET,
  STUMPLESS_NETWORK_TARGET,
  STUMPLESS_SOCKET_TARGET,
  STUMPLESS_STREAM_TARGET,
  STUMPLESS_WINDOWS_EVENT_LOG_TARGET
};

struct stumpless_target {
  stumpless_id_t id;
  enum stumpless_target_type type;
  char *name;
  int options;
  int default_prival;
  char *default_app_name;
  size_t default_app_name_length;
  char *default_msgid;
  size_t default_msgid_length;
  int mask;
};

int
stumpless( const char *message );

int
stumpless_add_entry( struct stumpless_target *target,
                     struct stumpless_entry *entry );

struct stumpless_target *
stumpless_get_current_target( void );

/**
 * Gets the default facility of a target.
 *
 * @param target The target to get the facility from..
 *
 * @return The default facility if no error is encountered. If an error is
 * encountered, then -1 is returned and an error code is set appropriately.
 */
int
stumpless_get_default_facility( const struct stumpless_target *target );

/**
 * Opens a target that has already been created and configured.
 *
 * Targets that have been created using the \c stumpless_new_*_target family of
 * functions need to be opened once they have been configured with all of the
 * desired parameters.
 *
 * If the provided target has not had all mandatory settings configured or some
 * other error is encountered, then the operation will fail and the target will
 * remain in a paused state.
 *
 * @param target The target to open.
 *
 * @return The opened target if it was opened successfully (which will be
 * equal to the target argument). If an error was encountered, then NULL is
 * returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_target( struct stumpless_target *target );

void
stumpless_set_current_target( struct stumpless_target *target );

/**
 * Sets the default facility of a target.
 *
 * @param target The target to modify.
 *
 * @param default_facility The default facility to use on the target.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_set_default_facility( struct stumpless_target *target,
                                int default_facility );

struct stumpless_target *
stumpless_set_target_default_app_name( struct stumpless_target *target,
                                       const char *app_name );

struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid );

/**
 * Checks to see if the given target is open.
 *
 * For targets that are opened with a single \open function call, they will
 * likely be open considered open as long as they are non-NULL, as the target
 * creation would otherwise fail before it could be opened. Targets are
 * be considered in a paused state if they were created but not opened yet, for
 * example with \c stumpless_new_network_target as opposed to
 * \c stumpless_open_network_target. Targets may also be paused if a settings
 * change has been made that could not be validated, such as changing the port
 * on a TCP network target to one that does not respond on the server.
 *
 * @param target The target to check.
 *
 * @return The target if it is currently open, and NULL if not.
 */
const struct stumpless_target *
stumpless_target_is_open( const struct stumpless_target *target );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_TARGET_H */
