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
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Hint: This document has been manually proofread and improved.
 * For Chinese Users(对中文用户):
 * 提示：此文档已由人工校对和完善。
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"无法绑定到本地 Unix 套接字"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"用于存储消息的缓冲区大小"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"缓冲区对于给定消息太小"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"此构建版本不支持链式目标"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图关闭不受支持的目标类型"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"提交事务 (CommitTransaction) 失败"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"使用 sys/socket.h 时套接字连接失败"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"使用 winsock2 时套接字连接失败"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"创建事务 (CreateTransaction) 失败"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"该目的地属性仅对网络目标有效"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"此条目中已存在具有该名称的元素"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"找不到具有指定特征的元素"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"系统调用的错误号"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"无法打开指定的文件"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"无法写入文件"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"无效 " ARG " 格式"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"日志处理函数 (Handler Function) 的返回代码"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"函数目标 (Function Target) 的日志处理程序执行失败"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo 无法解析提供的主机名"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"失败的getaddrinfo调用的返回代码"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"获取计算机名称 (GetComputerName) 失败"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"获取主机名 (gethostname) 失败"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"失败调用后GetLastError的结果"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"获取模块文件名 (GetModuleFileNameW) 失败"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"获取模块句柄 (GetModuleHandleExW) 失败"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"索引越界：无效索引无法表示为 int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"无效的设施 (Facility) 代码"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"设施代码必须符合 RFC 5424 标准（乘以 8 后的值）"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"目标 ID 无效"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"无效 " INDEXED_THING " 索引"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ 注册表值既不为空，也不以两个 NULL 字符结束"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"字符串格式不符合 name=\"value\" 规范"

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"无效的优先级值 (Prival)"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"优先级代码必须根据 RFC 5424 定义：值介于 0 到 255（含）之间"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"无效的严重程度 (Severity) 等级"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"严重程度代码必须根据 RFC 5424 定义：值介于 0 到 7（含）之间"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"在 UTF-8 字符串解析过程中达到无效状态"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"目标类型与此操作不兼容"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendv 的返回代码"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv 失败"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"无法使用 mkstemp 创建具有所选名称的本地套接字文件"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"最大消息大小限制仅对 UDP 网络目标有效"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"多字节字符串转宽字符字符串失败时的 GetLastError 结果"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"无法将提供的多字节字符串转换为宽字符字符串"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"内存分配调用失败"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"尝试发送的邮件大小"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"消息太大，无法在单个数据报中发送"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] 或 inet_pton 无法解析该名称"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"网络连接已关闭"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所选网络协议不受支持"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"此构建版本不支持网络目标 (Network Targets)"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " 参数不能为空"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图打开不受支持的目标类型"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"找不到具有指定特征的参数"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"无法创建注册表子项"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"无法删除注册表子项"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"无法打开注册表子项"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"无法读取注册表值"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"无法设置注册表值"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"使用 Unix 套接字时 sendto 调用失败"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图将条目发送到不受支持的目标类型"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图向不支持的目标类型发送消息"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"使用 sys/socket.h 套接字发送失败"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"使用 winsock2 套接字发送失败"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"严重程度着色功能 仅支持流目标"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"无法打开套接字"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Windows 事件日志源的无障碍注册"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"无法将 " PARAM " 绑定到 SQLite3 语句"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"数据库忙，无法完成事务"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"无法关闭 SQLite3 数据库"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"预处理语句 (Prepared Statement) 的自定义回调失败"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"无法打开 SQLite3 数据库"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 调用失败"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"失败的 SQLite3 调用的返回代码"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"操作重试次数"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step 调用失败"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"此构建版本不支持 SQLite3 目标"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"无法写入流"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"违规字符串的长度"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"字符串长度超出最大限制"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"该目标类型始终处于打开状态"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"传输端口仅对网络目标有效"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所选传输协议不受支持"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"无法使用 socket 函数打开 Unix 套接字"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"无法检查不受支持的目标类型是否处于打开状态"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"无法关闭 Windows 事件日志 (WEL)"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"无法打开 Windows 事件日志 (WEL)"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"无法将提供的宽字符字符串转换为多字节字符串"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"Windows 系统调用的错误返回代码"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows socket 错误代码"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"转换失败后的 GetLastError 结果代码"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"无法打开 winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"失败调用后 WSAGetLastError 的结果"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H */
