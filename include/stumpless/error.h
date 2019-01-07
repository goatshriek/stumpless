/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018 Joel E. Anderson
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

#ifndef __STUMPLESS_ERROR_H
#  define __STUMPLESS_ERROR_H

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * An identifier of the types of errors that might be encountered. Note that
 * the same error may be encountered in different contexts.
 */
enum stumpless_error_id {
  STUMPLESS_ADDRESS_FAILURE,
  STUMPLESS_ARGUMENT_EMPTY,
  STUMPLESS_ARGUMENT_TOO_BIG,
  STUMPLESS_FILE_OPEN_FAILURE,
  STUMPLESS_FILE_WRITE_FAILURE,
  STUMPLESS_INVALID_FACILITY,
  STUMPLESS_INVALID_ID,
  STUMPLESS_MEMORY_ALLOCATION_FAILURE,
  STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED,
  STUMPLESS_SOCKET_BIND_FAILURE,
  STUMPLESS_SOCKET_CONNECT_FAILURE,
  STUMPLESS_SOCKET_SEND_FAILURE,
  STUMPLESS_STREAM_WRITE_FAILURE,
  STUMPLESS_TARGET_INCOMPATIBLE,
  STUMPLESS_TARGET_UNSUPPORTED,
  STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED,
  STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE,
  STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE
};

/**
 * Information describing an error encountered by the library.
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

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_ERROR_H */
