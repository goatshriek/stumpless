/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2022 Joel E. Anderson
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
 * Error codes and functions for detecting and assessing them.
 */

#ifndef __STUMPLESS_ERROR_H
#  define __STUMPLESS_ERROR_H

#include <stdbool.h>
#include <stdio.h>
#include <stumpless/config.h>
#include <stumpless/generator.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * A macro to implement error id enum and error string array.
 */
#define STUMPLESS_FOREACH_ERROR(ERROR)	\
/**
  A provided network address was not valid.
 
  This might be formatting problem, or it might mean that a DNS lookup failed.
 */\
  ERROR(STUMPLESS_ADDRESS_FAILURE, 0)	\
/** A required function parameter was NULL or empty. */\
  ERROR(STUMPLESS_ARGUMENT_EMPTY, 1)	\
/** A provided argument was too big, for example to fit into a buffer target. */\
  ERROR(STUMPLESS_ARGUMENT_TOO_BIG, 2)	\
/**
  A duplicate of an already existing element was detected in an entry.
 
  @since release v1.6.0.
 */\
  ERROR(STUMPLESS_DUPLICATE_ELEMENT, 3)	\
/**
  No element with the specified characteristics was found.
 
  @since release v1.6.0.
 */\
  ERROR(STUMPLESS_ELEMENT_NOT_FOUND, 4)	\
/** Could not open a file. */\
  ERROR(STUMPLESS_FILE_OPEN_FAILURE, 5)	\
/** Could not write to a file. */\
  ERROR(STUMPLESS_FILE_WRITE_FAILURE, 6)	\
/** A provided index was not in a valid range. */\
  ERROR(STUMPLESS_INDEX_OUT_OF_BOUNDS, 7)	\
/** A provided facility code did not conform to RFC 5424. */\
  ERROR(STUMPLESS_INVALID_FACILITY, 8)	\
/** A target or entry ID was not valid. */\
  ERROR(STUMPLESS_INVALID_ID, 9)	\
/**
  A provided severity code did not conform to RFC 5424.
 
  @since release v1.6.0.
 */\
  ERROR(STUMPLESS_INVALID_SEVERITY, 10)	\
/** A memory allocation or reallocation failed. */\
  ERROR(STUMPLESS_MEMORY_ALLOCATION_FAILURE, 11)	\
/** The given layer 3 protocol is not supported by this implementation. */\
  ERROR(STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED, 12)	\
/**
  No param with the specified characteristics was found.
 
  @since release v1.6.0.
 */\
  ERROR(STUMPLESS_PARAM_NOT_FOUND, 13)	\
/** Could not bind to a socket. */\
  ERROR(STUMPLESS_SOCKET_BIND_FAILURE, 14)	\
/** Could not connect to a socket. */\
  ERROR(STUMPLESS_SOCKET_CONNECT_FAILURE, 15)	\
/** Could not create a socket. */\
  ERROR(STUMPLESS_SOCKET_FAILURE, 16)	\
/** Could not send to a socket. */\
  ERROR(STUMPLESS_SOCKET_SEND_FAILURE, 17)	\
/** Could not write to a stream. */\
  ERROR(STUMPLESS_STREAM_WRITE_FAILURE, 18)	\
/** The requested operation is not valid on the given target type. */\
  ERROR(STUMPLESS_TARGET_INCOMPATIBLE, 19)	\
/** The target type provided is unsupported by this implementation. */\
  ERROR(STUMPLESS_TARGET_UNSUPPORTED, 20)	\
/** The given layer 4 protocol is not supported by this implementation. */\
  ERROR(STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED, 21)	\
/** Could not close the Windows Event Log. */\
  ERROR(STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE, 22)	\
/** Could not open the Windows Event Log. */\
  ERROR(STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE, 23)	\
/** A provided encoding does not conform to the standard. */\
  ERROR(STUMPLESS_INVALID_ENCODING, 24) \
/** The current hostname could not be retrieved. */\
  ERROR(STUMPLESS_GETHOSTNAME_FAILURE, 25 ) \
/**
 * A call to a function target's log function failed.
 *
 * @since release v2.1.0
 */\
  ERROR(STUMPLESS_FUNCTION_TARGET_FAILURE, 26 ) \
/**
 * A call to a systemd journald function failed.
 *
 * @since release v2.1.0
 */\
  ERROR( STUMPLESS_JOURNALD_FAILURE, 27 ) \
/**
 * A general failure of a Windows API call. Details on what call failed and
 * why are provided in the error details.
 *
 * @since release v2.1.0
 */\
  ERROR( STUMPLESS_WINDOWS_FAILURE, 28 ) \
/**
 * The format of the given string is incorrect.
 *
 * @since release v2.2.0
 */\
  ERROR( STUMPLESS_INVALID_PARAM_STRING, 29 )

/**
 * An (enum) identifier of the types of errors that might be encountered.
 *
 * Note that the same error may be encountered in different contexts with a
 * different ultimate cause. To completely diagnose a problem, you will need
 * to look at more than just the error id.
 *
 * @note The real implementation of enum values is now moved under `STUMPLESS_FOREACH_ERROR(ERROR)` macro.
 */
enum stumpless_error_id {
  STUMPLESS_FOREACH_ERROR(STUMPLESS_GENERATE_ENUM)
};


/** 
 *Information describing an error encountered by the library. 
 */
struct stumpless_error {
  enum stumpless_error_id id; /**< error family */
  const char *message; /**< specific details of the failure */
  int code; /**< an error code possibly providing more information */
  const char *code_type; /**< a description of the error code */
};

/**
 * Retrieves the error encountered by the last library call.
 *
 * The returned error struct is only valid until the next call to a stumpless
 * function. After this, it should not be referred to, and if the error of any
 * subsequent call is needed another call to stumpless_get_error must be made.
 *
 * Note that the id is the only field of the error that is guaranteed to be set.
 * Other members may or may not be set, depending on the context of the error.
 *
 * If the code_type is NULL, then the code is not valid and should be ignored.
 *
 * This function does _not_ clear or update the per-thread error code for
 * stumpless, as it is involved in the error handling process itself.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. No synchronization primitives are used as the
 * returned pointer is specific to the thread of execution. As a result, the
 * result should not be shared between threads.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers. If you do so, note that
 * if it is called before a stumpless library function in the handler itself
 * the result will not be meaningful.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @return A stumpless_error struct describing the error encountered by the last
 * function call. If no error was encountered, this will be NULL.
 */
STUMPLESS_PUBLIC_FUNCTION
const struct stumpless_error *
stumpless_get_error( void );

/**
 * Gets the error id of the given error.
 *
 * **Thread Safety: MT-Safe race:err**
 * This function is thread safe, as long as err is not modifed by other threads
 * during this call.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since Release v1.5.0
 *
 * @param err The error to get the id from. This must not be NULL.
 *
 * @return The error id of the given error.
 */
STUMPLESS_PUBLIC_FUNCTION
enum stumpless_error_id
stumpless_get_error_id( const struct stumpless_error *err );

/**
 * Gets the error string of the given error id.
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
 * @since Release v1.6.0
 *
 * @param id The error id to get the error string from.
 *
 * @return The error string of the given error id.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_error_id_string( enum stumpless_error_id id );

/**
 * Gets the current stream that errors are written to.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic variables are used to store and
 * retrieve the error stream.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be ansynchronously
 * cancelled.
 *
 * @return The current stream errors are written to.
 */
STUMPLESS_PUBLIC_FUNCTION
FILE *
stumpless_get_error_stream( void );

/**
 * True if the last call to a stumpless function encountered an error. To get
 * the error itself, use the stumpless_get_error function.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. No synchronization primitives are used as the
 * returned flag is specific to the thread of execution.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers. If you do so, note that
 * if it is called before a stumpless library function in the handler itself
 * the result will not be meaningful.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v1.6.0.
 *
 * @return True if the last stumpless call had an error, false if not.
 */
STUMPLESS_PUBLIC_FUNCTION
bool
stumpless_has_error( void );

/**
 * Prints information about the current error to the error stream.
 *
 * A prefix can be added to the information if desired. If one is provided then
 * it will be followed by a colon character and a space, followed by the error
 * information. If it is not provided then the colon and space characters will
 * not be printed.
 *
 * The message will end with a newline.
 *
 * If there is not currently an active error message, then nothing will be
 * printed (not even the prefix).
 *
 * **Thread Safety: MT-Safe race:prefix**
 * This function is thread safe, of course assuming that prefix is not changed
 * by other threads during execution. A lock is used to coordinate accesses to
 * the error stream.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers, as it uses a
 * non-reentrant lock to synchronize access to the error stream.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the lock used to control access to the error stream may not
 * be released after a cancellation.
 *
 * @param prefix An optional prefix to print in front of the message. If this is
 * NULL then it will simply be ignored.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_perror( const char *prefix );

/**
 * Sets the stream to write errors to.
 *
 * This will be stderr by default, but can be set to any stream. If it is set
 * to NULL then error messages will not be printed (essentially skipping all
 * \c stumpless_perror calls).
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. Atomic variables are used to store and
 * retrieve the error stream.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be ansynchronously
 * cancelled.
 *
 * @param stream The stream to write errors to. If this is NULL then the messages
 *	intended for the error stream will be ignored.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_set_error_stream( FILE *stream );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_ERROR_H */
