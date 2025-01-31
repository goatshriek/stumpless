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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_KO_KR_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_KO_KR_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"로컬 UNIX 소켓에 바인딩할 수 없습니다"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"주어진 메시지에 대한 버퍼가 너무 작습니다"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"이 빌드에서는 체인 타겟을 지원하지 않습니다"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"지원되지 않는 타겟 타입을 닫으려고 시도했습니다"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"트랜잭션 커밋에 실패"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h 소켓으로 연결 실패"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 소켓으로 연결 실패"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"트랜잭션 생성에 실패"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"목적지는 네트워크 타겟에만 유효합니다"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"제공된 이름의 요소가 이미 이 항목에 존재합니다"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"지정된 특성을 가진 요소를 찾을 수 없습니다"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"실패한 호출 이후의 errno"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"지정된 파일을 열 수 없습니다"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"파일에 쓸 수 없습니다"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"잘못된 " ARG " 형식"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"로그 핸들러 함수의 반환 코드"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"함수 타겟의 로그 핸들러가 실패"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"제공된 호스트 이름에서 getaddrinfo 실패"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"실패한 getaddrinfo 호출의 반환 코드"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName 호출에 실패"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname 호출에 실패"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"실패한 호출 이후의 GetLastError 결과"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW 호출에 실패"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW 호출에 실패"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"잘못된 인덱스 또는 이를 int로 표현할 수 있는 범위를 벗어난 -1"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"잘못된 시설"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"시설 코드는 RFC 5424에 따라 정의되어야 하며, 8을 곱한 후 정의해야 합니다."

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"잘못된 타겟 ID"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"잘못된 " INDEXED_THING " 인덱스"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"MULTI_SZ 레지스트리 값이 비어 있거나 두 개의 NULL 문자로 끝나지 않았습니다"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"문자열이 이름=\"값\" 형식이 아닙니다"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"잘못된 심각도"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"심각도 코드는 RFC 5424에 따라 정의되어야 합니다. 값은 0부터 7까지입니다."

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"UTF-8 문자열 구문 분석 중 잘못된 상태에 도달했습니다"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"타겟 유형이 이 작업과 호환되지 않습니다"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendv의 반환 코드"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv 호출에 실패"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp를 사용하여 선택한 로컬 소켓 이름의 파일을 만들 수 없습니다"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"최대 메시지 크기는 UDP 네트워크 타겟에만 유효합니다"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"실패한 호출 이후의 GetLastError 결과"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"제공된 다중 바이트 문자열을 와이드 문자열로 변환할 수 없습니다"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"메모리 할당 호출에 실패"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"전송을 시도한 메시지의 크기"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"메시지가 단일 데이터그램으로 전송하기에 너무 큽니다"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] 및 inet_pton이 이름을 해결하지 못했습니다"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"네트워크 연결이 닫혔습니다"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"선택한 네트워크 프로토콜이 지원되지 않습니다"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"이 빌드에서는 네트워크 타겟을 지원하지 않습니다"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME "이 NULL입니다"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"지원되지 않는 타겟 타입을 열려고 시도했습니다"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"지정된 특성을 가진 매개변수를 찾을 수 없습니다"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"레지스트리 하위 키를 만들 수 없습니다"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"레지스트리 하위 키를 삭제할 수 없습니다"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"레지스트리 하위 키를 열 수 없습니다"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"레지스트리 값 읽기를 실패했습니다"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"레지스트리 값 설정을 실패했습니다"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"UNIX 소켓으로 sendto 호출에 실패했습니다"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"지원되지 않는 타겟 타입에 항목을 전송하려고 시도했습니다"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"지원되지 않는 타겟 타입에 메시지를 전송하려고 시도했습니다"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h 소켓으로 send 호출에 실패"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 소켓으로 send 호출에 실패"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"소켓 열기에 실패했습니다"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
"Windows 이벤트 로그 소스의 Stumpless 등록"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"문장에 " PARAM "을(를) 바인딩할 수 없습니다"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"데이터베이스가 사용 중이어서  트랜잭션을 완료할 수 없습니다"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"sqlite3 데이터베이스를 닫을 수 없습니다"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"준비된 문을 위한 사용자 정의 콜백이 실패"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"sqlite3 데이터베이스를 열 수 없습니다"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 호출에 실패"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"실패한 sqlite3 호출의 반환 코드"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"작업을 재시도한 횟수"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step 호출에 실패"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"이 빌드에서는 sqlite3 타겟을 지원하지 않습니다"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"스트림에 쓸 수 없습니다"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"문제가 되는 문자열의 길이"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"문자열의 길이가 최대 제한을 초과했습니다"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"이 타겟 유형은 항상 열려 있습니다"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"전송 포트는 네트워크 타겟에만 유효합니다"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"선택한 전송 프로토콜이 지원되지 않습니다"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"socket 함수로 UNIX 소켓을 열지 못했습니다"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"지원되지 않는 타겟 유형이 열려 있는지 확인했습니다"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"Windows 이벤트 로그를 닫을 수 없습니다"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Windows 이벤트 로그를 열 수 없습니다"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"제공된 와이드 문자열을 다중 바이트 문자열로 변환할 수 없습니다"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"실패한 호출 이후의 Windows 오류 코드"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows 소켓 오류 코드"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"실패한 호출 이후의 GetLastError 결과"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 소켓을 열지 못했습니다"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"실패한 호출 이후의 WSAGetLastError 결과"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_KO_KR_H */