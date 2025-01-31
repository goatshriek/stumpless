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
 * Albanian localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_SQ_AL_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_SQ_AL_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nuk mund të bëhej lidhja me unix prizën (socket-ën) lokale"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer-i është shumë i vogël për mesazhin e dhënë"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"u provua të mbyllej një lloj caku (targeti) i papërkrahur"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction (thirrja Kryej Transaksionin) dështoi"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"dështoi lidhja me një prizë (socket) sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"dështoi lidhja me një prizë (socket) winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction (thirrja Krijo Transaksionin) dështoi"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destinacioni është valid vetëm për caqe (targetët) rrjeti"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"një element me emrin e dhënë veçse është i pranishëm në këtë hyrje"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"një element me karakteristikat e specifikuara nuk mund të gjendej"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno pas thirrjes së dështuar"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"nuk mund të hapej fajlli i specifikuar"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"nuk mund të shkruhej në fajllin e specifikuar"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formati " ARG " jo-valid"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"kodi i kthyer nga funksioni që trajton evidentimin (logging)"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"trajtuesi i evidentimit për një funksion të synuar dështoi"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo dështoi në hostname-in e dhënë"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"kodi përgjegjës i thirrjes së dështuar getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName dështoi"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname dështoi"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"rezultati i GetLastError pas thirrjes së dështuar"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW dështoi"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW dështoi"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"indeks jo-valid, ose -1 në qoftë se vlera është shumë e madhe" \
"për të qenë numër i plotë (integer)"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"pajisje (facility) jo-valide"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"koded e pajisjes (facility) duhet të definohen në përputhshmëri" \
"me RFC 5424, pas shumëzimit me 8" 

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id-ja e cakut (target) jo-valide"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"indeks " INDEXED THING " jo-valid"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"vlera e një regjistri MULTI_SZ as nuk ishte e zbrazët" \
"dhe as nuk mbarohej me dy karaktere NULL"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"string-u nuk është i formatit name=\"value\""

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"rëndësia jo-valide"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"koded e rëndësisë duhet të definohen në përputhshmëri" \
" me RFC 5424: vlera duhet të jetë në mes 0" \
" dhe 7 (duke përfshirë)"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"gjendja jo-valide u arrit gjatë analizës (parsing) të string-ut UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"lloji i cakut (target) nuk është i përputhshëm me këtë veprim"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"kodi i kthyer nga sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv dështoi"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nuk mund të krijohej fajlli me emrin lokal të prizës" \
"(socket-ës) duke përdorur mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"gjatësia maksimale e mesazhit është valide vetëm për caqe" \
"(targetë) në rrjet UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"rezultati i GetLastError pas thirrjes së dështuar"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"nuk mund të kthehej string-u multibyte i dhënë në një string wide char"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"një thirrje për ndarje të memories dështoi"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"madhësia e mesazhit i cili u provua të dërgohej"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"mesazhi është shumë i madh për tu dërguar me një datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] dhe inet_pton dështuan të zgjidhin emrin"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protokolli i rrjetës i zgjedhur nuk përkrahet"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"caqet (targetët) në rrjet nuk përkrahen në këtë ndërtim (build)"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " ishte NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"u provua të hapej një lloj caku (targeti) i pa përkhaur"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"një parametër me karakteristikat e specifikuara nuk mund të gjendej"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"një nënçelës i regjistrit (registry subkey) nuk mund të krijohej"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"një nënçelës i regjistrit nuk mund të fshihej"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"një nënçelës i regjistrit nuk mund të hapej"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"një vlerë regjistri nuk mund të lexohej"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"një vlerë regjistri nuk mund të vendosej"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto dështoi me një prizë (socket) të unix-it"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"u provua të dergohej një hyrje në një lloj caku (targeti) të papërkrahur"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"u provua të dërgohej një mesazh në një lloj caku (targeti) të papërkrahur"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"dërgimi dështoi me një prizë (socket) të tipit sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"dërgimi dështoi me një prizë (socket) të tipit winsock2"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"dështoi hapja e një prize (socket-e)"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless regjistrimi i Windows Event Log Source"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"nuk mund të lidhej " PARAM " me shprehjen"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"baza e të dhënave ishte e zënë dhe nuk mundi të kryej transaksionin"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"nuk mund të mbyllej databaza sqlite3"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"një thirrje mbrapa (callback) i kustomizuar" \
"për shprehjen e pregaditur dështoi"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"nuk mund të hapej databaza sqlite3"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 dështoi"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"kodi i përgjigjes së sqlite3 thirrjes së dështuar"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"numri i herëve që veprimi është marrur"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step dështoi"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3 caqet (targetët) nuk janë të përkrahur nga ky ndërtim"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"nuk mund të shkruhej në rrjedhë"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"gjatësia e string-ut ofendues"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"gjatësia e string-ut që ka tejkaluar limitin"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ky lloj caku (targeti) është gjithmonë i hapur"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"portet e transportit janë valide vetëm për caqe (targetë) rrjeti"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protokolli i zgjedhur i transportit nuk përkrahet"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"dështoi hapja e një unix prize (socket-e) me një funksion prizë (socket)"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"u kontrollua për të parë nëse një tip caku (targeti)" \
"i papërkrahur ishte i hapur"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"nuk mund të mbyllej Windows Event Log"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"nuk mund të hapej Windows Event Log"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"nuk mund të kthehej string-u i dhënë wide char në një string multibyte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"Window kodi i gabimit i kthyer nga thirrja e dështuar"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket kodi i gabimit"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"rezultati i GetLastError pas thirrjes së dështuar"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"dështoi hapja e një winsock2 prize (socket-e)"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"rezultati i WSAGetLastError pas thirrjes së dështuar"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_SQ_AL_H */
