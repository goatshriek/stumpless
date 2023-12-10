/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2023 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SQLITE3_H
#define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SQLITE3_H

#include <stumpless/config.h>

#ifdef STUMPLESS_SQLITE3_TARGETS_SUPPORTED
#  include <stumpless/target/sqlite3.h>
#  include "private/target/sqlite3.h"
#  define config_close_sqlite3_target_and_db                                   \
stumpless_close_sqlite3_target_and_db
#  define config_send_entry_to_sqlite3_target send_entry_to_sqlite3_target
#else
#  include "private/target.h"
#  define config_close_sqlite3_target_and_db close_unsupported_target
#  define config_send_entry_to_sqlite3_target send_entry_to_unsupported_target
#endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SQLITE3_H */
