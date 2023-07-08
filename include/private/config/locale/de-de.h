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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"konnte sich nicht an den lokalen Unix-Socket binden"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"Puffer ist zu klein für die gegebene Nachricht"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen nicht unterstützen Zieltyp zu schließen"

// todo translate
#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"Verbindung mit einem sys/socket.h-Socket fehlgeschlagen"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"Verbindung mit einem winsock2 fehlgeschlagen"

// todo translate
#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"Ziel ist nur für Netzwerkziele gültig"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"Ein Element mit dem angegeben Namen ist bereits in diesem Eintrag vorhanden"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"Ein Element mit den angegeben Eigenschafen konnte nicht gefunden werden"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"Errno nach dem fehlgeschlagenen Aufruf"

// todo translate
#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the specified file"

// todo translate
#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the file"

// todo translate
#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"return code of the log handler function"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"the log handler for a function target failed"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo schlug bei dem angegebenen Hostnamen fehl"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"Rückgabewert des fehlgeschlagegen getaddrinfo-Aufrufs"

// todo translate
#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName failed"

// todo translate
#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname failed"

// todo translate
#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW failed"

// todo translate
#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW failed"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"Der ungültige Index, oder -1 davon ist zu groß, um ihn als int" \
"darzustellen"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"Ungültige Einreichung"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"Einrichtungscodes müssen in Übereinstimmung mit RFC 5424 definiert werden, " \
"nach der Multiplikation mit 8"

// todo translate
#  define L10N_INVALID_ID_ERROR_MESSAGE \
"invalid target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"Ungültiger " INDEXED_THING " index"

// todo translate
#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ registry value was neither empty nor terminated with two NULL" \
" characters"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"Ungültiger Schweregrad"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"Schweregrad-Codes müssen in Übereinstimmung mit RFC 5424 definiert werden: " \
"Werte zwischen 0 und einschließlich 7"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

// todo translate
#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"target type is incompatible with this operation"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"return code of sd_journal_sendv"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv failed"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"Konnte mit mksetmp keine Datei mit dem gewählten lokalen " \
"Socket-Namen erzeugen"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"Die maximale Nachrichtengröße ist nur für UDP-Netzwerkziele gütlig"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"could not convert the provided multibyte string to a wide char string"

// todo translate
#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"a memory allocation call failed"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"Die Größe der Nachricht, die versucht wurde, gesendet zu werden"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"Die Nachricht ist zu groß um in einem einzigen Diagramm gesendet zu werden"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen network protocol is unsupported"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"Netzwerkziele werden von diesem Build nicht unterstützt"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " war NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen nicht unterstützten Zieltyp zu öffen"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"Ein Parameter mit den angegebenen Eigenschaften konnte nicht gefunden werden"

// todo translate
#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be created"

// todo translate
#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be deleted"

// todo translate
#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"a registry subkey could not be opened"

// todo translate
#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"a registry value could not be read"

// todo translate
#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"a registry value could not be set"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto mti einem Unix-Socket fehlgeschlagen"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht einen Eintrag an einen nicht unterstützten Zieltyp zu senden"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Es wurde versucht eine Nachricht an einen nicht unterstützen Zieltyp zu senden"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"Senden mit einem sys/socket.h-Socket fehlgeschlagen"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"Senden mit einem winsock2-Socket fehlgeschlagen"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"Konnte keinen Socket öffnen"

// todo translate
#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless registration of Windows Event Log Source"

// todo translate
#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the stream"

// todo translate
#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"the length of the offending string"

// todo translate
#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"length of string exceeded maximum limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"Dieser Zieltyp ist immer offen"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"Transportanschlüsse sind nur für Netzwerkziele gültig"

// todo translate
#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen transport protocol is unsupported"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"Es konnte kein Unix-Socket mit der Socket-Funktion geöffnet werden"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"Überprüft, ob ein nicht unterstützer Zieltyp geöffnet war"

// todo translate
#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"could not close the Windows Event Log"

// todo translate
#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the Windows Event Log"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

// todo translate
#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket Fehler Code"

// todo translate
#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"Es konnte kein winsock2-Socket geöffnet werden"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"Das Ergebnis von WSAGetLastError nach dem fehlgeschlagenen Aufruf"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_DE_DE_H */
