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
 * Turkey Turkish localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_TR_TR_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_TR_TR_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"yerel unix soketine bağlanamadı"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"tampon bellek verilen mesaj için çok küçük"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"desteklenmeyen hedef tipi kapatılmaya çalışıldı"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction başarısız oldu"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h soketi ile bağlantı başarısız oldu"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 soketi ile bağlantı başarısız oldu"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction başarısız oldu"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"hedefte sadece ağ hedefleri için geçerlidir"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"verilen isimde bir eleman bu girişte zaten mevcut"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"verilen karakteristiklerde bir öğe bulunamadı"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"başarısız çağrıdan sonra errno"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"belirtilen dosya açılamadı"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"dosyaya yazılamadı"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"geçersiz " ARG " formatı"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"kaydedicinin(logger) geri dönüş kodu"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"fonksiyon hedefi için kaydedici(log handler) başarısız oldu"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo verilen bilgisayar adı(hostname) için başarısız oldu"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"getaddrinfo çağrısın hata kodu tipi"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName başarısız oldu"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname başarısız oldu"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"başarısız çağrıdan sonraki GetLastError'ün sonucu"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW başarısız oldu"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW başarısız oldu"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"geçersiz indeks veya -1 olanı gösterilemeyecek kadar büyük"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"geçersiz tesis(facility)"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"facility kodları 8 ile çarpımdan sonra" \
"RFC 5424'e uygun olarak tanımlanmalıdır"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"geçersiz hedef id'si"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"geçersiz " INDEXED_THING " indeksi"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ kayıt defteri hem boş değildi, hem de" \
"iki NULL karakterle sonlandırılmamıştır"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"string name=\"value\" biçiminde değil"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"geçersiz önem derecesi(severity)"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"önem derecesi(severity) kodları RFC 5424'e uygun olarak tanımlanmalıdır:" \
"0 ve 7 arasındaki değerler, 7 dahil"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"UTF-8 string yorumlama sırasında geçersiz duruma ulaşıldı"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"hedef tipi(target type) bu operasyonla uyumlu değil"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendv'nin geri dönüş kodu"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv başarısız oldu"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp kullanılırken seçilen yerel soket ismiyle dosya oluşturulamadı"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"maksimum mesaj boyutu sadece UDP ağ hedefleri için geçerlidir."

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"başarısız çağrıdan sonraki GetLastError'ün sonucu"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"sağlanan çok baytlı string geniş karakter dizisine(wide char string)" \
"dönüştürülemedi."

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"bir bellek ayırma çağrısı başarısız oldu"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"gönderilmeye çalışılan mesajın boyutu"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"mesaj tek bir datagramda göndermek için fazla büyük"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] ve inet_pton ismi çözümleyemedi"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"seçilen ağ protokolü desteklenmiyor"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"ağ hedefleri bu derleme için desteklenmiyor"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " NULL idi"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"desteklenmeyen bir hedef tipi açılmaya çalışıldı"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"belirtilen özelliklere sahip bir param bulunamadı"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"kayıt defteri alt anahtarı(registry subkey) oluşturulamadı"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"kayıt defteri alt anahtarı(registry subkey) silinemedi"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"kayıt defteri alt anahtarı(registry subkey) açılamadı"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"kayıt defteri(registry) değeri okunamadı"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"kayıt defteri(registry) değeri ayarlanamadı"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"unix soketi ile sendto başarısız oldu"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"desteklenmeyen hedef türüne girdi(entry) gönderilmeye çalışıldı"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"desteklenmeyen hedef türüne mesaj gönderilmeye çalışıldı"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h soketi ile gönderme başarısız oldu"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 soketi ile gönderme başarısız oldu"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"soket açılamadı"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Windows Olay Günlüğü kaynağının Stumpless Kaydı"

// todo translate
#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"could not bind " PARAM " to the statement"

// todo translate
#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"the database was busy and could not complete the transaction"

// todo translate
#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"could not close the sqlite3 database"

// todo translate
#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"a custom callback for prepared statements failed"

// todo translate
#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"could not open the sqlite3 database"

// todo translate
#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 failed"

// todo translate
#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"the return code of the failed sqlite3 call"

// todo translate
#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"the number of times the operation was retried"

// todo translate
#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step failed"

// todo translate
#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3 targets are not supported by this build"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"akışa(stream) yazılamadı"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"offending string'in uzunluğu"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"dizenin(string) uzunluğu maksimum boyutu geçti"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"bu hedef tipi her zaman açık"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"aktarım portları yalnızca ağ hedefleri için geçerlidir"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"seçilen aktarım protokolü desteklenmiyor"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"socket fonksiyonu ile bir unix soketi açılamadı"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"desteklenmeyen bir hedef türünün açık olup olmadığını kontrol etti"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"Windows Olay Günlüğü kapatılamadı"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Windows Olay Günlüğü açılamadı"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"verilen geniş karakter dizesi(wide char string) çok baytlı" \
"dizeye(multibye string) dönüştürülemedi"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"başarısız çağrıdan döndürülen Windows hata kodu"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows soketinin hata kodu"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"başarısız çağrıdan sonraki GetLastError'ün sonucu"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 soketi açılamadı"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"başarısız çağrıdan sonraki WSAGetLastError'ün sonucu"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_TR_TR_H */
