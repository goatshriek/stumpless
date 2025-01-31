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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_CZ_CZ_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_CZ_CZ_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"není možné spojení s unixovým socketem"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer je příliš malý pro tuto zprávu"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o uzavření cílového souboru nepodporovaného typu"

// todo translate
#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"selhání spojení se sys/socket.h socketem"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"selhání spojení s winsock socketem"

// todo translate
#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"daný cílový soubor je platný pouze pro síťové cíle"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"element s daným jménem se už vyskytuje v tomto vstupu"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"není možné najít element se specifikovanou charakteristikou"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"volání vrátilo číslo chyby (errno)"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"chybové hlášení- nepodařilo se otevřít soubor"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"chybové hlášení- nepodařilo se zapísat"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"neplatný " ARG " formát"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"návratový kód funkce obsluhy protokolu"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"obslužná rutina protokolu pro cíl funkce selhala"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"funkce getaddrinfor selhala během poskytování hostname"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"volání funkce getaddrinfo vrátilo chybovou návratovou hodnotu"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName zlyhal"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname zlyhal"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"výsledek GetLastError po neúspěšném volání"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW zlyhal"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW zlyhal"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"neplatný index - index je příliš velký na to aby byl reprezentován jako" \
" datový typ int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"nekompatibilní zařízení"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"hodnota kódu zařízení, po vydělení číslem 8, musí být definována v souladu s" \
" protokolem RFC 5424"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"neplatné cílové ID"

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
"kód služby musí být definován v souladu s normou RFC 5424: hodnoty mezi 0 a" \
" 7 včetně"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

// todo translate
#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"target type is incompatible with this operation"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"návratový kód sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv zlyhal"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"není možné vytvořit soubor s vybraným jménem lokálního socketu pomocí mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maximální velikost zprávy je platná pouze pro UDP"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"could not convert the provided multibyte string to a wide char string"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"volání alokace paměti se nezdařilo"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"velikost zprávy, která se pokusila odeslat je "

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"zpráva je příliš velká na to, aby byla poslána v jednom datagramu"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"vybraný síťový protokol není podporován"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"cíle sítě nejsou podporovány tímto sestavením"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " měl hodnotu NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o otevření cíle nepodporovaného typu"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"specifikován parametr nebyl nalezen"

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
"odesílání unixových socketu (unix socket) selhalo"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslání vstupu nepodporovaného typu na cíl"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslání vstupu nepodporovaného typu"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"odesílání systémového socketu (sys/socket.h) selhalo"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"odesílání winsock2 socketu selhalo"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"otevření socketu selhalo"

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

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"nelze zapisovat do streamu"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"délka problémový řetězce je"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"délka řetězce přesáhla maximální limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"cíl danného typu je stále otevřený"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"přenosové porty jsou platné pouze pro síťové cíle"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"zvolený transportní protokol není podporován"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"selhání otevírání unixového socketu pomocí soketové funkce"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"zkontrolování vyditeľnosti cílového souboru nepodporovaného typu"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"nemohl zavřít protokol událostí systému Windows"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Chybový kód Windows Socket"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

// todo translate
#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"chybová návratová hodoty (error code) Windows socketu"

// todo translate
#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"selhání otevírání winsock2 socketu"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"výsledek WSAGetLastError po selhání volání"

#endif  /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_CZ_CZ_H */
