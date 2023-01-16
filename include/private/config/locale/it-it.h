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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_IT_IT_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_IT_IT_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"bind con socket locale unix fallita"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"il buffer è troppo piccolo per il messaggio"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentativo di chiusura di un target non supportato"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction fallita"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"connect fallita con un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"connect fallita con un socket winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction fallita"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"la destinazione è valida solo per target di rete"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un elemento con il nome dato è già presente in questa voce"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"non è stato possibile trovare un elemento con le caratteristiche date"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno dopo la chiamata fallita"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"non è stato possibile aprire un file con il nome scelto"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"non è stato possibile scrivere al file scelto"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formato di " ARG " non valido"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"il codice di ritorno della chiamata funzione fallita"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"la funzione per un target di funzione fallita"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo fallita con l'hostname dato"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"il codice di ritorno della chiamata getaddrinfo fallita"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName fallita"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname fallita"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"il risultato di GetLastError dopo la chiamata fallita"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW fallita"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW fallita"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"l'indice non valido, oppure -1 se è troppo grande da rappresentare con un int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"il servizio non valido"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"i codici di servizio devono essere definiti in osservanza del RFC 5424," \
" dopo la moltiplicazione per 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"target id non valido"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"indice " INDEXED_THING " non valido"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"un valore MULTI_SZ nel registro non è nè vuoto nè terminato con due" \
" caratteri nullo"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"gravità non valida"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"i codici gravità devono essere definiti in osservanza del RFC 5424: tra 0" \
" e 7, compreso"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"il tipo di target è incompatibile con questa operazione"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"il codice di ritorno della chiamata sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv fallita"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"non è stato possibile creare un file con il nome scelto per la socket" \
" locale usando mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"la dimensione massima del messaggio è solo valido per target di rete UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"il risultato di GetLastError dopo la chiamata fallita"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"non è stato possibile convertire una stringa multibyte a una stringa \"wide\""

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"una chiamata di allocazione della memoria fallita"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"la dimensione del messaggio che si è tentato di inviare"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"il messaggio è troppo grande per essere inviato in unico datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] e inet_pton fallita realizzare il nome"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"il protocollo di rete non è supportato"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"i target di rete non sono supportati in questa build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " era NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentativo di apertura di un target di tipo non supportato"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"non è stato possibile trovare un parametro con le caratteristiche definite"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"non è stato possibile creare una chiave nel registro"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"non è stato possibile eliminare una chiave nel registro"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"non è stato possibile aprire una chiave nel registro"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"non è stato possibile leggere un valore nel registro"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"non è stato possibile assegnare un valore nel registro"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto fallita con un socket unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentativo di invio di una voce a un tipo di target non supportato"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentativo di invio di un messaggio a un tipo di target non supportato"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send fallita con un socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send fallita con un socket winsock2"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"fallita apertura di un socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"la registrazione per Stumpless di Windows Event Log Source"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"non è stato possibile scrivere al stream"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"la lunghezza della stringa non valida"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"la lunghezza della stringa eccede il limite massimo"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"questo tipo di target è sempre aperto"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"le porte di trasporto sono solo valide per target di rete"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"il protocollo di trasporto non è supportato"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"fallita apertura di un socket unix usando la funzione socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"controllato se un tipo di target non supportato era aperto"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"non è stato possibile chiudere il Windows Event Log"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"non è stato possibile aprire il Windows Event Log"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"non è stato possibile convertire una stringa \"wide\" a una stringa multibyte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"il codice di errore di ritorno della chiamata fallita"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"codice di errore di Windows Socket"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"il risultato di GetLastError dopo la chiamata fallita"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"fallita apertura di un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"il risultato di WSAGetLastError dopo la chiamata fallita"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_IT_IT_H */
