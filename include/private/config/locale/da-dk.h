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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_DA_DK_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_DA_DK_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke binde til den lokale unix Socket"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer er for lilel til den givne besked"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"prøvede at lukke en ikke støttet måltype"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction(begå transaktion) fejlede"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"forbind fejlede med et sys/socket.h socket"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"forbind fejlede med et winsock2 socket"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction(lav transaktion) fejlede"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destination er kun gyldigt for netværk mål"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"et element med det givne navn findes allerede i denne entry"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"et element med de speciferede karakteristika kunne ikke findes"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno efter det fejlede kald"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"kunne ikke åbne den speciferede fil"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"kunne ikke skrive til files"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"ugyldigt " ARG " format"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"retuner koden af log handler funktionen"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"log handleren for et funtionsmål fejlede"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo fejlede på det givne hostnavn"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"retuner koden af the fejlede getaddrinfo kald"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName fejlede"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname fejlede"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"resultatet af GetLastError efter det fejlede kald"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW fejlede"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW fejlede"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"det ugyldige index, eller -1 af det er for stor til at representere som en int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"den ugyldige facilitet"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"facilitets koder skal være defineret i Overensstemmelse med RFC 5424, efter" \
"multiplikationen med 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"ugyldigt mål id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"ugyldigt " INDEXED_THING " index"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"en MULTI_SZ registreringsdatabase værdi var hverken tom eller Afsluttet " \
" characters med to NULL's"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"den ugyldige alvorlighed"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"alvorligheds koder skal være defineret i Overensstemmelse med RFC 5424:" \
" værdier mellem 0 og 7 inklusivt"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"ugyldig stat nået under UTF-8 streng parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"måltype er uforenelig med denne operation"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"retur kode af sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv fejlede"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"kunne ikke lave en fejl med det valgte lokale socket navn ved brug af mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"max besked størrelse er kun gyldigt for UDP nætværk mål "

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"resultatet af GetLastError efter det fejlede kald"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"kunne ikke konvertere den givne multibyte streng til en bred char streng"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"et memory allocation kald fejlede"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"størrelsen på beskeden der blev forsøgt at blive sendt"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"beskeden er for stor til at blive sendt i et enkelt diagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] og inet_pton fejlede i at løse navnet"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"valgte nætværks protokol er ikke støttet"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"netværk mål er ikke støttet af dette build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " var NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"prøvede at åbne en ikke støttet måltype"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"et parameter med de speciferede karakteristika kunne ikke blive fundet"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"en registreringsdatabase subkey kunne ikke blive oprettet"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"en registreringsdatabase kunne ikke blive slettet"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"en registreringsdatabase subkey kunne ikke blive åbnet"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"en registreringsdatabase værdi kunne ikke blive læst"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"en registreringsdatabase værdi kunne ikke blive sat"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto fejlede med et unix socket"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"prøvede at sende en indtræden til en ikke støttet måltype"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"prøvede at sende en besked til en ikke støttet måltype"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send fejlede med et sys/socket.h socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send fejlede med et winsock2 socket"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åbne et socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
"Stumpless registration af Windows Event Log kilde"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"kunne ikke skrive til strømmen"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"længden på den ulovlige streng"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"længde af streng overskrider den maksimale længde"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"denne måltype er altid åben"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"transport porte er kun gyldige for netværksmål"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"valgte transport protokol er ikke understøttet"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åbne en unix socket med socket funktion"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"tjekkede for om en ikke støttet måltype var åben"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"kunne ikke lukke Windows Event Loggen"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"kunne åbne lukke Windows Event Loggen"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"kunne ikke konvertere den givne brede char streng til en multibyte streng"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"Windows fejlkoden retunerede af det fejlede kald"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket fejlkode"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"resultatet af GetLastError efter det fejlede kald"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åbne et winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"resultatet af WSAGetLastError efter det fejlede"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_DA_DK_H */
