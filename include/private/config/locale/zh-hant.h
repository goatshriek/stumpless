/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions ands
 * limitations under the License.
 */

/* Warning: This Language Docmention use translate with robot. Please
 * help us to keep them readable.
 * For Traditional Chinese Users(對中文用戶):
 * 警告：這個語言文檔是機翻的。請幫助我們保持他們可讀。
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_HANT_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_HANT_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"無法綁定到本地unix socket"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"用於存儲訊息的緩衝區"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"緩衝區對於給定訊息太小"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"此版本不支援鏈式目標"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"試圖關閉不支援的目標類型"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction失敗"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"使用sys/socket.h時socket連線失敗"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"使用winsock2時socket連線失敗"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction失敗"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"目標僅對網路目標有效"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"此條目中已存在具有提供名稱的element"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"找不到具有指定特徵的element"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"失敗的調用errno"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"無法打開指定的檔案"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"無法寫入檔案"

#  define L10N_FORMAT_ERROR_MESSAGE( ARG ) \
"無效 " ARG " 格式"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"日誌處理程序函數的返回代碼"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"函數目標的日誌處理程序失敗"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo在提供的主機名上失敗"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"失敗的getaddrinfo調用的返回代碼"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName失敗"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname失敗"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"失敗調用後GetLastError的結果"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW失敗"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW失敗"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"無效索引，無法表示為int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"無效設備"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"設施代碼必須根據RFC 5424定義，在乘以8之後"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"目標id無效"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"無效 " INDEXED_THING " 索引"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ註冊表值既不為空，也不以兩個NULL字符結束"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"字串不是 name=\"value\" 格式"

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"無效的prival"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"私有代碼必須根據 RFC 5424 定義：值介於 0 到 255（含）之間"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"severity無效"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"severity代碼必須根據RFC 5424定義：值在0~7之間"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"UTF-8 字串解析過程中到達無效狀態"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"目標類型與此操作不相容"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sdjournal_sendv的返回代碼"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv失敗"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"無法使用mkstemp建立具有所選本地socket名稱的檔案"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"最大訊息大小僅對UDP網路目標有效"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"GetLastError的結果調用失敗"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"無法將提供的多位元組字串轉換為寬字元字串"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"記憶體分配調用失敗"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"嘗試發送的郵件大小"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"訊息太大，無法在單個資料報中發送"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] 和 inet_pton 無法解析該名稱"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"網路連線已關閉"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所選網路協議不支援"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"此生成不支援網路目標"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME "是空的"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"試圖打開不支援的目標類型"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"找不到具有指定特徵的參數"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"無法建立註冊表子項"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"無法刪除註冊表子項"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"無法打開註冊表子項"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"無法讀取註冊表值"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"無法設置註冊表值"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendtofailed使用unix socket"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"試圖將條目發送到不支援的目標類型"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"試圖向不支援的目標類型發送訊息"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sendfailed使用sys/socket.h socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"sendfailed帶有winsock2 socket"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"嚴重性顏色僅支援流目標"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"無法打開套接字"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Windows事件日誌源的無障礙註冊"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"無法將 " PARAM " 綁定到語句"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"資料庫忙碌，無法完成事務"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"無法關閉 sqlite3 資料庫"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"預處理語句的自訂回調失敗"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"無法打開 sqlite3 資料庫"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 失敗"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"失敗的 sqlite3 調用的返回代碼"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"操作重試的次數"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step 失敗"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"此版本不支援 sqlite3 目標"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"無法寫入流"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"違規字串的長度"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"字串長度超出最大限制"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"此目標類型始終處於打開狀態"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"傳輸端口僅對網路目標有效"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所選傳輸協議不支援"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"無法使用socket函數打開unix socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"檢查是否打開了不支援的目標類型"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"無法關閉Windows事件日誌"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"無法打開Windows事件日誌"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"無法將提供的寬字元字串轉換為多位元組字串"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"失敗調用返回的Windows錯誤代碼"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows socket錯誤代碼"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"失敗調用後GetLastError的結果"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"無法打開winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"失敗調用後WSAGetLastError的結果"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_HANT_H */
