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

/** @file
 * Convenience functions for creating and writing simple log entries.
 */

#ifndef __STUMPLESS_LOG_H
#  define __STUMPLESS_LOG_H

#  include <stdarg.h>
#  include <stumpless/config.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Logs a message to the default target.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * stump_str() instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int stump( const char *message, ... );

/**
 * Logs a message to the default target.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @since release v2.1.0
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int stump_str( const char *message );

/**
 * Logs a message to the default target, along with the file, line, and function
 * information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stump_trace_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @since release v2.1.0
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stump_trace( const char *file,
             int line,
             const char *func,
             const char *message,
             ... );

/**
 * Logs a message to the default target, along with the file, line, and function
 * information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @since release v2.1.0
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stump_trace_str( const char *file,
                 int line,
                 const char *func,
                 const char *message );

/**
 * Logs a message to the current target with the given priority.
 *
 * This function can serve as a replacement for the traditional \c syslog
 * function.
 *
 * For detailed information on what the current target will be for a given
 * system, check the stumpless_get_current_target() function documentation.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumplog_str instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumplog( int priority, const char *message, ... );

/**
 * Sets the log mask of the current target.
 *
 * The mask is a bit field of severities that this target will allow if the
 * default mask-based filter is in use. These can be formed and checked using
 * the STUMPLESS_SEVERITY_MASK and STUMPLESS_SEVERITY_MASK_UPTO macros, and
 * combining them using bitwise or operations.
 *
 * This function can serve as a replacement for the traditional \c setlogmask
 * function.
 *
 * For detailed information on what the current target will be for a given
 * system, check the stumpless_get_current_target() function documentation.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param mask The mask to use with the target.
 *
 * @return The previous mask that was in use on the current target. If the
 * mask could not be retrieved, 0 is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumplog_set_mask( int mask );

/**
 * Logs a message to the current target with the given priority.
 *
 * This function can serve as a replacement for the traditional \c syslog
 * function.
 *
 * For detailed information on what the current target will be for a given
 * system, check the stumpless_get_current_target() function documentation.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @since release v2.1.0
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumplog_str( int priority, const char *message );

/**
 * Logs a message to the default target with the given priority, along with the
 * file, line, and function information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function can serve as a replacement for the traditional \c syslog
 * function.
 *
 * For detailed information on what the default target will be for a given
 * system, check the stumpless_get_default_target() function documentation.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * stumplog_trace_str() instead.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param file The name of the source file the entry should be tied to.
 *
 * @param line The line in the source file that the entry should be tied
 * to.
 *
 * @param func The name of the function that the entry should be tied to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumplog_trace( int priority,
                const char *file,
                int line,
                const char *func,
                const char *message,
                ... );

/**
 * Logs a message to the default target with the given priority, along with the
 * file, line, and function information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function can serve as a replacement for the traditional \c syslog
 * function.
 *
 * For detailed information on what the default target will be for a given
 * system, check the stumpless_get_default_target() function documentation.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @since release v2.1.0
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param file The name of the source file the entry should be tied to.
 *
 * @param line The line in the source file that the entry should be tied
 * to.
 *
 * @param func The name of the function that the entry should be tied to.
 *
 * @param message The message to log. This must be a valid UTF-8 string in
 * shortest form.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumplog_trace_str( int priority,
                    const char *file,
                    int line,
                    const char *func,
                    const char *message );

/**
 * Logs a message to the default target.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call it.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
vstump( const char *message, va_list subs );

/**
 * Logs a message to the default target, along with the file, line, and function
 * information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call it.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
vstump_trace( const char *file,
              int line,
              const char *func,
              const char *message,
              va_list subs );

/**
 * Logs a message to the default target with the given priority. Can serve as
 * a replacement for the traditional \c vsyslog function.
 *
 * For detailed information on what the default target will be for a given
 * system, check the stumpless_get_default_target() function documentation.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call it.
 */
STUMPLESS_PUBLIC_FUNCTION
void
vstumplog( int priority, const char *message, va_list subs );

/**
 * Logs a message to the default target with the given priority, along with the
 * file, line, and function information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * This function can serve as a replacement for the traditional \c vsyslog
 * function.
 *
 * For detailed information on what the default target will be for a given
 * system, check the stumpless_get_default_target() function documentation.
 *
 * **Thread Safety: MT-Safe env locale**
 * This function is thread safe. Different target types handle thread safety
 * differently, as some require per-target locks and others can rely on system
 * libraries to log safely, but all targets support thread safe logging in some
 * manner. For target-specific information on how thread safety is supported and
 * whether AS or AC safety can be assumed, refer to the documentation for the
 * target's header file (in the `stumpless/target` include folder). For all
 * targets, the environment variables and locale will be used during some of the
 * string formatting of the message.
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
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call it.
 */
STUMPLESS_PUBLIC_FUNCTION
void
vstumplog_trace( int priority,
                 const char *file,
                 int line,
                 const char *func,
                 const char *message,
                 va_list subs );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_LOG_H */
