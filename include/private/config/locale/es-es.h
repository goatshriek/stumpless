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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"no se pudo vincular con el socket unix local"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"el buffer es demasiado pequeño para el mensaje proporcionado"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado cerrar un tipo de objeto no soportado"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction ha fallado"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"al conectar socket sys/socket.h ha fallado"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"al conectar socket winsock2 ha fallado"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction ha fallado"

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

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formato " ARG " no válido"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"código de retorno de la función manager log"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"el manejo del log para el objetivo de la función ha fallado"

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

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW ha fallado"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW ha fallado"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"el índice no válido, o -1 por lo que es deamasiado largo para representarse" \
" como entero"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"facilidad no válida"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"Los códigos de facilidad deben ser definidos de acuerdo al RFC 5424" \
" despues de la multiplicación por 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id de objetivo no válido"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"índice " INDEXED_THING " no válido"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"un valor de registro MULTI_SZ no estaba ni vacío ni terminado con dos NULL"

// todo translate
#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"the string is not of the name=\"value\" format"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la gravedad inválida"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"los códigos de gravedad deben ser definidos de acuerdo al RFC 5424:" \
" valores entre 0 y 7 inclusive"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"se alcanzó un estado inválido durante el análisis de la cadena UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"el tipo de destino es incompatible con esta operación"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"código de retorno de sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv ha fallado"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"no se pudo crear un archivo con el nombre de socket local elegido usando" \
" mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"el tamaño máximo de mensaje sólo es válido para objetivos de red UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"el resultado de GetLastError después de la llamada fallida"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"no se ha podido convertir la cadena multibyte a una cadena de caracteres" \
" anchos (wide char)"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"la reserva de memoria para una llamada ha fallado"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"el tamaño del mensaje que se ha intentado enviar"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"el mensaje es demasiado largo para ser enviado en un datagrama simple"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] y inet_pton fallaron en resolver el nombre"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protocolo de red elegido no soportado"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"objetivos de red no soportados por esta compilación"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " fue NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado abrir un tipo de objetivo no soportado"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"no se encontró un parámetro con las características especificadas"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"no se pudo crear un registro subclave"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"no pudo eliminarse un registro subclave"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"no pudo abrirse un registro subclave"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"no pudo leerse un registro valor"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"no pudo establecerse un registro valor"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado enviar una entrada a un tipo de objetivo no soportado"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"se ha intentado enviar un mensaje a un tipo de objetivo no soportado"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al enviar con socket winsock2"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al abrir el socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"registro de Stumpless del Registro de Eventos de Windows"

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
"no se pudo escribir en el stream"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"el largo de la cadena infractora"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"el largo de la cadena ha excedido el límite máximo"

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

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"no se ha podido convertir la cadena de caracteres anchos (wide char) a una" \
" cadena multibyte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"el código de error de Windows devuelto por la llamada fallida"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"código de error de socket de Windows"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"el resultado de GetLastError después de la llamada fallida"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"se ha fallado al abrir un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"el resultado de WSAGetLastError despues que la llamada fallara"

#endif /*  __STUMPLESS_PRIVATE_CONFIG_LOCALE_ES_ES_H */
