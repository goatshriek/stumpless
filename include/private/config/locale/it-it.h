/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2020 Joel E. Anderson
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
"non ha potuto legare il unix socket locale"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"il buffer è troppo piccolo per il messaggio"

#  define L10N_CHECK_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TYPE OF TARGET"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ha provato chiudere un tipo di bersaglio non supportato"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"connect ha fallito con un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"connect ha fallito con un socket winsock2"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"la destinazione è solo valida per bersaglio rete"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un elemento con il nome dato è già in questa voce"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un elemento con le caratteristiche date non ha potuto essere trovato"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno dopo il fallimento"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"non ha potuto costruire un file con il nome socket dato con mkstemp"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo ha fallito con l'hostname dato"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"il codice ritornato del getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName ha fallito"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname ha fallito"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"il risultato di GetLastError dopo il fallimento"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"l'indice non valido, oppure -1 se è troppo grande rappresentare come un int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"il servizio non valido"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"i codici servizio devono soddisfare RFC 5424, dopo la moltiplicazione con 8"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"non valido " INDEXED_THING " indice"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la gravità non valida"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"i codici gravità devono soddisfare RFC 5424: tra 0 e 7, compreso"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"il massimo dimensione è solo valido per i bersagli reti UDP"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"il messaggio è troppo grande per mandare in unico datagram"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"la dimensione del messagio"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"i bersagli reti non sono supportato"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " era NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ha provato aprire un tipo di bersaglio non supportato"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un parametro con le caratteristiche date non ha potuto essere trovato"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ha provato mandare una voce a un tipo di bersaglio non supportato"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ha provato mandare un messaggio a un tipo di bersaglio non supportato"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send ha fallito con un socket sys/socket.h"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto ha fallito con un socket unix"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send ha fallito con un socket winsock2"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"ha fallito aprire un socket"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"questo tipo di bersaglio è sempre aperto"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"i porti trasporti sono solo valido per bersagli reti"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"ha fallito aprire un socket unix usando la funzione socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"ha controllato se un tipo di bersaglio non supportato era aperto"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"il codice errore di Windows Socket"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"ha fallito aprire un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"il risultato di WSAGetLastError dopo il fallimento"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"la lunghezza della stringa era troppo lunga"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"la lunghezza della stringa non valida"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"il formato di " ARG " era non valido"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_IT_IT_H */
