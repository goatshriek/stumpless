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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_PL_PL_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_PL_PL_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"nie można podłączyć do gniazda unix"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"bufor używany do przechowywania wiadomości"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"bufor jest za mały dla tej wiadomości"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"cele łańcuchowe nie są obsługiwane w tym buildzie"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"próba zamknięcia pliku docelowego nieobsługiwanego typu"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"próba wywołania CommitTransaction zakończyła się błędem"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"błąd połączenia z gniazdem sys/socket.h socketem"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"błąd połączenia winsock socketem"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"próba wywołania CreateTransaction zakończyła się błędem"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"podany plik docelowy jest ważny tylko dla miejsc docelowych w sieci"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"element o podanej nazwie już pojawia się w tym wejściu"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"nie można znaleźć elementu o określonej charakterystyce"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"połączenie zwróciło numer błędu (errno)"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"komunikat o błędzie - nie udało się otworzyć pliku"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"komunikat o błędzie - nie udało się zapisać"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"niepoprawny format " ARG

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"kod powrotu funkcji obsługi protokołu"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"obsługa protokołu dla celu funkcji nie powiodła się"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"funkcja getaddrinfor nie powiodła się podczas podawania nazwy hosta"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"wywołanie getaddrinfo zwróciło błąd zwracanej wartości"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"próba wywołania GetComputerName nie udana"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"próba wywołania gethostname zakończyła się błędem"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"wynik GetLastError po nieudanym wywołaniu"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"próba wywołania GetModuleFileNameW zakończyła się błędem"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"próba wywołania GetModuleHandleExW zakończyła się błędem"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"nieprawidłowy indeks - indeks jest zbyt duży, aby mógł być reprezentowany" \
" jako typ danych int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"niezgodne urządzenie"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"wartość kodu urządzenia, po podzieleniu przez 8, należy zdefiniować zgodnie" \
" z protokołem RFC 5424"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"nieprawidłowy cel ID"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"nieprawidłowy indeks " INDEXED_THING

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"wartość rejestru MULTI_SZ nie była ani pusta, ani zakończona dwoma znakami NULL" \

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"string nie jest w formacie name=\"value\""

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"nieprawidłowa usługa"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"kod serwisowy musi być zdefiniowany zgodnie ze standardem RFC 5424:" \
" wartości pomiędzy 0 a 7 łącznie z"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"nieprawidłowy stan osiągnięty podczas analizowania ciągu znaków UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"cel jest niekompatybilny z tą operacją"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"kod powrotu sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv przegrany"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"nie jest możliwe utworzenie pliku z wybraną nazwą gniazda lokalnego" \
" przy użyciu mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maksymalny rozmiar wiadomości obowiązuje tylko dla UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"wynik GetLastError po nie udanym wywołaniu"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"nie udało się przekonwertować podanego multi byte stringa do wide stringa"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"wywołanie alokacji pamięci nie powiodło się"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"rozmiar wiadomości, która próbowała je wysłać "

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"wiadomość jest zbyt duża, aby można ją było wysłać w jednym datagramie"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"funkcje gethostbyname[2] i inet_pton nie mogły rozpoznać nazwy"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"połączenie zostało zamknięte"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"wybrany protokół sieciowy nie jest obsługiwany"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"cele sieciowe nie są obsługiwane przez tę kompilację"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " miał wartość NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"podjęto próbę otwarcia celu nieobsługiwanego typu"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"określony parametr nie został znaleziony"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"nie udało się utworzyć podklucza rejestru"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"nie udało się usunąć podklucza rejestru"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"nie udało się otworzyć podklucza rejestru"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"nie udało się odczytać wartości rejestru"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"nie udało się ustawić wartości rejestru"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"próba wysłania do socketu unix nie udana"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"próba wysłania nieobsługiwanego typu danych wejściowych do celu"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"próba wysłania wejścia nieobsługiwanego typu"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"próba wysłania do socketu systemowego (sys/socket.h) nie udana"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"wysyłanie winsock2 socketu przegrany"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"kolory poziomów ważności są obsługiwane wyłącznie dla celów strumieniowych"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"otwór w gnieździe przegrany"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Rejestracja źródła dziennika zdarzeń Windows w Stumpless"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"nie udało się powiązać parametru " PARAM " z instrukcją"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"baza danych była zajęta i nie mogła sfinalizować transakcji"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"nie udało się zamknąć bazy danych sqlite3"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"wywolanie niestandardowego callbacka dla instrukcji przygotowanych nie powiodło się"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"nie udało się otworzyć bazy danych sqlite3"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 nieudane"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"wynik nieudanego wywołania sqlite3"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"liczba ponownych prób wykonania operacji"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"wywołanie sqlite3_step nie powiodło się"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3 targets nie są obsługiwane przez ten build"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"nie mogę pisać do streamu"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"długość łańcucha problemu to"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"długość ciągu przekroczyła maksymalny limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"cel danego typu jest nadal otwarty"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"porty transportowe są ważne tylko dla miejsc docelowych w sieci"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"wybrany protokół transportowy nie jest obsługiwany"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"błąd otwierania gniazda uniksowego przy użyciu funkcji gniazda"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"sprawdź rozszerzalność pliku docelowego nieobsługiwanego typu"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"nie można zamknąć dziennika zdarzeń systemowych Windows"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Kod błędu Windows Socket"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"nie udało się przekonwertować podanego multi byte stringa do wide stringa"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"błąd Windows zwrócony przez nieudane wywołanie"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"błąd zwracane wartości (error code) Windows socketu"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"wynik GetLastError po nieudanym wywolaniu"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"błąd otwierania winsock2 socketu"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"wynik WSAGetLastError po niepowodzeniu połączenia"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_PL_PL_H */
