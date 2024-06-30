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

/** @mainpage Stumpless
 *
 * Stumpless is a C logging library built for high performance and a rich
 * feature set.
 *
 * \section basic-usage Basic Usage
 * The simplest way to get started is to use the `stumplog` function as a direct
 * replacement for the standard library's `syslog` function:
 *
 * \code{.c}
 * // if you're used to doing this:
 * syslog( LOG_INFO | LOG_USER, "My message #%d", count );
 *
 * // then you can start by changing to this:
 * stumplog( LOG_INFO | LOG_USER, "My message #%d", count );
 * \endcode
 *
 * If you haven't opened a target, this will log messages to the default target
 * for the platform: on Linux this is \c /dev/log, on a Mac system this will be
 * \c /var/run/syslog, and on a Windows machine it is the Windows Event Log. If
 * you open a target or even a few before calling `stumplog`, then logs will be
 * sent to the most recently opened target.
 *
 * If you want an even shorter function call, you can use the stump() function
 * to send a message to the current target. You can also use format specifiers
 * just as you would with \c printf.
 *
 * \code{.c}
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode
 *
 * If you don't need format specifiers, use one of the \c _str variants such as
 * stump_str(): it's both faster and safer!
 *
 * \code{.c}
 * stump_str( "Login failure! See structured data for info." );
 * \endcode
 *
 * If you want to open a specific target rather than using the default, then
 * just open the one you need and start sending messages. For example, to log to
 * a file named \c example.log
 *
 * \code{.c}
 * target = stumpless_open_file_target( "example.log" );
 *
 * // uses the last opened target by default
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode
 *
 * Sending messages over the network to something like Splunk or rsyslog is just
 * as easy:
 *
 * \code{.c}
 * target = stumpless_open_udp4_target( "send-to-splunk-example",
 *                                      "mylogserver.com" ); // or use an IP
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode
 *
 * If you have multiple targets, you can send messages to a chosen target like
 * this:
 *
 * \code{.c}
 * stumpless_add_message( target,
 *                        "Login attempt failure #%d for user %s",
 *                        count,
 *                        username );
 * \endcode
 *
 * \section severity-shorthand Severity Shorthand
 * It's common to specify severity levels directly in logging calls, so
 * stumpless provides some macro functions to make this less verbose and more
 * efficient. For example, to log messages with a severity of INFO, you can do
 * this:
 *
 * \code{.c}
 * stump_i( "this gets logged as an info message" );
 * \endcode
 *
 * And if you want to also see source file, line number, and function name info
 * in each message you can use stump_t() (the 't' is for trace):
 *
 * \code{.c}
 * stump_t( "this includes source info" );
 * \endcode
 *
 * Using these functions has the added benefit that they can be removed at
 * compile time by simply defining the proper \c STUMPLESS_ENABLE_UPTO or
 * \c STUMPLESS_DISABLE_DOWNTO symbols. This makes it easy to change logging
 * levels between builds, for example to have prod and debug versions without
 * differences in their source code.
 *
 * \code{.c}
 * // be sure to define this before stumpless.h gets included
 * #define STUMPLESS_ENABLE_UPTO_INFO
 *
 * // ...
 *
 * // this log will go through just fine
 * stump_i( "I'm doing that thing you asked" );
 *
 * // this debugging message is completely removed: no runtime impact whatsoever
 * stump_d( "DEBUG info: %d, %d, %s", thing_1, thing_2, stringy_thingy );
 * \endcode
 *
 * Check out the headers in the stumpless/level include directory named after
 * a severity level such as \ref alert.h to see the full list of severity
 * shorthand functions, or \ref severity_level_example.c to see a
 * complete program in action.
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
#include <stumpless/prival.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/file.h>
#include <stumpless/target/function.h>
#include <stumpless/target/sqlite3.h>
#include <stumpless/target/stream.h>
#include <stumpless/version.h>

#ifdef STUMPLESS_CHAIN_TARGETS_SUPPORTED
/** @example chain_example.c
 * Demonstrates how to work with a chain target.
 */

#  include <stumpless/target/chain.h>
#endif

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
