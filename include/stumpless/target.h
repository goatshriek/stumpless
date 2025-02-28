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

/** @dir target
 * Header files for target types provided by the library.
 */

/** @file
 * General types and functions for working with all targets.
 */

#ifndef __STUMPLESS_TARGET_H
#define __STUMPLESS_TARGET_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/id.h>
#include <stumpless/generator.h>

/** The name of the default target. */
#define STUMPLESS_DEFAULT_TARGET_NAME "stumpless-default"

#ifdef __cplusplus
extern "C" {
#endif

/** write to a character buffer */
#define STUMPLESS_BUFFER_TARGET_VALUE 0

/** write to a file */
#define STUMPLESS_FILE_TARGET_VALUE 1

/** call a custom function */
#define STUMPLESS_FUNCTION_TARGET_VALUE 2

/** send to the systemd journald service */
#define STUMPLESS_JOURNALD_TARGET_VALUE 3

/** send to a network endpoint */
#define STUMPLESS_NETWORK_TARGET_VALUE 4

/** write to a Unix socket */
#define STUMPLESS_SOCKET_TARGET_VALUE 5

/** write to a FILE stream */
#define STUMPLESS_STREAM_TARGET_VALUE 6

/** add to the Windows Event Log */
#define STUMPLESS_WINDOWS_EVENT_LOG_TARGET_VALUE 7

/** add to a SQLite3 database */
#define STUMPLESS_SQLITE3_TARGET_VALUE 8

/**
 * write to a series of targets
 *
 * @since release v2.2.0
 */
#define STUMPLESS_CHAIN_TARGET_VALUE 9

/**
 * A macro function that runs the provided action once for each target_type,
 * providing the symbol and value. The action must take two arguments, the
 * first being the symbol name of the target_type, and the second the numeric
 * value of the target_type.
 */
#define STUMPLESS_FOREACH_TARGET_TYPE( ACTION )\
ACTION( STUMPLESS_BUFFER_TARGET, STUMPLESS_BUFFER_TARGET_VALUE )\
ACTION( STUMPLESS_FILE_TARGET, STUMPLESS_FILE_TARGET_VALUE )\
ACTION( STUMPLESS_FUNCTION_TARGET, STUMPLESS_FUNCTION_TARGET_VALUE )\
ACTION( STUMPLESS_JOURNALD_TARGET, STUMPLESS_JOURNALD_TARGET_VALUE )\
ACTION( STUMPLESS_NETWORK_TARGET, STUMPLESS_NETWORK_TARGET_VALUE )\
ACTION( STUMPLESS_SOCKET_TARGET, STUMPLESS_SOCKET_TARGET_VALUE )\
ACTION( STUMPLESS_STREAM_TARGET, STUMPLESS_STREAM_TARGET_VALUE )\
ACTION( STUMPLESS_WINDOWS_EVENT_LOG_TARGET, STUMPLESS_WINDOWS_EVENT_LOG_TARGET_VALUE )\
ACTION( STUMPLESS_SQLITE3_TARGET, STUMPLESS_SQLITE3_TARGET_VALUE )\
ACTION( STUMPLESS_CHAIN_TARGET, STUMPLESS_CHAIN_TARGET_VALUE )

/**
 * Types of targets that may be created.
 */
enum stumpless_target_type {
  STUMPLESS_FOREACH_TARGET_TYPE( STUMPLESS_GENERATE_ENUM )
};

// needed so that we can define the filter function type before targets
struct stumpless_target;

/**
 * A function that determines whether a given entry should be sent to a given
 * target.
 *
 * The two parameters are guaranteed not to be NULL whenever a filter function
 * is called by the library itself, and so NULL checks are not necessary.
 *
 * Note that this function does not actually add the entry to the target, but
 * only evaluates whether or not it should be sent.
 *
 * The safety attributes (thread, async, async-cancel) of a filter function
 * come into play whenever an entry is sent to a target via stumpless_add_entry
 * or another function that results in a call to this. If the function is not
 * safe in conditions where the add function is, the target will need to be
 * treated as though it is also unsafe in these conditions when entries are
 * passed to it.
 *
 * @param target The target that the entry will be sent to if it passes. Will
 * not be NULL when called during logging.
 *
 * @param entry The entry that is being submitted to the target. Will not be
 * NULL when called during logging.
 *
 * @return true if the entry should be sent to the target, false if not.
 */
typedef bool ( *stumpless_filter_func_t )(
  const struct stumpless_target *target,
  const struct stumpless_entry *entry );

/**
 * A target that log entries can be sent to.
 */
struct stumpless_target {
/** A unique identifier of this target. */
  stumpless_id_t id;
/**
 * The type of this target. The type of a target will not change over the
 * lifetime of the target.
 */
  enum stumpless_target_type type;
/**
 * The name of this target.
 *
 * For some target types, the name may have more significcance than a simple
 * identifier. For example, the name of a file target will be the file that the
 * target writes to.
 *
 * The name of the target will be NULL-terminated.
 */
  char *name;
/** The number of characters in the name. */
  size_t name_length;
/** A bitwise or of all options set on the target. */
  int options;
/** The prival used for messages without a severity or facility provided. */
  int default_prival;
/**
 * The app name used for messages without one provided.
 *
 * The default app name is not NULL-terminated.
 */
  char default_app_name[STUMPLESS_MAX_APP_NAME_LENGTH];
/** The number of characters in the default app name. */
  size_t default_app_name_length;
/**
 * The msgid used for messages without one provided.
 *
 * The default msgid is not NULL-terminated.
 */
  char default_msgid[STUMPLESS_MAX_MSGID_LENGTH];
/** The number of characters in the default msgid. */
  size_t default_msgid_length;
/** The log mask for the target. Used by the default target filter. */
  int mask;
/**
 * A filter function used to determine if a given entry should be processed by
 * this target or ignored. If this is NULL, then all entries sent to the target
 * are accepted. By default targets use the stumpless_mask_filter which filters
 * messages based on the severity bits in the mask of the target.
 *
 * @since release v2.1.0
 */
  stumpless_filter_func_t filter;
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * A pointer to a mutex which protects all target fields. The exact type of
 * this mutex depends on the build.
 */
  void *mutex;
#endif
};

/**
 * Adds an entry into a given target. This is the primary logging function of
 * stumpless; all other logging functions call this one after performing any
 * setup specific to themselves.
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
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked.
 *
 * @param target The target to send the message to.
 *
 * @param entry The entry to send to the target.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_add_entry( struct stumpless_target *target,
                     const struct stumpless_entry *entry );

/**
 * Adds a log message with a priority to a given target.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_add_log_str instead.
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
 * @param target The target to send the message to.
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
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_add_log( struct stumpless_target *target,
                   int priority,
                   const char *message,
                   ... );

/**
 * Adds a log message with a priority to a given target.
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
 * @param target The target to send the message to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
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
stumpless_add_log_str( struct stumpless_target *target,
                       int priority,
                       const char *message );

/**
 * Adds a message to a given target.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_add_message_str instead.
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
 * @param target The target to send the message to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This may be NULL, in which case an event with
 * no message is logged. This must be a valid UTF-8 string in shortest form.
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
stumpless_add_message( struct stumpless_target *target,
                       const char *message,
                       ... );

/**
 * Adds a string message to a given target.
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
 * @param target The target to send the message to.
 *
 * @param message The message to log. This may be NULL, in which case an event
 * with no message is logged. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_add_message_str( struct stumpless_target *target,
                           const char *message );

/**
 * Closes a target.
 *
 * Targets that can be closed in multiple ways will be closed in the most
 * complete way possible. Specifically, SQLite3 targets will have the underlying
 * database connection closed as well, and chain targets will have all targets
 * in them closed.
 *
 * This function can be used when you'd like to avoid checking the type of the
 * target and then calling the appropriate close function. Note that use of this
 * doesn't actually avoid the check - it just does the check on your behalf. It
 * is more efficient to call the specific close function if you know the type of
 * the target.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @param target The target to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_target( struct stumpless_target *target );

/*
 * Gets the current console stream where logs are written to.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic variables are used to store and
 * retrieve the console stream.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be ansynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @return The current stream where messages are logged to on setting the
 * the CONS option.
 */
STUMPLESS_PUBLIC_FUNCTION
FILE *
stumpless_get_cons_stream( void );

/**
 * Gets the current target.
 *
 * The current target is either the last target that was opened, set by a call
 * to stumpless_set_current_target(), or the default target if neither of the
 * former exists.
 *
 * The current target will still be the last target that was opened even if the
 * target was opened with STUMPLESS_OPTION_ODELAY option and is not yet
 * connected for logging.
 *
 * If the target that is designated as the current target is closed, then the
 * current target will be reset to the default target until another target is
 * opened.
 *
 * Be careful not to confuse this target with the default target, which is the
 * target used when no suitable current target exists. While these may be the
 * same in some cases, they will not always be.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic operations are used to work with the
 * default target.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the
 * possible use of memory management functions to create the default target.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @return The current target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_get_current_target( void );

/**
 * Gets the options to be used while initializing a target.
 *
 * If no options are set for atomic variable default_option, it will default
 * to 0.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic operations are used to work with the
 * default option.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers as it only consists of
 * an atomic read.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled, as it only consists of an atomic read.
 *
 * @return Value store in atomic variable default_option
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_get_default_options( void );

/**
 * Gets the default facility of a target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param target The target to get the facility from..
 *
 * @return The default facility if no error is encountered. If an error is
 * encountered, then -1 is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_get_default_facility( const struct stumpless_target *target );

/**
 * Gets the default target.
 *
 * The default target is opened when a logging call is made with no target
 * open. It will not be opened until either this happens or a call to this
 * function is made. It will not be closed until a call to stumpless_free_all()
 * is made. It should not be closed manually outside of the free all function.
 *
 * Be careful not to confuse this target with the current target, which is the
 * last target opened or set via stumpless_set_current_target(). While these
 * will return the same target in some cases, such as if they are called before
 * opening any targets, they are not equivalent.
 *
 * The default target type will change depending on the configuration of the
 * system configuration. If Windows Event Log targets are supported, then the
 * default target will log to an event log named
 * \c STUMPLESS_DEFAULT_TARGET_NAME. If Windows Event Log targets are not
 * supported and socket targets are, then the default target will point at the
 * socket named in STUMPLESS_DEFAULT_SOCKET, which will be /var/run/syslog if
 * it existed at build time, or else /dev/log. If neither of these target types
 * are supported then a file target is opened to log to the file named in
 * \c STUMPLESS_DEFAULT_FILE.
 *
 * The default target will not have any options set, and will have a default
 * facility of \c STUMPLESS_FACILITY_USER. These settings may be modified by
 * calling the appropriate modifiers on the target after retrieving it with this
 * function.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic operations are used to work with the
 * default target.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the
 * possible use of memory management functions to create the default target.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @return The default target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_get_default_target( void );

/**
 * Gets a given option of a target.
 *
 * While the returned value is the option if it is set, code can also simply
 * check the truth value of the return to see if the provided option is set.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param target The target to get the option from.
 *
 * @param option The option to check the target for.
 *
 * @return The option if it is set on the target. If the option is not set,
 * then zero is returned. If an error is encountered, then zero is returned
 * and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_get_option( const struct stumpless_target *target, int option );

/**
 * Returns the default app name of the given target. The character buffer must
 * be freed by the caller when it is no longer needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * target with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.0.0
 *
 * @param target The target to get the app name from.
 *
 * @return The default app name of the target, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_target_default_app_name( const struct stumpless_target *target );

/**
 * Returns the default msgid of the given target. The character buffer must be
 * freed by the caller when it is no longer needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * target with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.0.0
 *
 * @param target The target to get the msgid from.
 *
 * @return The default msgid of the target, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_target_default_msgid( const struct stumpless_target *target );

/**
 * Returns the current filter used by the given target to determine if entries
 * should be allowed through it.
 *
 * Note that NULL is a valid return value from this function, indicating that
 * the target does not currently have a filter set. In order to detect an
 * error condition, use the `stumpless_has_error` function instead.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param target The target to get the filter from.
 *
 * @return The filter function in use by the target, or NULL if an error is
 * encountered. If an error is encountered, an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
stumpless_filter_func_t
stumpless_get_target_filter( const struct stumpless_target *target );

/**
 * Gets the log mask of a target.
 *
 * The mask is a bit field of severities that this target will allow if the
 * default mask-based filter is in use. These can be formed and checked using
 * the STUMPLESS_SEVERITY_MASK and STUMPLESS_SEVERITY_MASK_UPTO macros, and
 * combining them using bitwise or operations.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param target The target to get the mask from.
 *
 * @return The current mask of the target. If an error is encountered, then
 * zero is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_get_target_mask( const struct stumpless_target *target );

/**
 * Returns the name of the given target. The character buffer must be freed by
 * the caller when it is no longer needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * target with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.0.0
 *
 * @param target The target to get the name from.
 *
 * @return The name of target, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_target_name( const struct stumpless_target *target );

/**
 * Opens a target that has already been created and configured.
 *
 * Targets that have been created using the \c stumpless_new_*_target family of
 * functions need to be opened once they have been configured with all of the
 * desired parameters, or if a previous change caused them to pause.
 *
 * If the provided target has not had all mandatory settings configured or some
 * other error is encountered, then the operation will fail and the target will
 * remain in a paused state.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate accesses and
 * updates to the current target.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param target The target to open.
 *
 * @return The opened target if it was opened successfully (which will be
 * equal to the target argument). If an error was encountered, then NULL is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_target( struct stumpless_target *target );

/**
 * Sets the console stream to write logs to.
 *
 * This will be stdout by default, but can be set to any stream. If it is set
 * to NULL then console messages will not be printed.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic variables are used to store and
 * retrieve the console stream.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be ansynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param stream The stream to write logs to. If this is NULL then the messages
 *	intended for the console stream will be ignored.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_set_cons_stream( FILE *stream );

/**
 * Sets the target used when one is not provided.
 *
 * Without being set, the current target will be the last one opened, or the
 * default target if a target has not yet been opened. The current target is
 * used by functions like stumplog() and stumpless() where a target is not
 * explicitly provided to the call.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic operations are used to work with the
 * default target.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers as it only consists of
 * an atomic read.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled, as it only consists of an atomic read.
 *
 * @param target The target to use as the current target.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_set_current_target( struct stumpless_target *target );

/**
 * Sets the default options to be used for all new targets created.
 *
 * If a target is created without calling this function, STUMPLESS_OPTION_NONE 
 * will be used as default. Using this function will not affect options for 
 * targets already created.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic operations are used to work with the
 * default target.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers as it only consists of
 * an atomic write.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled, as it only consists of an atomic write.
 *
 * @param option The bitwise 'or' of all options to be set as default.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_set_default_options( int option );

/**
 * Sets the default facility of a target.
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
 * @param target The target to modify.
 *
 * @param default_facility The default facility to use on the target. This
 * should be a STUMPLESS_FACILITY value.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_default_facility( struct stumpless_target *target,
                                int default_facility );

/**
 * Sets an option on a target.
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
 * @param target The target to modify.
 *
 * @param option The option to set on the target. This should be a
 * STUMPLESS_OPTION value.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_option( struct stumpless_target *target, int option );

/**
 * Sets the default app name for a given target.
 *
 * **Thread Safety: MT-Safe race:app_name**
 * This function is thread safe, of course assuming that the name is not changed
 * by any other threads during exeuction. A mutex is used to coordinate changes
 * to the target while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new name and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param target The target to modify.
 *
 * @param app_name The new default app name, as a NULL-terminated string.
 * The app name length is restricted to be 48 characters or less.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_target_default_app_name( struct stumpless_target *target,
                                       const char *app_name );

/**
 * Sets the default msgid for a given target.
 *
 * **Thread Safety: MT-Safe race:msgid**
 * This function is thread safe, of course assuming that the msgid is not
 * changed by any other threads during exeuction. A mutex is used to coordinate
 * changes to the target while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new name and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param target The target to modify.
 *
 * @param msgid The new default msgid, as a NULL-terminated string. The string 
 * must be in the ASCII printable range 33 <= character <= 126 as specified in 
 * RFC5424.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid );

/**
 * Sets the filter used to determine whether entries should be logged by a
 * given target.
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
 * @param target The target to set the filter function for.
 *
 * @param filter The filter to be used by the target. This can be NULL if all
 * entries should be logged by the target with no filtering.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_target_filter( struct stumpless_target *target,
                             stumpless_filter_func_t filter );

/**
 * Sets the log mask of a target.
 *
 * The mask is a bit field of severities that this target will allow if the
 * default mask-based filter is in use. These can be formed and checked using
 * the STUMPLESS_SEVERITY_MASK and STUMPLESS_SEVERITY_MASK_UPTO macros, and
 * combining them using bitwise or operations.
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
 * @param target The target to modify.
 *
 * @param mask The mask to use with the target.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_target_mask( struct stumpless_target *target, int mask );

/**
 * Checks to see if the given target is open.
 *
 * For targets that are opened with a single \c open function call, they will
 * likely be considered open as long as they are non-NULL, as the target
 * creation would otherwise fail before it could be opened. Targets are
 * be considered in a paused state if they were created but not opened yet, for
 * example with \c stumpless_new_network_target as opposed to
 * \c stumpless_open_network_target. Targets may also be paused if a settings
 * change has been made that could not be validated, such as changing the port
 * on a TCP network target to one that does not respond on the server.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being accessed.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @param target The target to check.
 *
 * @return The target if it is currently open, and NULL if not.
 */
STUMPLESS_PUBLIC_FUNCTION
const struct stumpless_target *
stumpless_target_is_open( const struct stumpless_target *target );

/**
 * Adds an entry into a given target. The entry has a structured data element
 * added to it with the file, line, and function information specified.
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
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks in some targets that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param target The target to send the message to.
 *
 * @param entry The entry to send to the target.
 *
 * @param file The name of the source file the entry should be tied to.
 *
 * @param line The line in the source file that the entry should be tied
 * to.
 *
 * @param func The name of the function that the entry should be tied to.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_trace_entry( struct stumpless_target *target,
                       struct stumpless_entry *entry,
                       const char *file,
                       int line,
                       const char *func );

/**
 * Adds a log message with a priority to a given target, along with the file,
 * line, and function information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_trace_log_str instead.
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
 * @param target The target to send the message to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied
 * to.
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
stumpless_trace_log( struct stumpless_target *target,
                     int priority,
                     const char *file,
                     int line,
                     const char *func,
                     const char *message,
                     ... );

/**
 * Adds a log message with a priority to a given target, along with the file,
 * line, and function information specified in a structured data element.
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
 * @param target The target to send the message to.
 *
 * @param priority The priority of the message - this should be the bitwise or
 * of a single STUMPLESS_SEVERITY and single STUMPLESS_FACILITY value.
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied
 * to.
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
stumpless_trace_log_str( struct stumpless_target *target,
                         int priority,
                         const char *file,
                         int line,
                         const char *func,
                         const char *message );

/**
 * Adds a message to a given target, along with the file, line, and function
 * information specified in a structured data element.
 *
 * The trace information is added in an element named `trace` with params named
 * `file`, `line`, and `function` for the respective pieces of information.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_trace_message_str instead.
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
 * @param target The target to send the message to.
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied
 * to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log, optionally containing any format
 * specifiers valid in \c printf. This may be NULL, in which case an event with
 * no message is logged. This must be a valid UTF-8 string in shortest form.
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
stumpless_trace_message( struct stumpless_target *target,
                         const char *file,
                         int line,
                         const char *func,
                         const char *message,
                         ... );

/**
 * Adds a message to a given target, along with the file, line, and function
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
 * @param target The target to send the message to.
 *
 * @param file The name of the source file the message should be tied to.
 *
 * @param line The line in the source file that the message should be tied
 * to.
 *
 * @param func The name of the function that the message should be tied to.
 *
 * @param message The message to log. This may be NULL, in which case an event
 * with no message is logged. This must be a valid UTF-8 string in shortest
 * form.
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_trace_message_str( struct stumpless_target *target,
                             const char *file,
                             int line,
                             const char *func,
                             const char *message );

/**
 * Unsets an option on a target.
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
 * @param target The target to modify.
 *
 * @param option The option to unset on the target. This should be a
 * STUMPLESS_OPTION value.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_unset_option( struct stumpless_target *target, int option );

/**
 * Adds a log message with a priority to a given target.
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
 * @param target The target to send the message to.
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
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
vstumpless_add_log( struct stumpless_target *target,
                    int priority,
                    const char *message,
                    va_list subs );

/**
 * Adds a message to a given target.
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
 * @param target The target to send the message to.
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
vstumpless_add_message( struct stumpless_target *target,
                        const char *message,
                        va_list subs );

/**
 * Adds a log message with a priority to a given target, along with the file,
 * line, and function information specified in a structured data element.
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
 * @param target The target to send the message to.
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
 *
 * @return A non-negative value if no error is encountered. If an error is
 * encountered, then a negative value is returned and an error code is set
 * appropriately. If the entry was rejected by the target's filter, then 0
 * is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
int
vstumpless_trace_log( struct stumpless_target *target,
                      int priority,
                      const char *file,
                      int line,
                      const char *func,
                      const char *message,
                      va_list subs );

/**
 * Adds a message to a given target, along with the file, line, and function
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
 * @param target The target to send the message to.
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
vstumpless_trace_message( struct stumpless_target *target,
                          const char *file,
                          int line,
                          const char *func,
                          const char *message,
                          va_list subs );

/**
 * Gets the string representation of the given target_type.
 *
 * This is a string literal that should not be modified or freed by the caller.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param target_type The target_type to get the string from.
 *
 * @return The string representation of the given target_type.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_target_type_string( enum stumpless_target_type target_type );


#ifdef __cplusplus
}                               /* extern "C" */
#endif

#endif                          /* __STUMPLESS_TARGET_H */
