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
 * Vietnam Vietnamese localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_VI_VN_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_VI_VN_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"Không thể liên kết với socket Unix cục bộ"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"Bộ đệm dùng để lưu trữ thông điệp"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"Bộ đệm quá nhỏ cho thông điệp đã cho"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"Các mục tiêu dạng chuỗi không được hỗ trợ trong bản dựng này"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Đã cố đóng một loại mục tiêu không được hỗ trợ"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction thất bại"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"Kết nối thất bại với socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"Kết nối thất bại với socket winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction thất bại"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"Đích chỉ hợp lệ cho các mục tiêu mạng"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"Một phần tử với tên đã cung cấp đã tồn tại trong mục nhập này"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"Không tìm thấy phần tử với các đặc tính đã chỉ định"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno sau lời gọi thất bại"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"Không thể mở tệp đã chỉ định"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"Không thể ghi vào tệp"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"Định dạng " ARG " không hợp lệ"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"Mã trả về của hàm xử lý nhật ký"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"Hàm xử lý nhật ký cho mục tiêu hàm đã thất bại"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo thất bại trên tên máy chủ đã cung cấp"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"Mã trả về của lời gọi getaddrinfo thất bại"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName thất bại"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname thất bại"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"Kết quả của GetLastError sau lời gọi thất bại"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW thất bại"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW thất bại"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"Chỉ mục không hợp lệ, hoặc -1 nếu nó quá lớn để biểu diễn dưới dạng int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"Tiện ích không hợp lệ"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"Mã tiện ích phải được định nghĩa theo RFC 5424, sau khi nhân với 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"ID mục tiêu không hợp lệ"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"Chỉ mục " INDEXED_THING " không hợp lệ"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"Giá trị registry MULTI_SZ không rỗng và không kết thúc bằng hai ký tự NULL"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"Chuỗi không có định dạng name=\"value\""

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"Prival không hợp lệ"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"Mã prival phải được định nghĩa theo RFC 5424: giá trị từ 0 đến 255"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"Mức độ nghiêm trọng không hợp lệ"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"Mã mức độ nghiêm trọng phải theo RFC 5424: giá trị từ 0 đến 7"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"Đã đạt trạng thái không hợp lệ khi phân tích chuỗi UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"Loại mục tiêu không tương thích với thao tác này"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"Mã trả về của sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv thất bại"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"Không thể tạo tệp với tên socket cục bộ đã chọn bằng mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"Kích thước thông điệp tối đa chỉ hợp lệ cho mục tiêu mạng UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"Kết quả của GetLastError sau lời gọi thất bại"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"Không thể chuyển đổi chuỗi đa byte đã cung cấp thành chuỗi ký tự rộng"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"Lời gọi cấp phát bộ nhớ thất bại"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"Kích thước thông điệp đã cố gửi"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"Thông điệp quá lớn để gửi trong một datagram"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] và inet_pton không thể phân giải tên"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"Kết nối mạng đã đóng"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"Giao thức mạng đã chọn không được hỗ trợ"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"Các mục tiêu mạng không được hỗ trợ trong bản dựng này"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
"ARG_NAME là NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Đã cố mở một loại mục tiêu không được hỗ trợ"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"Không tìm thấy tham số với các đặc tính đã chỉ định"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"Không thể tạo subkey registry"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"Không thể xóa subkey registry"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"Không thể mở subkey registry"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"Không thể đọc giá trị registry"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"Không thể đặt giá trị registry"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto thất bại với socket Unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Đã cố gửi một mục nhập đến loại mục tiêu không được hỗ trợ"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Đã cố gửi thông điệp đến loại mục tiêu không được hỗ trợ"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"send thất bại với socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"send thất bại với socket winsock2"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"Màu mức độ nghiêm trọng chỉ được hỗ trợ cho các mục tiêu luồng"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"Không thể mở socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Đăng ký nguồn Nhật ký Sự kiện Windows của Stumpless"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"Không thể liên kết " PARAM " với câu lệnh"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"Cơ sở dữ liệu đang bận và không thể hoàn tất giao dịch"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"Không thể đóng cơ sở dữ liệu sqlite3"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"Callback tùy chỉnh cho câu lệnh đã chuẩn bị thất bại"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"Không thể mở cơ sở dữ liệu sqlite3"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 thất bại"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"Mã trả về của lời gọi sqlite3 thất bại"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"Số lần thao tác được thử lại"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step thất bại"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"Các mục tiêu sqlite3 không được hỗ trợ trong bản dựng này"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"Không thể ghi vào luồng"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"Độ dài chuỗi vi phạm"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"Độ dài chuỗi vượt quá giới hạn tối đa"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"Loại mục tiêu này luôn mở"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"Cổng vận chuyển chỉ hợp lệ cho các mục tiêu mạng"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"Giao thức vận chuyển đã chọn không được hỗ trợ"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"Không thể mở socket Unix với hàm socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"Đã kiểm tra xem loại mục tiêu không được hỗ trợ có mở hay không"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"Không thể đóng Nhật ký Sự kiện Windows"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Không thể mở Nhật ký Sự kiện Windows"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"Không thể chuyển đổi chuỗi ký tự rộng đã cung cấp thành chuỗi đa byte"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"Mã lỗi Windows được trả về bởi lời gọi thất bại"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Mã lỗi Socket Windows"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"Kết quả của GetLastError sau lời gọi thất bại"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"Không thể mở socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"Kết quả của WSAGetLastError sau lời gọi thất bại"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_VI_VN_H */
