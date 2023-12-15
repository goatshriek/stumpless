/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2023 Joel E. Anderson
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

/** @mainpage Stumpless
 *
 * Stumpless is a logging library built for high performance and a rich feature
 * set.
 */

/** @example basic_example.c
 * Demonstrates usage of the basic logging calls (stump(), stump_str(),
 * stumpless_add_message(), stumplog()).
 */

/** @example cpp_example.cpp
 * Demonstrates usage of Stumpless through the C++ bindings.
 */

/** @example entry_example.c
 * Demonstrates different ways to work with stumpless_entry and related
 * structures.
 */

/** @example file_example.c
 * Demonstrates how to work with a file target.
 */

/** @example filter_example.c
 * Demonstrates how to work with runtime filters on logging targets.
 */

/** @example function_example.c
 * Demonstrates how to work with a function target.
 */

/** @example severity_level_example.c
 * Demonstrates how to work with the severity levels of logged events.
 */

/** @example stream_example.c
 * Demonstrates how to work with a stream target.
 */

/** @file
 * The main header file for the stumpless logging library. Unless you are
 * specifically trying to include ONLY required headers, it is best to simply
 * include this header to use stumpless. It will ensure that all available
 * features are declared, as well as take care of any ordering or conditional
 * includes that may be necessary on the target platform.
 *
 * If you do want to only include specific header files, you can use this file
 * as a template. Note that all headers are under the stumpless directory,
 * which must be in the include path.
 */

#ifndef __STUMPLESS_H
#define __STUMPLESS_H

#include <stumpless/config.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/facility.h>
#include <stumpless/filter.h>
#include <stumpless/generator.h>
#include <stumpless/id.h>
#include <stumpless/level/alert.h>
#include <stumpless/level/crit.h>
#include <stumpless/level/debug.h>
#include <stumpless/level/emerg.h>
#include <stumpless/level/err.h>
#include <stumpless/level/info.h>
#include <stumpless/level/notice.h>
#include <stumpless/level/trace.h>
#include <stumpless/level/warning.h>
#include <stumpless/log.h>
#include <stumpless/memory.h>
#include <stumpless/option.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/chain.h>
#include <stumpless/target/file.h>
#include <stumpless/target/function.h>
#include <stumpless/target/sqlite3.h>
#include <stumpless/target/stream.h>
#include <stumpless/version.h>
#include <stumpless/priority.h>

#ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/** @example journald_example.c
 * Demonstrates how to work with a journald target.
 */

#  include <stumpless/config/journald_supported.h>
#  include <stumpless/target/journald.h>
#endif

#ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
/** @example tcp_example.c
 * Demonstrates how to work with a network target with a TCP network endpoint.
 */

/** @example udp_example.c
 * Demonstrates how to work with a network target with a UDP network endpoint.
 */

#  include <stumpless/target/network.h>
#endif

#ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
/** @example socket_example.c
 * Demonstrates how to work with a socket target.
 */

#  include <stumpless/target/socket.h>
#endif

#ifdef STUMPLESS_SQLITE3_TARGETS_SUPPORTED
/** @example sqlite3_example.c
 * Demonstrates how to work with a sqlite3 target.
 *
 * @since release v2.2.0
 */
#endif

#ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
/** @example wel_example.c
 * Demonstrates how to work with a Windows Event Log target.
 */

#  include <stumpless/config/wel_supported.h>
#  include <stumpless/target/wel.h>
#  include <stumpless/windows/default_events.h>
#endif

#endif /* __STUMPLESS_H */
