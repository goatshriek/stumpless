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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_SK_SK_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_SK_SK_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nieje možné spojenie s unixovým socketom"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer je príliš malý pre tuto správu"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o uzatvorenie cieľového súboru nepodporovaného typu"

// todo translate
#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie spojenie so sys/socket.h socketom"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie spojenie s winsock socketom"

// todo translate
#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"daný cieľový súbor je platný len pre sieťové ciele"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"element s daným menom sa uz vyskytuje v tomto vstupe"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"nieje možné nájsť element so špecifikovanou charakteristikou"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"volanie vrátilo číslo chyby (errno)"

// todo translate
#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the specified file"

// todo translate
#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the file"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"neplatný " ARG " formát"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"return code of the log handler function"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"the log handler for a function target failed"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"funkcia getaddrinfor zlyhala počas poskytovania hostname"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"volanie funkcie getaddrinfo vrátilo chybovú návratovú hodnotu"

// todo translate
#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName failed"

// todo translate
#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname failed"

// todo translate
#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW failed"

// todo translate
#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW failed"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"neplatný index - index je priveľký na to aby bol reprezentovany ako datový" \
" typ int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"nekompatibilné zariadenie"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"hodnota kódu zariadenia, po vydelení číslom 8, musí byť definovaná v súlade" \
" s protokolom RFC 5424"

// todo translate
#  define L10N_INVALID_ID_ERROR_MESSAGE \
"invalid target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"neplatný index " INDEXED_THING

// todo translate
#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ registry value was neither empty nor terminated with two NULL" \
" characters"

// todo translate
#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"the string is not of the name=\"value\" format"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"neplatná služba"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"kód služby musí byť definovaný v súlade s normou RFC 5424: hodnoty medzi" \
" 0 a 7 vrátane"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

// todo translate
#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"target type is incompatible with this operation"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"return code of sd_journal_sendv"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv failed"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nieje možné vytvoriť súbor s vybraným menom lokálneho socketu pomocou mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maximálna veľkosť správy je platná len pre UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"L10N MISSING MB TO WIDE CONVERSION ERROR CODE TYPE"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"L10N MISSING MB TO WIDE CONVERSION ERROR MESSAGE"

// todo translate
#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"a memory allocation call failed"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"veľkosť správy, ktorá sa pokúsila odoslať je "

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"správa je príliš veľká na to, aby bola poslaná v jednom datagrame"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

// todo translate
#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen network protocol is unsupported"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"táto verzia nepodporuje sieťové cieľe"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " mal hodnotu NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o otvorenie cieľa nepodporovaného typu"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"špecifikovaný parameter nebol nájdený"

// todo translate
#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be created"

// todo translate
#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be deleted"

// todo translate
#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"a registry subkey could not be opened"

// todo translate
#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"a registry value could not be read"

// todo translate
#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"a registry value could not be set"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie unixoveho socketu (unix socket) zlyhalo"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslanie vstupu nepodporovaného typu na cieľ"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslanie vstupu nepodporovaného typu"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie systemového socketu (sys/socket.h) zlyhalo"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie winsock2 socketu zlyhalo"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"otvorenie socketu zlyhalo"

// todo translate
#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless registration of Windows Event Log Source"

// todo translate
#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"could not bind " PARAM " to the statement"

// todo translate
#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"the database was busy and could not complete the transaction"

// todo translate
#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"could not close the sqlite3 database"

// todo translate
#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"a custom callback for prepared statements failed"

// todo translate
#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"could not open the sqlite3 database"

// todo translate
#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 failed"

// todo translate
#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"the return code of the failed sqlite3 call"

// todo translate
#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"the number of times the operation was retried"

// todo translate
#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step failed"

// todo translate
#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3 targets are not supported by this build"

// todo translate
#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the stream"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"dĺžka problemového reťazca je"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"dĺžka reťazca presiahla maximálny limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"cieľ danného typu je stále otvorený"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"prenosové porty su platné len pre sieťové ciele"

// todo translate
#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen transport protocol is unsupported"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie otvárania unixového socketu pomocou soketovej funkcie"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"skontrolovanie vyditeľnosti cieľového súboru nepodporovaného typu"

// todo translate
#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"could not close the Windows Event Log"

// todo translate
#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the Windows Event Log"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

// todo translate
#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"chybová návratová hodota (error code) Windows Socketu"

// todo translate
#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie otvarania winsock2 socketu"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"výsledok WSAGetLastError po zlyhaní volania"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_SK_SK_H */
