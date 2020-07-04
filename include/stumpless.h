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
 * The main header file for the library. Unless you are specifically trying to
 * reduce your compilation times by including ONLY the necessary headers, it is
 * best to only include this header. It will ensure that all available features
 * are declared, as well as take care of any ordering or conditional includes
 * that may be necessary on the target platform.
 *
 * If you do want to only include specific header files for some reason, you
 * can use this file as a template for doing so. Note that all headers are
 * under a stumpless directory, which should be included in the path.
 */

#ifndef __STUMPLESS_H
#  define __STUMPLESS_H

/* the config includes should always be first, thanks to windows.h */
#  include <stumpless/config.h>

#  include <stumpless/element.h>
#  include <stumpless/entry.h>
#  include <stumpless/error.h>
#  include <stumpless/facility.h>
#  include <stumpless/id.h>
#  include <stumpless/level/info.h>
#  include <stumpless/memory.h>
#  include <stumpless/option.h>
#  include <stumpless/param.h>
#  include <stumpless/severity.h>
#  include <stumpless/target.h>
#  include <stumpless/target/buffer.h>
#  include <stumpless/target/file.h>
#  include <stumpless/target/stream.h>
#  include <stumpless/version.h>

#  ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
#    include <stumpless/target/network.h>
#  endif

#  ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include <stumpless/target/socket.h>
#  endif

#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include <stumpless/config/wel_supported.h>
#    include <stumpless/target/wel.h>
#  endif

#endif /* __STUMPLESS_H */
