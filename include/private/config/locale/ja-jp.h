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
 * Japanese localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_JA_JP_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_JA_JP_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"ローカルの UNIX ソケットにバインドできませんでした"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"指定されたメッセージに対してバッファが小さすぎます"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"サポートされていないターゲット タイプを閉じようとしました"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction が失敗しました"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h ソケットでの接続に失敗しました"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 ソケットでの接続に失敗しました"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction が失敗しました"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"宛先はネットワーク ターゲットに対してのみ有効です"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"指定された名前の要素がこのエントリにすでに存在します"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"指定された特性を持つ要素が見つかりませんでした"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"失敗した呼び出し後の errno"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"指定されたファイルを開けませんでした"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"ファイルに書き込めませんでした"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"無効な " ARG " 形式"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"ログハンドラ関数のリターンコード"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"関数ターゲットのログハンドラーが失敗しました"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"指定されたホスト名で getaddrinfo が失敗しました"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"失敗した getaddrinfo 呼び出しの戻りコード"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName が失敗しました"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname が失敗しました"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"呼び出しが失敗した後の GetLastError の結果"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW が失敗しました"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW が失敗しました"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"無効なインデックス、またはその -1 が大きすぎて int として表現できない"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"無効な施設"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"施設コードは、8 を乗算した後、RFC 5424 に従って定義する必要があります。"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"無効なターゲットID"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"無効な " INDEXED_THING " インデックス"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ レジストリ値は空でも、2 つの NULL 文字で終了していませんでした"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"文字列は 名前=\"価値\" 形式ではありません"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"無効な重大度"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"重大度コードは RFC 5424 に従って定義する必要があります。値は 0 と 7 です。"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"UTF-8 文字列の解析中に無効な状態に達しました"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"ターゲット タイプはこの操作と互換性がありません"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendvのリターンコード"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv が失敗しました"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp を使用して、選択したローカル ソケット名のファイルを作成できませんでした"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"最大メッセージ サイズは UDP ネットワーク ターゲットに対してのみ有効です"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"呼び出しが失敗した後の GetLastError の結果"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"指定されたマルチバイト文字列をワイド文字列に変換できませんでした"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"メモリ割り当て呼び出しが失敗しました"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"送信しようとしたメッセージのサイズ"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"メッセージが大きすぎて単一のデータグラムで送信できない"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] と inet_pton が名前の解決に失敗しました"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"ネットワーク接続が閉じられています"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"選択したネットワーク プロトコルはサポートされていません"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"ネットワーク ターゲットはこのビルドではサポートされていません"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME "NULL でした"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"サポートされていないターゲット タイプを開こうとしました"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"指定された特性を持つパラメータが見つかりませんでした"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"レジストリ サブキーを作成できませんでした"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"レジストリ サブキーを削除できませんでした"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"レジストリのサブキーを開けませんでした"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"レジストリ値を読み取れませんでした"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"レジストリ値を設定できませんでした"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"UNIX ソケットで sendto が失敗しました"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"サポートされていないターゲット タイプにエントリを送信しようとしました"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"サポートされていないターゲット タイプにメッセージを送信しようとしました"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h ソケットで送信が失敗しました"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 ソケットで送信に失敗しました"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"ソケットを開けませんでした"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless Windows イベント ログ ソースの登録"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
PARAM " をステートメントにバインドできませんでした"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"データベースがビジー状態のため、トランザクションを完了できませんでした"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"sqlite3データベースを閉じることができませんでした"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"準備されたステートメントのカスタム コールバックが失敗しました"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"sqlite3データベースを開けませんでした"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 が失敗しました"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"失敗したsqlite3呼び出しのリターンコード"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"操作が再試行された回数"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step が失敗しました"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"sqlite3 ターゲットはこのビルドではサポートされていません"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"ストリームに書き込めませんでした"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"問題のある文字列の長さ"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"文字列の長さが最大制限を超えました"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"このターゲット タイプは常にオープンです"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"トランスポート ポートはネットワーク ターゲットに対してのみ有効です"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"選択したトランスポート プロトコルはサポートされていません"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"ソケット関数を使用して UNIX ソケットを開けませんでした"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"サポートされていないターゲット タイプが開いているかどうかを確認するためにチェックされました"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"Windows イベント ログを閉じることができませんでした"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Windowsイベントログを開けませんでした"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"指定されたワイド文字列をマルチバイト文字列に変換できませんでした"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"失敗した呼び出しによって返された Windows エラー コード"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windowsソケットエラーコード"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"呼び出しが失敗した後の GetLastError の結果"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 ソケットを開けませんでした"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"呼び出しが失敗した後の WSAGetLastError の結果"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_JA_JP_H */
