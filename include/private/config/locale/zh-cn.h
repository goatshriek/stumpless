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

/* Warning: This Language Docmention use translate with robot. Please
* help us to keep them can read.
* For Chinese Users(对中文用户):
* 警告：这个语言文档是机翻的。请帮助我们保持他们可读。
*/

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"无法绑定到本地unix socket"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"缓冲区对于给定消息太小"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图关闭不受支持的目标类型"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction失败"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"使用sys/socket.h时socket连接失败"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"使用winsock2时socket连接失败"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction失败"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"目标仅对网络目标有效"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"此条目中已存在具有提供名称的element"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"找不到具有指定特征的element"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"失败的调用errno"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"无法打开指定的文件"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"无法写入文件"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"无效 " ARG " 格式"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"日志处理程序函数的返回代码"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"函数目标的日志处理程序失败"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo在提供的主机名上失败"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"失败的getaddrinfo调用的返回代码"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName失败"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname失败"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"失败调用后GetLastError的结果"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW失败"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW失败"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"无效索引，无法表示为int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"无效设备"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"设施代码必须根据RFC 5424定义，在乘以8之后"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"目标id无效"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"无效 " INDEXED_THING " 索引"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ注册表值既不为空，也不以两个NULL字符结束"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"severity无效"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"severity代码必须根据RFC 5424定义：值在0~7之间"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"目标类型与此操作不兼容"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sdjournal_sendv的返回代码"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv失败"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"无法使用mkstemp创建具有所选本地socket名称的文件"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"最大消息大小仅对UDP网络目标有效"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"GetLastError的结果调用失败"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"无法将提供的多字节字符串转换为宽字符字符串"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"内存分配调用失败"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"尝试发送的邮件大小"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"消息太大，无法在单个数据报中发送"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所选网络协议不受支持"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"此生成不支持网络目标"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME "是空的"

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
"sendtofailed使用unix socket"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图将条目发送到不受支持的目标类型"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"试图向不支持的目标类型发送消息"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sendfailed使用sys/socket.h socket"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"sendfailed带有winsock2 socket"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"无法打开套接字"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Windows事件日志源的无障碍注册"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"无法写入流"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"违规字符串的长度"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"字符串长度超出最大限制"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"此目标类型始终处于打开状态"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"传输端口仅对网络目标有效"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"所选传输协议不受支持"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"无法使用socket函数打开unix socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"检查是否打开了不受支持的目标类型"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"无法关闭Windows事件日志"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"无法打开Windows事件日志"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"无法将提供的宽字符字符串转换为多字节字符串"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"失败调用返回的Windows错误代码"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows socket错误代码"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"失败调用后GetLastError的结果"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"无法打开winsock2 socket"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"失败调用后WSAGetLastError的结果"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_ZH_CN_H */
