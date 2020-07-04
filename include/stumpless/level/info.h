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
 * Macro functinons that log messages and entries at the informational level.
 *
 * These can be turned into no-ops at compile time by defining
 * STUMPLESS_DISABLE_INFO_LEVEL during build, or at least before inclusion of
 * this header (or stumpless.h).
 */

#ifndef __STUMPLESS_LEVEL_INFO_H
#  define __STUMPLESS_LEVEL_INFO_H

#  ifdef STUMPLESS_DISABLE_INFO_LEVEL

/**
 * A placeholder for a logging call of informational severity.
 *
 * This function has been disabled during the build of this library, and
 * will therefore be removed during compilation. Use ENABLE_INFO_LOGS during
 * build to enable this function.
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
 * appropriately.
 */
#    define stump_i(...) ( ( void ) 0 )

/**
 *
 */
#    define stump_i_entry(TARGET, ENTRY) ( ( void ) 0 )

/**
 *
 */
#    define stumplog_i(PRIORITY, ...) ( ( void ) 0 )

#  else

/**
 * Logs a message to the default target with informational severity.
 *
 * This function will be removed at compile time if STUMPLESS_DISABLE_INFO_LEVEL
 * has been defined during build. It is enabled by default and has been enabled
 * in this build. If it is not enabled, then this function is removed at compile
 * time and will have no effect. If it is enabled, then it is equivalent to a
 * call to stump with the same parameters.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_INFO, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different prival, then
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
 * appropriately.
 */
#    define stump_i(...) stump(__VA_ARGS__)

/**
 * Adds an entry to a given target with informational severity.
 */
#    define stump_i_entry(TARGET, ENTRY) stumpless_add_entry( (TARGET), (ENTRY) )

/**
 * Adds a message to a given target with the specified priority.
 */
#    define stump_i_log(TARGET, PRIORITY, ...) stumpless_add_entry( (TARGET), (PRIORITY), __VA_ARGS__ )

/**
 * Adds a message to a given target with informational severity.
 */
#    define stump_i_message(TARGET, ...) stumpless_add_entry( (TARGET), __VA_ARGS__ )

/**
 * Adds a message to the default target with the specified priority.
 */
#    define stumplog_i(PRIORITY, ...) stumplog( (PRIORITY), __VA_ARGS__)

#  endif

#endif /* __STUMPLESS_LEVEL_INFO_H */
