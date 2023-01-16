/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2023 Joel E. Anderson
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
 * United States English localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"could not bind to the local unix socket"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer is too small for the given message"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"attempted to close an unsupported target type"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"connect failed with a sys/socket.h socket"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"connect failed with a winsock2 socket"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destination is only valid for network targets"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"an element with the provided name is already present in this entry"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"an element with the specified characteristics could not be found"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno after the failed call"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the specified file"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the file"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"return code of the log handler function"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"the log handler for a function target failed"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo failed on the provided hostname"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"return code of the failed getaddrinfo call"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName failed"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname failed"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW failed"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW failed"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"the invalid index, or -1 of it is too large to represent as an int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"the invalid facility"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"facility codes must be defined in accordance with RFC 5424, after the" \
" multiplication by 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"invalid target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"invalid " INDEXED_THING " index"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ registry value was neither empty nor terminated with two NULL" \
" characters"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"the invalid severity"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"severity codes must be defined in accordance with RFC 5424: values between 0" \
" and 7 inclusive"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"target type is incompatible with this operation"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"return code of sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv failed"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"could not create a file with the chosen local socket name using mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"max message size is only valid for UDP network targets"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"could not convert the provided multibyte string to a wide char string"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"a memory allocation call failed"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"the size of the message that was attempted to be sent"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"message is too large to be sent in a single datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen network protocol is unsupported"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"network targets are not supported by this build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " was NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tried to open an unsupported target type"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"a param with the specified characteristics could not be found"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be created"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be deleted"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"a registry subkey could not be opened"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"a registry value could not be read"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"a registry value could not be set"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto failed with a unix socket"

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

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless registration of Windows Event Log Source"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the stream"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"the length of the offending string"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"length of string exceeded maximum limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"this target type is always open"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"transport ports are only valid for network targets"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen transport protocol is unsupported"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"failed to open a unix socket with socket function"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"checked to see if an unsupported target type was open"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"could not close the Windows Event Log"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the Windows Event Log"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket error code"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"failed to open a winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"the result of WSAGetLastError after the failed call"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H */
