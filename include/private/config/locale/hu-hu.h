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

/** @file
 * Hungarian localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_HU_HU_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_HU_HU_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nem tudott csatlakozni a helyi unix foglalathoz"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"a puffer túl kicsi az adott üzenethez"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"nem támogatott céltípust próbált bezárni"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"A CommitTransaction sikertelen"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"kapcsolat sikertelen a sys/socket.h aljzattal"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"a csatlakozás sikertelen winsock2 aljzattal"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"A CreateTransaction nem sikerült"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"cél csak hálózati célokra érvényes"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"a megadott nevű elem már szerepel ebben a bejegyzésben"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"a megadott jellemzőkkel rendelkező elem nem található"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno a sikertelen hívás után"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"nem tudta megnyitni a megadott fájlt"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"nem tudott írni a fájlba"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"érvénytelen " ARG " formátum"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"a naplókezelő függvény visszatérési kódja"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"egy függvénycél naplókezelője meghiúsult"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"A getaddrinfo nem sikerült a megadott gazdagépnéven"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"a sikertelen getaddrinfo hívás visszatérési kódja"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"A GetComputerName nem sikerült"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"A gethostname nem sikerült"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"a GetLastError eredménye a sikertelen hívás után"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"A GetModuleFileNameW nem sikerült"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"A GetModuleHandleExW nem sikerült"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"az érvénytelen index, vagy annak -1 értéke túl nagy ahhoz, hogy int-ként" \
" jelenítse meg"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"az érvénytelen létesítmény"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"a létesítménykódokat az RFC 5424 szerint kell meghatározni a 8-cal" \
" való szorzás után"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"érvénytelen célazonosító"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"érvénytelen " INDEXED_THING " index"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ rendszerleíró adatbázis értéke nem volt üres, és nem fejeződött" \
" be két NULL karakterrel"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"a karakterlánc nem név=\"érték\" formátumú"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"az érvénytelen súlyosság"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"a súlyossági kódokat az RFC 5424 szerint kell meghatározni: 0" \
" és 7 közötti értékek"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"érvénytelen állapot az UTF-8 karakterlánc-elemzés során"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"céltípus nem kompatibilis ezzel a művelettel"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendv visszatérési kódja"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"A sd_journal_sendv nem sikerült"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nem tudott fájlt létrehozni a kiválasztott helyi socket névvel az" \
" mkstemp használatával"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"A maximális üzenetméret csak UDP hálózati célokra érvényes"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"a GetLastError eredménye a sikertelen hívás után"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"nem tudta konvertálni a megadott többbájtos karakterláncot széles " \
" karakterláncra"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"egy memóriafoglalási hívás meghiúsult"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"az elküldeni próbált üzenet mérete"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"az üzenet túl nagy ahhoz, hogy egyetlen datagramban elküldhető legyen"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] és inet_pton nem tudta feloldani a nevet"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"a kiválasztott hálózati protokoll nem támogatott"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"a hálózati célokat ez a build nem támogatja"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " volt NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"nem támogatott céltípust próbált megnyitni"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"a megadott jellemzőkkel rendelkező paraméter nem található"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"beállításjegyzék alkulcs nem hozható létre"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"a beállításjegyzék alkulcsát nem lehetett törölni"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"a beállításjegyzék alkulcsát nem lehetett megnyitni"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"rendszerleíró adatbázis értéke nem olvasható"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"rendszerleíró adatbázis értéke nem állítható be"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"A sendto nem sikerült unix sockettel"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"megpróbált bejegyzést küldeni egy nem támogatott céltípusnak"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"megpróbált üzenetet küldeni egy nem támogatott céltípusnak"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"a küldés nem sikerült sys/socket.h sockettel"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"a küldés nem sikerült winsock2 sockettel"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"nem sikerült kinyitni az aljzatot"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"A Windows eseménynapló-forrásának Stumpless regisztrációja"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"nem tudta a " PARAM " paramétert az utasításhoz kötni"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"az adatbázis foglalt volt, és nem tudta befejezni a tranzakciót"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"nem tudta bezárni az sqlite3 adatbázist"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"az elkészített utasítások egyéni visszahívása meghiúsult"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"nem tudta megnyitni az sqlite3 adatbázist"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"A sqlite3_prepare_v2 nem sikerült"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"a sikertelen sqlite3 hívás visszatérési kódja"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"hányszor próbálkoztak újra a művelettel"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"A sqlite3_step nem sikerült"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"Ez a build nem támogatja az sqlite3 célokat"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"nem tudott írni az adatfolyamba"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"a szabálysértő karakterlánc hossza"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"a karakterlánc hossza túllépte a maximális korlátot"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ez a céltípus mindig nyitva van"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"A szállítási portok csak hálózati célokra érvényesek"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"a kiválasztott szállítási protokoll nem támogatott"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nem sikerült kinyitni egy unix foglalatot socket funkcióval"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"ellenőrizte, hogy nincs-e nyitva egy nem támogatott céltípus"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"nem tudta bezárni a Windows eseménynaplót"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"nem tudta megnyitni a Windows eseménynaplót"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"nem tudta konvertálni a megadott széles karakterláncot többbájtos" \
" karakterláncsá"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"a sikertelen hívás által visszaadott Windows hibakód"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket hibakód"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"a GetLastError eredménye a sikertelen hívás után"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"nem sikerült megnyitni egy winsock2 aljzatot"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"a WSAGetLastError eredménye a sikertelen hívás után"

#endif //STUMPLESS_HU_HU_H