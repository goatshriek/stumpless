/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_OPEN_DEFAULT_TARGET_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_OPEN_DEFAULT_TARGET_H

#  include <stumpless/config.h>


/* definition of config_open_default_target */
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include "private/config/wel_supported.h"
#    include "stumpless/target/wel.h"
#    define config_open_default_target wel_open_default_target
#    define config_close_default_target stumpless_close_wel_target
#  elif STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include <stumpless/target/socket.h>
#    include "private/config/socket_supported.h"
#    define config_open_default_target socket_open_default_target
#    define config_close_default_target stumpless_close_socket_target
#  else
#    include <stumpless/target/file.h>
#    include "private/target/file.h"
#    define config_open_default_target file_open_default_target
#    define config_close_default_target stumpless_close_file_target
#  endif
#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_OPEN_DEFAULT_TARGET_H */
