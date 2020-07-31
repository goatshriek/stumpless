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
 * Error codes and functions for detecting and assessing them.
 */

#ifndef __STUMPLESS_ERROR_H
#  define __STUMPLESS_ERROR_H

#include <stdbool.h>
#include <stdio.h>

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

#define STUMPLESS_GENERATE_ENUM(ENUM, INDEX) ENUM = INDEX,

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
 * Note that the id is the only field of the error that is guaranteed to be set.
 * Other members may or may not be set, depending on the context of the error.
 *
 * If the code_type is NULL, then the code is not valid and should be ignored.
 *
 * @return A stumpless_error struct describing the error encountered by the last
 * function call. If no error was encountered, this will be NULL.
 */
struct stumpless_error *stumpless_get_error( void );

/**
 * Gets the error id of the given error.
 *
 * @since Release v1.5.0
 *
 * @param err The error to get the id from. This must not be NULL.
 *
 * @return The error id of the given error.
 */
enum stumpless_error_id
stumpless_get_error_id( const struct stumpless_error *err );

/**
 * Gets the error string of the given error id.
 *
 * @since Release v1.6.0
 *
 * @param id The error id to get the error string from.
 *
 * @return The error string of the given error id.
 */
const char *
stumpless_get_error_id_string( enum stumpless_error_id id );

/**
 * Gets the current stream that errors are written to.
 *
 * @return The current stream errors are written to.
 */
FILE *
stumpless_get_error_stream( void );

/**
 * True if the last call to a stumpless function encountered an error. To get
 * the error itself, use the stumpless_get_error function.
 *
 * @since release v1.6.0.
 *
 * @return True if the last stumpless call had an error, false if not.
 */
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
 * @param prefix An optional prefix to print in front of the message. If this is
 * NULL then it will simply be ignored.
 */
void
stumpless_perror( const char *prefix );

/**
 * Sets the stream to write errors to.
 *
 * This will be stderr by default, but can be set to any stream. If it is set
 * to NULL then error messages will not be printed (essentially skipping all
 * \c stumpless_perror calls).
 *
 * @param stream The stream to write errors to. If this is NULL then it will be
 * ignored.
 */
void
stumpless_set_error_stream( FILE *stream );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_ERROR_H */
