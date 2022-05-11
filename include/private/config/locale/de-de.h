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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"konnte sich nicht an den lokalen Unix-Socket binden"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"Puffer ist zu klein für die gegebene Nachricht"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen nicht unterstützen Zieltyp zu schließen"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"L10N MISSING COMMIT TRANSACTION FAILED ERROR MESSAGE"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"Verbindung mit einem sys/socket.h-Socket fehlgeschlagen"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"Verbindung mit einem winsock2 fehlgeschlagen"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"L10N MISSING CREATE TRANSACTION FAILED ERROR MESSAGE"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"Ziel ist nur für Netzwerkziele gültig"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"Ein Element mit dem angegeben Namen ist bereits in diesem Eintrag vorhanden"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"Ein Element mit den angegeben Eigenschafen konnte nicht gefunden werden"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"Errno nach dem fehlgeschlagenen Aufruf"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"FILE OPEN FAILURE MESSAGE"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"FILE WRITE FAILURE MESSAGE"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"FUNCTION TARGET FAILURE CODE TYPE"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"FUNCTION TARGET FAILURE ERROR MESSAGE"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"Konnte mit mksetmp keine Datei mit dem gewählten lokalen " \
"Socket-Namen erzeugen"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo schlug bei dem angegebenen Hostnamen fehl"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"Rückgabewert des fehlgeschlagegen getaddrinfo-Aufrufs"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GETCOMPUTERNAME FAILED ERROR MESSAGE"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"GETHOSTNAME FAILED ERROR MESSAGE"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"GETLASTERROR ERROR CODE TYPE"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"Der ungültige Index, oder -1 davon ist zu groß, um ihn als int" \
"darzustellen"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"Ungültige Einreichung"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"Einrichtungscodes müssen in Übereinstimmung mit RFC 5424 definiert werden, " \
"nach der Multiplikation mit 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"INVALID ID ERROR MESSAGE"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"Ungültiger " INDEXED_THING " index"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"Ungültiger Schweregrad"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"Schweregrad-Codes müssen in Übereinstimmung mit RFC 5424 definiert werden: " \
"Werte zwischen 0 und einschließlich 7"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"JOURNALD FAILURE ERROR CODE"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"JOURNALD FAILURE ERROR MESSAGE"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"Die maximale Nachrichtengröße ist nur für UDP-Netzwerkziele gütlig"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"L10N MISSING MB TO WIDE CONVERSION ERROR CODE TYPE"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"L10N MISSING MB TO WIDE CONVERSION ERROR MESSAGE"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"MEMORY ALLOCATION FAILURE MESSAGE"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"Die Nachricht ist zu groß um in einem einzigen Diagramm gesendet zu werden"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"Die Größe der Nachricht, die versucht wurde, gesendet zu werden"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"NETWORK PROTOCOL UNSUPPORTED ERROR MESSAGE"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"Netzwerkziele werden von diesem Build nicht unterstützt"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " war NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen nicht unterstützten Zieltyp zu öffen"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"Ein Parameter mit den angegebenen Eigenschaften konnte nicht gefunden werden"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY SUBKEY CREATION FAILED ERROR MESSAGE"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"L10N MISSING REGISTRY VALUE SET FAILED ERROR MESSAGE"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen Eintrag an einen nicht unterstützten Zieltyp zu senden"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht eine Nachricht an einen nicht unterstützen Zieltyp zu senden"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"Senden mit einem sys/socket.h-Socket fehlgeschlagen"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto mti einem Unix-Socket fehlgeschlagen"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"Senden mit einem winsock2-Socket fehlgeschlagen"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"Konnte keinen Socket öffnen"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"STREAM WRITE FAILURE ERROR MESSAGE"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"Dieser Zieltyp ist immer offen"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"TRANSPORT PROTOCOL UNSUPPORTED ERROR MESSAGE"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"Transportanschlüsse sind nur für Netzwerkziele gültig"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"Es konnte kein Unix-Socket mit der Socket-Funktion geöffnet werden"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"Überprüft, ob ein nicht unterstützer Zieltyp geöffnet war"

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
"Windows Socket Fehler Code"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"Es konnte kein winsock2-Socket geöffnet werden"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"Das Ergebnis von WSAGetLastError nach dem fehlgeschlagenen Aufruf"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"STRING TOO LONG"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"STRING LENGTH ERROR CODE TYPE"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"INVALID TARGET TYPE ERROR MESSAGE"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H */
