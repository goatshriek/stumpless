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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_PT_BR_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_PT_BR_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"não foi possível conectar com o socket unix local"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"o buffer é pequeno demais para a mensagem dada"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"foi tentado fechar um tipo de objetivo não suportado"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction falhou"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"conexão falhou com um socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"conexão falhou com um socket winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction falhou"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"o destino só é válido para objetivos de rede"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"um elemento com este nome já está presente nesta entrada"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"um elemento com estas características não pode ser encontrado"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno depois da chamada com erro"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"não foi possível abrir o arquivo especificado"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"não foi possível escrever no arquivo"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formato  " ARG " inválido"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"código de retorno da função tratadora de log"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"o tratador de log para a função objetivo falhou"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo falhou com o  hostname dado"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"código de retorno da chamada com erro de getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName falhou"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname falhou"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"o resultado de GetLastError depois da chamada com erro"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW falhou"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW falhou"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"o índice inválidou, ou -1, é grande demais para representar como inteiro"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"o recurso inválido"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"códigos de recurso (facility) devem ser definidos de acordo com a " \
"RFC 5424, após a multiplicação por 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id de objetivo inválido"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"índice " INDEXED_THING " inválido"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"um valor de registro MULTI_SZ não estava nem vazio nem finalizado" \
"com dois caracteres NULL"

// todo translate
#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"the string is not of the name=\"value\" format"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"a gravidade inválida"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"códigos de gravidade devem ser definidos de acordo com a RFC 5424:" \
" valores entre 0 e 7, incluso"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"tipo de objetivo é incompatível com esta operação"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"código de retorno de sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv falhou"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"não foi possível criar um arquivo com o nome de socket local" \
" escolhido usando mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"tamanho máximo de menságem só é válido para objetivos de rede UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"o resultado de GetLastError após a chamada com erro"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"não foi possível converter a string multibyte para wide char"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"uma chamada de alocação de memória falhou"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"o tamanho da mensagem que se tentou enviar"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"a mensagem é grande demais para ser enviada em um único datagrama"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"o protocolo de rede escolhido não é suportado"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"objetivos de rede não são suportados por essa build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " era NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"foi tentado abrir um tipo não suportado de objetivo"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"um parâmetro com as características especificadas não foi encontrado"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"uma subchave de registro não pode ser criada"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"uma subchave de registro não pode ser deletada"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"uma subchave de registro não pode ser aberta"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"uma subchave de registro não pode ser lida"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"não foi possivel escrever um valor de registro"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto falhou com um socket unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"foi tentado enviar uma entrada com um tipo de objetivo não suportado"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"foi tentado enviar uma mensagem com um tipo de objetivo não suportado"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"envio falhou com um socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"envio falhou com um socket winsock2"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"erro ao tentar abrir um socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Registro do Stumpless no Windows Event Log Source"

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
"não foi possível escrever na stream"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"o tamanho da string infratora"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"o tamanho da string excedeu o limite máximo"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"esse tipo de objetivo está sempre aberto"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"portas de transporte só são válidas para objetivos de rede"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"o protocolo de transporte escolhido não é válido"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"erro ao abrir um socket unix com a função socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"foi conferido se um tipo de objetivo não suportado estava aberto"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"não foi possível fechar o Windows Event Log"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"não foi possível abrir o Windows Event Log"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"não foi possível converter a string wide char dada para uma string multibyte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"o código de erro do Windows retornado pela chamada com erro"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"código de erro do Windows Socket"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"o resultado de GetLastError depois da chamada com erro"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"erro ao abrir um socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"o resultado de WSAGetLastError depois da chamada com erro"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_PT_BR_H */
