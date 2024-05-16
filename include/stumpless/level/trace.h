/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021-2024 Joel E. Anderson
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
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 * Macro functions that log messages and entries for source tracing. This is
 * equivalent to a debug log severity with the addition of structured data
 * fields that specify the source file and line of the call. While it shares
 * the same severity as debug logs, it is considered below them and can be
 * disabled separately from the debug level.
 *
 * These can be turned into no-ops at compile time by defining
 * STUMPLESS_DISABLE_TRACE_LEVEL during build, or at least before inclusion of
 * this header (or stumpless.h).
 */

#ifndef __STUMPLESS_LEVEL_TRACE_H
#define __STUMPLESS_LEVEL_TRACE_H

#include <stumpless/level/mask.h>

#ifndef STUMPLESS_DISABLE_TRACE_LEVEL
#  include <stumpless/config.h>
#  include <stumpless/log.h>
#  include <stumpless/severity.h>
#  include <stumpless/target.h>
#endif

/**
 * Logs a message to the current target with debug severity, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build.
 * If it is disabled, then this function is removed at compile time and will
 * have no effect. Otherwise, it is equivalent to a call to
 * \ref stumpless_add_log with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_TRACE, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use \ref stumplog_t instead.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \ref stump_t_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @param ... The message to log, optionally along with the values for any
 * format specifiers valid in \c printf. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t( ... ) ( 0 )
#else
#  define stump_t( ... )                                                       \
stumpless_trace_log( stumpless_get_current_target(  ),                         \
                     STUMPLESS_SEVERITY_DEBUG | STUMPLESS_DEFAULT_FACILITY,    \
                     __FILE__,                                                 \
                     __LINE__,                                                 \
                     __func__,                                                 \
                     __VA_ARGS__ )
#endif

/**
 * Logs a message to the current target with debug severity, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to \ref stumpless_add_log
 * with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_TRACE, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stumplog_em instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @since release v2.1.0.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_str( message ) ( 0 )
#else
#  define stump_t_str( message )                                               \
stumpless_trace_log_str( stumpless_get_current_target(  ),                     \
                         STUMPLESS_SEVERITY_DEBUG | STUMPLESS_DEFAULT_FACILITY,\
                         __FILE__,                                             \
                         __LINE__,                                             \
                         __func__,                                             \
                         ( message ) )
#endif

/**
 * Adds an entry to a given target with debug severity, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to \ref stumpless_add_entry
 * with the provided target and entry.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * This call does not override the severity of the entry itself. Rather, it is
 * intended to allow logging calls to be removed at compile time if the severity
 * is known ahead of time.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked.
 *
 * @param target The target to send the entry to.
 *
 * @param entry The entry to send to the target.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_entry( target, entry ) ( 0 )
#else
#  define stump_t_entry( target, entry )                                       \
stumpless_trace_entry( ( target ), ( entry ), __FILE__, __LINE__, __func__ )
#endif

/**
 * Adds a message to a given target with the specified priority, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to stumplog with the
 * provided message and priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \ref stump_t_log_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @param target The target to send the entry to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param ... The message to log, optionally along with the values for any
 * format specifiers valid in \c printf. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_log( target, priority, ... ) ( 0 )
#else
#  define stump_t_log( target, priority, ... )                                 \
stumpless_trace_log( ( target ),                                               \
                     ( priority ),                                             \
                     __FILE__,                                                 \
                     __LINE__,                                                 \
                     __func__,                                                 \
                     __VA_ARGS__ )
#endif

/**
 * Adds a message to a given target with the specified priority, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to
 * \ref stump_t_log_str with the provided target, message, and
 * priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @since release v2.1.0.
 *
 * @param target The target to send the entry to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_log_str( target, priority, message ) ( 0 )
#else
#  define stump_t_log_str( target, priority, message )                         \
stumpless_trace_log_str( ( target ),                                           \
                         ( priority ),                                         \
                         __FILE__,                                             \
                         __LINE__,                                             \
                         __func__,                                             \
                         ( message ) )
#endif

/**
 * Adds a message to a given target with trace severity, along with the
 * file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to \ref stumpless_add_log
 * with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_TRACE, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stump_t_log instead.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \ref stump_t_message_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @param target The target to send the entry to.
 *
 * @param ... The message to log, optionally along with the values for any
 * format specifiers valid in \c printf. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_message( target, ... ) ( 0 )
#else
#  define stump_t_message( target, ... )                                       \
stumpless_trace_log( ( target ),                                               \
                     STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_DEBUG,    \
                     __FILE__,                                                 \
                     __LINE__,                                                 \
                     __func__,                                                 \
                     __VA_ARGS__ )
#endif

/**
 * Adds a message to a given target with debug severity. The entry has a
 * structured data element added to it with the file, line, and function of
 * the invocation specified.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build.
 * If it is disabled, then this function is removed at compile time and will
 * have no effect. Otherwise, it is equivalent to a call to
 * \ref stumpless_add_log_str with the provided target and message.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_TRACE, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use \ref stump_t_log instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @since release v2.1.0.
 *
 * @param target The target to send the entry to.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stump_t_message_str( target, message ) ( 0 )
#else
#  define stump_t_message_str( target, message )                               \
stumpless_trace_log_str( ( target ),                                           \
                         STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_DEBUG,\
                         __FILE__,                                             \
                         __LINE__,                                             \
                         __func__,                                             \
                         ( message ) )
#endif

/**
 * Adds a message to the current target with the specified priority, along with
 * the file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to \ref stumplog with the
 * provided priority and message.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \ref stumplog_t_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param ... The message to log, optionally along with the values for any
 * format specifiers valid in \c printf. This must be a valid UTF-8 string in
 * shortest form.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stumplog_t( priority, ... ) ( ( void ) 0 )
#else
#  define stumplog_t( priority, ... )                                          \
stumplog_trace( ( priority ), __FILE__, __LINE__, __func__, __VA_ARGS__ )
#endif

/**
 * Adds a message to the current target with the specified priority, along with
 * the file, line, and function of the invocation specified in a structured data
 * element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_TRACE_LEVEL has been defined during build. If
 * it is disabled, then this function is removed at compile time and will have
 * no effect. Otherwise, it is equivalent to a call to \ref stumplog_str with
 * the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with trace level calls disabled.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder).
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access. It also may make memory
 * allocation calls to create internal cached structures, and memory allocation
 * may not be signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked
 * and the potential for memory allocation.
 *
 * @since release v2.1.0.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 */
#ifdef STUMPLESS_DISABLE_TRACE_LEVEL
#  define stumplog_t_str( priority, message ) ( ( void ) 0 )
#else
#  define stumplog_t_str( priority, message )                                  \
stumplog_trace_str( ( priority ), __FILE__, __LINE__, __func__, ( message ) )
#endif

#endif /* __STUMPLESS_LEVEL_TRACE_H */
