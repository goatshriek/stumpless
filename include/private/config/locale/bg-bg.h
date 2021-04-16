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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_BG_BG_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_BG_BG_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"не може да се свърже с локален unix сокет"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"буферът е твърде малък за даденото съобщение"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"направен е опит да се затвори неподдържан целеви тип"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно свързване със sys/socket.h сокет"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно свързване с winsock2 сокет"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"дестинацията е валидна само за мрежови цели"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"елемент с предоставеното име вече присъства в този запис"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"не може да бъде намерен елемент с посочените характеристики"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno след неуспешно извикване"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"върната стойност от фунцията манипулатор на логове"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"манипулаторът на логове за целевата фукция е неуспешен"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"не можа да създаде файл с избраното име на локален сокет, използвайки mkstemp"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo не успя с посоченото име на хост"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"върната стойност от неуспешното извикване на getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName не успя"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname не успя"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"резултатът от GetLastError след неуспешното извикване"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"невалиден индекс или -1, ако е твърде голям за да бъде представен, като int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"невалидното съоръжение"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"кодовете на съоръженията трябва да бъдат дефинирани в съответствие с RFC 5424," \
" след умножаване по 8"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"невалиден " INDEXED_THING " индекс"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"невалидната тежест"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"нивата на тежест трябва да бъдат дефинирани в съответствие с RFC 5424: стойности между 0" \
" и 7 включително"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"максимален размер на съобщението е валиден само за UDP мрежови цели"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"съобщението е твърде голямо, за да бъде изпратено в една дейтаграма"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"размер на съобщението, което беше опитано да се изпрати"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"мрежови цели не се поддържат от тази компилация"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " беше NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"опит да се отвори неподдържан целеви тип"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"не може да бъде намерен параметър с посочените характеристики"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"опит да се изпрати запис до неподдържан целеви тип"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"опит да се изпрати съобщение до неподдържан целеви тип"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно изпращане със sys/socket.h сокет"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto не успя с unix сокет"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно изпращане с winsock2 сокет"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно отваряне на сокет"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"този целеви тип е винаги отворен"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"транспортните портове са валидни само за мрежови цели"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно отваряне на unix сокет с функция socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"проверете дали е отворен неподдържан целеви тип"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket код на грешка"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"неуспешно отваряне на winsock2 сокет"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"резултатът от WSAGetLastError след неуспешното извикване"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"дължината на низа надвишава максималната граница"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"дължината на нарушаващия низ"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"невалиден " ARG " формат"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TARGET TYPE ERROR MESSAGE"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_BG_BG_H */
