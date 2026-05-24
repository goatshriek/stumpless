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
 * United States English localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_NB_NO_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_NB_NO_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke binde til lokal unix socket"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer brukt for å lagre meldingen"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"bufferen er for liten for meldingen"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"kjedemål støttes ikke av dette buildet"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"forsøkte å lukke en ustøttet måltype"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction mislyktes"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"tilkobling mislyktes med en sys/socket.h socket"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"tilkobling mislyktes med en winsock2 socket"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction mislyktes"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destinasjon er kun gyldig for nettverksmål"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"et element med det oppgitte navnet finnes allerede i denne oppføringen"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"et element med de angitte egenskapene ble ikke funnet"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno etter det mislykkede kallet"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"kunne ikke åpne den angitte filen"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"kunne ikke skrive til filen"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"ugyldig " ARG " format"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"returnkode for loggbehandlerfunksjonen"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"loggbehandleren for et funksjonsmål mislyktes"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo mislyktes for det oppgitte vertsnavnet"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"returnkode for det mislykkede getaddrinfo-kallet"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName mislyktes"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname mislyktes"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"resultatet av GetLastError etter det mislykkede kallet"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW mislyktes"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW mislyktes"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"den ugyldige indeksen, eller -1 hvis den er for stor til å representeres som int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"den ugyldige fasiliteten"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"fasilitkoder må defineres i henhold til RFC 5424, etter" \
" multiplikasjon med 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"ugyldig mål-ID"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"ugyldig " INDEXED_THING " indeks"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"en MULTI_SZ-registerverdi var verken tom eller avsluttet med to NULL-tegn"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"strengen er ikke på formatet navn=\"verdi\""

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"den ugyldige prival-verdien"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"prival-koder må defineres i henhold til RFC 5424: verdier mellom 0" \
" og 255 inkludert"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"den ugyldige alvorlighetsgraden"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"alvorlighetsgrader må defineres i henhold til RFC 5424: verdier mellom 0" \
" og 7 inkludert"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"ugyldig tilstand nådd under UTF-8 strengparsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"måltypen er ikke kompatibel med denne operasjonen"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"returnkode for sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv mislyktes"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"kunne ikke opprette en fil med det valgte lokale kontaktnavnet ved hjelp av mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maksimal meldingsstørrelse er kun gyldig for UDP-nettverksmål"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"resultatet av GetLastError etter det mislykkede kallet"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"kunne ikke konvertere den oppgitte multibyte-strengen til en wide char-streng"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"et minneallokeringskall mislyktes"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"størrelsen på meldingen som ble forsøkt sendt"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"meldingen er for stor til å sendes i et enkelt datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] og inet_pton klarte ikke å løse opp navnet"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"nettverkstilkoblingen er lukket"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"valgt nettverksprotokoll støttes ikke"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"nettverksmål støttes ikke av dette buildet"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " var NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"forsøkte å åpne en ustøttet måltype"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"en parameter med de angitte egenskapene ble ikke funnet"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"en register subnøkkel kunne ikke opprettes"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"en register subnøkkel kunne ikke slettes"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"en register subnøkkel kunne ikke åpnes"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"en registerverdi kunne ikke leses"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"en registerverdi kunne ikke angis"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto mislyktes med en unix socket"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"forsøkte å sende en oppføring til en ustøttet måltype"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"forsøkte å sende en melding til en ustøttet måltype"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send mislyktes med en sys/socket.h socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"end mislyktes med en winsock2-socket"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"alvorlighetsfarger støttes kun for strømmål"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åpne en socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless-registrering av Windows-hendelsesloggkilde"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"kunne ikke binde " PARAM " til setningen"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"databasen var opptatt og kunne ikke fullføre transaksjonen"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"kunne ikke lukke sqlite3-databasen"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"en egendefinert tilbakeringing for forberedte setninger mislyktes"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"kunne ikke åpne sqlite3-databasen"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 mislyktes"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"returnkoden for det mislykkede sqlite3-kallet"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"antall ganger operasjonen ble forsøkt på nytt"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step mislyktes"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3-mål støttes ikke av dette buildet"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"kunne ikke skrive til strømmen"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"lengden på den problematiske strengen"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"strenglengden overskred maksimumsgrensen"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"denne måltypen er alltid åpen"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"transportporter er kun gyldige for nettverksmål"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"valgt transportprotokoll støttes ikke"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åpne en unix socket med socket-funksjonen"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"sjekket om en ustøttet måltype var åpen"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"kunne ikke lukke Windows-hendelsesloggen"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"kunne ikke åpne Windows-hendelsesloggen"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"kunne ikke konvertere den oppgitte wide char-strengen til en multibyte-streng"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"Windows-feilkoden returnert av det mislykkede kallet"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket-feilkode"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"resultatet av GetLastError etter det mislykkede kallet"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"kunne ikke åpne en winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"resultatet av WSAGetLastError etter det mislykkede kallet"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_NB_NO_H */
