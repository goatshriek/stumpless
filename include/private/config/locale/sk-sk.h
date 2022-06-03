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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_SK_SK_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_SK_SK_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nieje možné spojenie s unixovým socketom"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer je príliš malý pre tuto správu"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o uzatvorenie cieľového súboru nepodporovaného typu"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"L10N MISSING COMMIT TRANSACTION FAILED ERROR MESSAGE"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie spojenie so sys/socket.h socketom"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie spojenie s winsock socketom"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"L10N MISSING CREATE TRANSACTION FAILED ERROR MESSAGE"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"daný cieľový súbor je platný len pre sieťové ciele"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"element s daným menom sa uz vyskytuje v tomto vstupe"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"nieje možné nájsť element so špecifikovanou charakteristikou"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"volanie vrátilo číslo chyby (errno)"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"FILE OPEN FAILURE MESSAGE"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"FILE WRITE FAILURE MESSAGE"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"FUNCTION TARGET FAILURE CODE TYPE"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"FUNCTION TARGET FAILURE ERROR MESSAGE"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nieje možné vytvoriť súbor s vybraným menom lokálneho socketu pomocou mkstemp"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"funkcia getaddrinfor zlyhala počas poskytovania hostname"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"volanie funkcie getaddrinfo vrátilo chybovú návratovú hodnotu"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GETCOMPUTERNAME FAILED ERROR MESSAGE"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"GETHOSTNAME FAILED ERROR MESSAGE"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"GETLASTERROR ERROR CODE TYPE"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"neplatný index - index je priveľký na to aby bol reprezentovany ako datový typ int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"nekompatibilné zariadenie"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"hodnota kódu zariadenia, po vydelení číslom 8, musí byť definovaná v súlade s protokolom RFC 5424"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"INVALID ID ERROR MESSAGE"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"neplatný index " INDEXED_THING

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"neplatná služba"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"kód služby musí byť definovaný v súlade s normou RFC 5424: hodnoty medzi 0 a 7 vrátane"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"JOURNALD FAILURE ERROR CODE"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"JOURNALD FAILURE ERROR MESSAGE"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maximálna veľkosť správy je platná len pre UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"L10N MISSING MB TO WIDE CONVERSION ERROR CODE TYPE"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"L10N MISSING MB TO WIDE CONVERSION ERROR MESSAGE"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"MEMORY ALLOCATION FAILURE MESSAGE"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"správa je príliš veľká na to, aby bola poslaná v jednom datagrame"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"veľkosť správy, ktorá sa pokúsila odoslať je "

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"NETWORK PROTOCOL UNSUPPORTED ERROR MESSAGE"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"táto verzia nepodporuje sieťové cieľe"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " mal hodnotu NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o otvorenie cieľa nepodporovaného typu"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"špecifikovaný parameter nebol nájdený"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY SUBKEY CREATION FAILED ERROR MESSAGE"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY SUBKEY DELETION FAILED ERROR MESSAGE"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY SUBKEY OPEN FAILED ERROR MESSAGE"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY VALUE GET FAILED ERROR MESSAGE"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY VALUE SET FAILED ERROR MESSAGE"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslanie vstupu nepodporovaného typu na cieľ"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"pokus o poslanie vstupu nepodporovaného typu"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie systemového socketu (sys/socket.h) zlyhalo"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie unixoveho socketu (unix socket) zlyhalo"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"odosielanie winsock2 socketu zlyhalo"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"otvorenie socketu zlyhalo"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"STREAM WRITE FAILURE ERROR MESSAGE"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"cieľ danného typu je stále otvorený"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"prenosové porty su platné len pre sieťové ciele"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"TRANSPORT PROTOCOL UNSUPPORTED ERROR MESSAGE"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie otvárania unixového socketu pomocou soketovej funkcie"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"skontrolovanie vyditeľnosti cieľového súboru nepodporovaného typu"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"WEL CLOSE FAILURE ERROR MESSAGE"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"WEL OPEN FAILURE ERROR MESSAGE"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"L10N MISSING WIDE TO MB CONVERSION ERROR CODE TYPE"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"L10N MISSING WIDE TO MB CONVERSION ERROR MESSAGE"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"L10N MISSING WINDOWS RETURN ERROR CODE TYPE"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"chybová návratová hodota (error code) Windows Socketu"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"zlyhanie otvarania winsock2 socketu"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"výsledok WSAGetLastError po zlyhaní volania"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"dĺžka reťazca presiahla maximálny limit"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"dĺžka problemového reťazca je"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"neplatný " ARG " formát"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TARGET TYPE ERROR MESSAGE"

#endif //STUMPLESS_SK_SK_H
