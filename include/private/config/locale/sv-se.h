/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2020-2021 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_SV_SE_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_SV_SE_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kunde inte binda till den lokala Unix-Socketen"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffern är för liten för det givna meddelandet"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"försökte att stänga en osupporterad målstyp"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"anslutning med en sys/socket.h-Socket misslyckades"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"anslutning med en winsock2-Socket misslyckades"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"typen är endast giltig för nätverksmål"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"ett element med det angivna namnet finns redan i dettaa införande"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"kunde inte hitta ett element med de angivna egenskaperna"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno efter det misslyckade anropet"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"FILE OPEN FAILURE MESSAGE"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"FILE WRITE FAILURE MESSAGE"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"FUNCTION TARGET FAILURE CODE TYPE"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"FUNCTION TARGET FAILURE ERROR MESSAGE"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp kunde inte skapa filen med det valda lokala Socket-namnet"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo misslyckades på det angivna hostnamnet"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"returneringskoden av det misslyckade getaddrinfo-anropet"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GETCOMPUTERNAME FAILED ERROR MESSAGE"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"GETHOSTNAME FAILED ERROR MESSAGE"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"GETLASTERROR ERROR CODE TYPE"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"det felaktiga indexedet, eller det -1 är för stort för att " \
"representera med en int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"den ogiltiga faciliteten"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"facilitetskoder måste vara definierade i enlighet med RFC 5424 " \
"efter multiplikation med 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"INVALID ID ERROR MESSAGE"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"ogiltig " INDEXED_THING " index"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"den ogiltiga allvarligheten"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"allvarlighetskoder måste vara definierade i enlighet med RFC 5424: värden " \
"mellan 0 till och med 7"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"största meddelandestorlek är endast giltig för UDP-nätverksmål"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"MEMORY ALLOCATION FAILURE MESSAGE"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"meddelandet är för stort för att skickas i ett enda datagram"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"storleken på meddelandet som försökte skickas"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"nätverksmål är inte supporterat av denna build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " var NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"försökte att öppna en osupporterad målstyp"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"kunde inte hitta en param med de specifierade egenskaperna"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"försökte att skicka ett införande till en osupporterad målstyp"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"försökte att skicka ett meddelande till en osupporterad målstyp"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"misslyckades att skicka med en sys/socket.h-Socket"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto misslyckades med en unix-Socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"misslyckades att skicka med en winsock2-Socket"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"misslyckades med att öppna en Socket"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"denna målstyp är alltid öppen"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"transportportar är alltid giltiga för nätverksmål"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"misslyckades att öppna en unix-Socket med socket-funktionen"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"kollade ifall en osupporterad målstyp var öppen"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"WEL CLOSE FAILURE ERROR MESSAGE"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"WEL OPEN FAILURE ERROR MESSAGE"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket felkod"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"misslyckades att öppna en winsock2-Socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"resultatet av WSAGetLastError efter det misslyckade anropet"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"STRING TOO LONG"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"STRING LENGTH ERROR CODE TYPE"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TARGET TYPE ERROR MESSAGE"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_SV_SE_H */
