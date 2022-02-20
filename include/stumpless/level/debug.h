/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
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
 * Macro functions that log messages and entries at the debug level.
 *
 * These can be turned into no-ops at compile time by defining
 * STUMPLESS_DISABLE_DEBUG_LEVEL during build, or at least before inclusion of
 * this header (or stumpless.h).
 */

#ifndef __STUMPLESS_LEVEL_DEBUG_H
#  define __STUMPLESS_LEVEL_DEBUG_H

#  include <stumpless/level/mask.h>

#  ifndef STUMPLESS_DISABLE_DEBUG_LEVEL
#    include <stumpless/config.h>
#    include <stumpless/severity.h>
#    include <stumpless/target.h>
#  endif

/**
 * Logs a message to the current target with debug severity.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumpless_add_log with the
 * provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_DEBUG, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stumplog_d instead.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stump_d_str instead.
 *
 * **Thread Safety: MT-Safe**
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
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d( ... ) ( 0 )
#  else
#    define stump_d( ... )                                                     \
stumpless_add_log( stumpless_get_current_target(  ),                           \
                   STUMPLESS_SEVERITY_DEBUG | STUMPLESS_DEFAULT_FACILITY,      \
                   __VA_ARGS__ )
#  endif

/**
 * Logs a message to the current target with debug severity.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumpless_add_log with the
 * provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_DEBUG, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stumplog_d instead.
 *
 * **Thread Safety: MT-Safe**
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
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_str( message ) ( 0 )
#  else
#    define stump_d_str( message )                                             \
stumpless_add_log_str( stumpless_get_current_target(  ),                       \
                       STUMPLESS_SEVERITY_DEBUG | STUMPLESS_DEFAULT_FACILITY,  \
                       ( message ) )
#  endif

/**
 * Adds an entry to a given target with debug severity.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumplog with the provided
 * message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * This call does not override the severity of the entry itself. Rather, it is
 * intended to allow logging calls to be removed at compile time if the severity
 * is known ahead of time.
 *
 * **Thread Safety: MT-Safe**
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
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_entry( target, entry ) ( 0 )
#  else
#    define stump_d_entry( target, entry )                                     \
stumpless_add_entry( ( target ), ( entry ) )
#  endif

/**
 * Adds a message to a given target with the specified priority.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumplog with the provided
 * message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stump_d_log_str instead.
 *
 * **Thread Safety: MT-Safe**
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
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_log( target, priority, ... ) ( 0 )
#  else
#    define stump_d_log( target, priority, ... )                               \
stumpless_add_log( ( target ), ( priority ), __VA_ARGS__ )
#endif

/**
 * Adds a message to a given target with the specified priority.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumplog with the provided
 * message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * **Thread Safety: MT-Safe**
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
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_log_str( target, priority, message ) ( 0 )
#  else
#    define stump_d_log_str( target, priority, message )                       \
stumpless_add_log_str( ( target ), ( priority ), ( message ) )
#endif

/**
 * Adds a message to a given target with debug severity.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumpless_add_log with the
 * provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_DEBUG, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stump_d_log instead.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stump_d_message_str instead.
 *
 * **Thread Safety: MT-Safe**
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
 * appropriately. If the function is disabled then the effective return value
 * is zero, although a return value of zero does not guarantee that this
 * function is disabled.
 */
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_message( target, ... ) ( 0 )
#  else
#    define stump_d_message( target, ... )                                     \
stumpless_add_log( ( target ),                                                 \
                   STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_DEBUG,      \
                   __VA_ARGS__ )
#  endif

/**
 * Adds a message to a given target with debug severity.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumpless_add_log with the
 * provided message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * This function will log the given message with a severity of
 * STUMPLESS_SEVERITY_DEBUG, and the facility defined by the
 * STUMPLESS_DEFAULT_FACILITY. If you wish to specify a different priority, then
 * you will need to use stump_d_log instead.
 *
 * **Thread Safety: MT-Safe**
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
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stump_d_message_str( target, message ) ( 0 )
#  else
#    define stump_d_message_str( target, message )                             \
stumpless_add_log_str( ( target ),                                             \
                       STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_DEBUG,  \
                       ( message ) )
#  endif

/**
 * Adds a message to the current target with the specified priority.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumplog with the provided
 * message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumplog_d_str instead.
 *
 * **Thread Safety: MT-Safe**
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
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given.
 */
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stumplog_d( priority, ... ) ( ( void ) 0 )
#  else
#    define stumplog_d( priority, ... ) stumplog( ( priority ), __VA_ARGS__ )
#  endif

/**
 * Adds a message to the current target with the specified priority.
 *
 * This function will be removed at compile time if
 * STUMPLESS_DISABLE_DEBUG_LEVEL has been defined during build. If it is
 * disabled, then this function is removed at compile time and will have no
 * effect. Otherwise, it is equivalent to a call to stumplog with the provided
 * message and calculated priority.
 *
 * Note that if this function is disabled, then the arguments will not be
 * evaluated, meaning that any side effects will not happen. Be sure that any
 * side effects you rely on will not cause problems if they are left out during
 * a build with debug level calls disabled.
 *
 * **Thread Safety: MT-Safe**
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
#  ifdef STUMPLESS_DISABLE_DEBUG_LEVEL
#    define stumplog_d_str( priority, message ) ( ( void ) 0 )
#  else
#    define stumplog_d_str( priority, message )                                \
stumplog_str( ( priority ), ( message ) )
#  endif

#endif /* __STUMPLESS_LEVEL_DEBUG_H */
