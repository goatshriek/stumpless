/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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
 * Macro functions that log messages and entries at the informational level.
 *
 * These can be turned into no-ops at compile time by defining
 * STUMPLESS_DISABLE_INFO_LEVEL during build, or at least before inclusion of
 * this header (or stumpless.h).
 */

#ifndef __STUMPLESS_LEVEL_INFO_H
#  define __STUMPLESS_LEVEL_INFO_H

#  ifndef STUMPLESS_DISABLE_INFO_LEVEL
#    include <stumpless/severity.h>
#    include <stumpless/target.h>
#  endif

/**
 * Logs a message to the current target with informational severity.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. If it is disabled, then this function is
 * removed at compile time and will have no effect. Otherwise, it is equivalent
 * to a call to stumpless_add_log with the provided message and calculated
 * priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with info level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_INFO, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stumplog_i instead.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_INFO_LEVEL
#    define stump_i( ... ) ( 0 )
#  else
#    define stump_i( ... )                                                     \
stumpless_add_log( stumpless_get_current_target(  ),                           \
                   STUMPLESS_SEVERITY_INFO | STUMPLESS_DEFAULT_FACILITY,       \
                   __VA_ARGS__ )
#  endif

/**
 * Adds an entry to a given target with informational severity.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. If it is disabled, then this function is
 * removed at compile time and will have no effect. Otherwise, it is equivalent
 * to a call to stumplog with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with info level calls disabled.
 *
 * This call does not override the severity of the entry itself. Rather, it is
 * intended to allow logging calls to be removed at compile time if the severity
 * is known ahead of time.
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
#  ifdef STUMPLESS_DISABLE_INFO_LEVEL
#    define stump_i_entry( target, entry ) ( 0 )
#  else
#    define stump_i_entry( target, entry )                                     \
stumpless_add_entry( ( target ), ( entry ) )
#  endif

/**
 * Adds a message to a given target with the specified priority.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. If it is disabled, then this function is
 * removed at compile time and will have no effect. Otherwise, it is equivalent
 * to a call to stumplog with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with info level calls disabled.
 *
 * @param target The target to send the entry to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_INFO_LEVEL
#    define stump_i_log( target, priority, ... ) ( 0 )
#  else
#    define stump_i_log( target, priority, ... )                               \
stumpless_add_log( ( target ), ( priority ), __VA_ARGS__ )
#endif

/**
 * Adds a message to a given target with informational severity.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. If it is disabled, then this function is
 * removed at compile time and will have no effect. Otherwise, it is equivalent
 * to a call to stumpless_add_log with the provided message and calculated
 * priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with info level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_INFO, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stump_i_log instead.
 *
 * @param target The target to send the entry to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_INFO_LEVEL
#    define stump_i_message( target, ... ) ( 0 )
#  else
#    define stump_i_message( target, ... )                                     \
stumpless_add_log( ( target ),                                                 \
                   STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_INFO,       \
                   __VA_ARGS__ )
#  endif

/**
 * Adds a message to the current target with the specified priority.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. If it is disabled, then this function is
 * removed at compile time and will have no effect. Otherwise, it is equivalent
 * to a call to stumplog with the provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with info level calls disabled.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 */
#  ifdef STUMPLESS_DISABLE_INFO_LEVEL
#    define stumplog_i( priority, ... ) ( ( void ) 0 )
#  else
#    define stumplog_i( priority, ... )                                        \
stumplog( ( priority ), __VA_ARGS__ )
#  endif

#endif /* __STUMPLESS_LEVEL_INFO_H */
