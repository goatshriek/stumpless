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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"no se pudo vincular con el socket unix local"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"el buffer es demasiado pequeño para el mensaje proporcionado"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado cerrar un tipo de objetvo no soportado"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al conectar socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al conectar socket winsock2"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"el destino es válido sólo para objetivos de red"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un elemento con este nombre ya está presente en esta entrada"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un elemento con las caraterísticas especificadas no pudo ser encontrado"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno despues de la llamada fallida"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"no se pudo abrir el archivo especificado"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"no se pudo escribir en el archivo"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"código de retorno de la función manager log"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"el manejo del log para el objetivo de la función ha fallado"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"no se pudo crear un archivo con el nombre de socket local elegido usando mkstemp"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo ha fallado en el hostname proporcionado"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"código de retorno de la llamada fallida a getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName ha fallado"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname ha fallado"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"el resultado de GetLastError despues de la llamada fallida"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"el índice no válido, o -1 por lo que es deamasiado largo para representarse como entero"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"facilidad no válida"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"Los códigos de facilidad deben ser definidos de acuerdo al RFC 5424" \
" despues de la multiplicación por 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id de objetivo no válido"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"índice " INDEXED_THING " no válido"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la severidad no válida"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"los códigos de severidad deben ser definidos de acuerdo al RFC 5424:" \
" valores entre 0 y 7 inclusive"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"el tamaño máximo de mensaje sólo es válido para objetivos de red UDP"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"el alojamiento de memoria para una llamada ha fallado"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"el mensaje es demasiado largo para ser enviado en un datagrama simple"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"el tamaño del mensaje que se ha intentado enviar"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protocolo de red elegido no soportado"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"objetivos de red no soportados por esta compilación"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " fue NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha tratado de abrir un tipo de objetivo no soportado"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un parámetro con las características especificadas no fue encontrado"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado enviar una entrada a un tipo de objetivo no soportado"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado enviar un mensaje a un tipo de objetivo no soportado"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket sys/socket.h"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket unix"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket winsock2"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al abrir el socket"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"no se pudo escribir en el stream"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"este tipo de objetivo siempre permanece abierto"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"los puertos de transporte sólo son válidos para objetivos de red"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protocolo de transporte elegido no soportado"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al abrir un socket unix con la función socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"se ha revisado si un tipo de objetivo no soportado fue abierto"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"no se pudo cerrar el log de eventos de Windows"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"no se pudo abrir el log de eventos de Windows"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"código de error de socket de Windows"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al abrir un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"el resultado de WSAGetLastError despues que la llamada fallara"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"el largo de la cadena ha excedido el límite máximo"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"el largo de la cadena infractora"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formato " ARG " no válido"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TARGET TYPE ERROR MESSAGE"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H */
