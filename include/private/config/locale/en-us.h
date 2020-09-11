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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"attempted to close an unsupported target type"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"connect failed with a sys/socket.h socket"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"connect failed with a winsock2 socket"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"an element with the provided name is already present in this entry"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"an element with the specified characteristics could not be found"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno after the failed call"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo failed on the provided hostname"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"return code of the failed getaddrinfo call"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"the invalid index, or -1 of it is too large to represent as an int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"the invalid facility"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"facility codes must be defined in accordance with RFC 5424, after the" \
" multiplication by 8"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"invalid " INDEXED_THING " index"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"the invalid severity"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"severity codes must be defined in accordance with RFC 5424: values between 0" \
" and 7 inclusive"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"network targets are not supported by this build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " was NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tried to open an unsupported target type"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"a param with the specified characteristics could not be found"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"attempted to send an entry to an unsupported target type"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"attempted to send a message to an unsupported target type"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send failed with a sys/socket.h socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send failed with a winsock2 socket"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"failed to open a socket"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"this target type is always open"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"checked to see if an unsupported target type was open"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket error code"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"failed to open a winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"the result of WSAGetLastError after the failed call"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H */
