/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2024 Joel E. Anderson
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
 * Romanian localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_RO_RO_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_RO_RO_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nu s-a putut lega la socketul unix local"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer folosit pentru a stoca mesajul"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"bufferul este prea mic pentru mesajul dat"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"țintele în lanț nu sunt suportate de această construcție"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"încercare de închidere a unui tip de țintă nesuportat"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction a eșuat"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"connect a eșuat cu un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"connect a eșuat cu un socket winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction a eșuat"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destinația este valabilă doar pentru ținte de rețea"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un element cu numele furnizat există deja în această intrare"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un element cu caracteristicile specificate nu a putut fi găsit"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno după apelul eșuat"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"nu s-a putut deschide fișierul specificat"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"nu s-a putut scrie în fișier"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"format " ARG " invalid"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"codul de returnare al funcției de gestionare a jurnalului"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"gestionarul de jurnal pentru o țintă de funcție a eșuat"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo a eșuat pe hostname-ul furnizat"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"codul de returnare al apelului getaddrinfo eșuat"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName a eșuat"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname a eșuat"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"rezultatul GetLastError după apelul eșuat"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW a eșuat"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW a eșuat"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"indexul invalid, sau -1 dacă este prea mare pentru a fi reprezentat ca int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"facilitatea invalidă"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"codurile de facilitate trebuie definite conform RFC 5424, după" \
" înmulțirea cu 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id țintă invalid"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"index " INDEXED_THING " invalid"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"o valoare MULTI_SZ din registry nu era nici goală nici terminată cu două" \
" caractere NULL"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"șirul nu este în formatul nume=\"valoare\""

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"privalul invalid"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"codurile prival trebuie definite conform RFC 5424: valori între 0" \
" și 255 inclusiv"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"severitatea invalidă"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"codurile de severitate trebuie definite conform RFC 5424: valori între 0" \
" și 7 inclusiv"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"stare invalidă atinsă în timpul analizei șirului UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"tipul de țintă este incompatibil cu această operație"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"codul de returnare al sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv a eșuat"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nu s-a putut crea un fișier cu numele de socket local ales folosind mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"dimensiunea maximă a mesajului este valabilă doar pentru ținte de rețea UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"rezultatul GetLastError după apelul eșuat"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"nu s-a putut converti șirul multibyte furnizat într-un șir de caractere wide"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"un apel de alocare a memoriei a eșuat"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"dimensiunea mesajului care s-a încercat a fi trimis"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"mesajul este prea mare pentru a fi trimis într-un singur datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] și inet_pton nu au reușit să rezolve numele"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"conexiunea de rețea este închisă"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protocolul de rețea ales nu este suportat"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"țintele de rețea nu sunt suportate de această construcție"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " era NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"încercare de deschidere a unui tip de țintă nesuportat"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un parametru cu caracteristicile specificate nu a putut fi găsit"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"o subcheie de registry nu a putut fi creată"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"o subcheie de registry nu a putut fi ștearsă"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"o subcheie de registry nu a putut fi deschisă"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"o valoare de registry nu a putut fi citită"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"o valoare de registry nu a putut fi setată"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto a eșuat cu un socket unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"încercare de trimitere a unei intrări către un tip de țintă nesuportat"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"încercare de trimitere a unui mesaj către un tip de țintă nesuportat"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send a eșuat cu un socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send a eșuat cu un socket winsock2"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"culorile de severitate sunt suportate doar pentru ținte de tip stream"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"nu s-a reușit deschiderea unui socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Înregistrarea Stumpless a sursei de Evenimente Windows"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"nu s-a putut lega " PARAM " de instrucțiune"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"baza de date era ocupată și nu a putut finaliza tranzacția"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"nu s-a putut închide baza de date sqlite3"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"un callback personalizat pentru instrucțiuni pregătite a eșuat"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"nu s-a putut deschide baza de date sqlite3"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 a eșuat"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"codul de returnare al apelului sqlite3 eșuat"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"numărul de ori cât operația a fost reîncercată"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step a eșuat"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"țintele sqlite3 nu sunt suportate de această construcție"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"nu s-a putut scrie în flux"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"lungimea șirului ofensator"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"lungimea șirului a depășit limita maximă"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"acest tip de țintă este întotdeauna deschis"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"porturile de transport sunt valabile doar pentru ținte de rețea"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"protocolul de transport ales nu este suportat"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nu s-a reușit deschiderea unui socket unix cu funcția socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"s-a verificat dacă un tip de țintă nesuportat era deschis"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"nu s-a putut închide Jurnalul de Evenimente Windows"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"nu s-a putut deschide Jurnalul de Evenimente Windows"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"nu s-a putut converti șirul de caractere wide furnizat într-un șir multibyte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"codul de eroare Windows returnat de apelul eșuat"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"cod de eroare Socket Windows"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"rezultatul GetLastError după apelul eșuat"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"nu s-a reușit deschiderea unui socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"rezultatul WSAGetLastError după apelul eșuat"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_RO_RO_H */
