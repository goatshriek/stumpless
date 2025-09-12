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
 * Egypt Arabic localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_AR_EG_H
#define __STUMPLESS_PRIVATE_CONFIG_LOCALE_AR_EG_H

#define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
    "تعذر الدمج مع"                                \
    "unix socket"

#define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
    "المخزن المستخدم لتخزين الرسائل"

#define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
    "المخزن صغير جدا لتخزين هذه الرسالة"

#define L10N_CHAIN_TARGETS_UNSUPPORTED \
    "الهدف غير مدعوم لهذه النسخة"

#define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
    "محاولة إغلاق هدف غير مدعوم"

#define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
    "فشلت العملية "                                  \
    "CommitTransaction"

#define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل التوصيل مع "                                \
    "sys/socket.h socket"

#define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل التوصيل مع "                                \
    "winsock2 socket"

#define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
    "فشلت العملية "                                  \
    "CreateTransaction"

#define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
    "الوجهة صالحة فقط لأهداف الشبكة"

#define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
    "يوجد عنصر مستخدم بهذا الاسم من قبل"

#define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
    "لم يتم العثور على عنصر بالمواصفات المحددة"

#define L10N_ERRNO_ERROR_CODE_TYPE \
    "errno "                       \
    " بعد النداء الفاشل"

#define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
    "تعذر فتح الملف المحدد"

#define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
    "تعذر الكتابة إلى الملف"

#define L10N_FORMAT_ERROR_MESSAGE(ARG) \
    "الصيغة " ARG                      \
    " غير صحيحة"

#define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
    "return code of the log handler function"

#define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
    "فشل معالجة السجل لدالة الهدف"

#define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
    "getaddrinfo "                             \
    "فشل للـ hostname "                        \
    "المطلوب"

#define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
    " قيمة الإرجاع بعد فشل نداء"                \
    "getaddrinfo"

#define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
    "فشلت "                                       \
    "GetComputerName"

#define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
    "فشلت "                                   \
    "gethostname"

#define L10N_GETLASTERROR_ERROR_CODE_TYPE \
    "نتيجة "                              \
    "GetLastError "                       \
    "بعد النداء الفاشل"

#define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
    "فشلت "                                          \
    "GetModuleFileNameW"

#define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
    "فشلت "                                         \
    "GetModuleHandleExW"

#define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
    "قيمة المؤشر غير صحيحة أو 1- "               \
    "أو القيمة كبيرة جدا لوضعها في "             \
    "int"

#define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
    "المنشأة غير صحيحة"

#define L10N_INVALID_FACILITY_ERROR_MESSAGE \
    "يجب تعريف رموز المنشاة وفقا لـ "       \
    "RFC 5424، بعد الضرب في 8"

#define L10N_INVALID_ID_ERROR_MESSAGE \
    "معرف الهدف غير صالح"

#define L10N_INVALID_INDEX_ERROR_MESSAGE(INDEXED_THING) \
    "المؤشر " INDEXED_THING                             \
    " غير صالح"

#define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
    "قيمة "                                 \
    "MULTI_SZ"                              \
    "في السجل فارغة او انتهت بـ اثنتين NULL"

#define L10N_INVALID_PARAM_ERROR_MESSAGE \
    "النص ليس بصيغة "                    \
    "name=\"value\""

#define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"قيمة الخطورة والمنشأة غير صالحة"

#define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"قيمة الخطورة والمنشأة يجب ان تكون بصيغة RFC 5424: القيم بين 0 و 255 شاملة"

#define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
    "مستوي الشدة غير معلوم "

#define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
    "قيمة الشدة يجب ان تكون بصيغة"          \
    "RFC 5424: القيم بين 0 و 7 شاملة"

#define L10N_INVALID_STATE_DURING_UTF8_PARSING   \
    "الوصول الي حالة غير صالحة اثناء تحليل النص" \
    "UTF-8"
#define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
    "نوع الهدف غير متوافق مع هذه العملية"

#define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
    "قيمة الارجاع لـ"                         \
    "sd_journal_sendv"

#define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
    "فشلت "                                 \
    "sd_journal_sendv"

#define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
    "لا يمكن إنشاء ملف باستخدام هذا الـ"               \
    "socket "                                          \
    " باستخدام mkstemp"

#define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
    "الحد الاقصى للرساله متاح فقط "                  \
    "لأهداف شبكة UDP"

#define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
    "نتيجة "                                       \
    "GetLastError "                                \
    "بعد فشل النداء"

#define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
    "تعذر تحويل النص المطلوب الي سلسلة من الحروف "

#define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
    "تعذر تعين مساحة في الذاكرة"

#define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
    "حجم الرسالة التي تمت محاولة إرسالها"

#define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
    "الرسالة كبيرة جدًا لإرسالها في حزمة بيانات واحدة"

#define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
    "فشل في حل الاسم"                             \
    "gethostbyname[2] و inet_pton"

#define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
    "تم غلق الاتصال بالشبكة"

#define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
    "بروتوكول الشبكة المختار غير مدعوم"

#define L10N_NETWORK_TARGETS_UNSUPPORTED \
    "اهداف الشبكة غير مدعومة لهذه النسخة"

#define L10N_NULL_ARG_ERROR_MESSAGE(ARG_NAME) \
    ARG_NAME                                  \
    " كان NULL"

#define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
    "محاولة فتح هدف غير مدعوم"

#define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
    "تعذر العثور على معامل بالخصائص المحددة"

#define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
    "تعذر انشاء مفتاح فرعي في السجل"

#define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
    "تعذر مسح مفتاح فرعي في السجل"

#define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
    "تعذر فتح مفتاح فرعي في السجل"

#define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
    "تعذر فراءة مفتاح فرعي في السجل"

#define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
    "تعذر وضع مفتاح فرعي في السجل"

#define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل "                                           \
    "sendto "                                        \
    "مع "                                            \
    "unix socket"

#define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
    "ممحاولة الارسال الي هدف غير معلوم "

#define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
    "ممحاولة ارسال رسالة الي هدف غير معلوم "

#define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل الارسال بـ"                              \
    "sys/socket.h socket"

#define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل الارسال مع "                             \
    "winsock2 socket"

#define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
    "أنواع الشدة مدعومة فقط لأهداف التدفق"

#define L10N_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل في فتح Socket"

#define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
    "تسجيل "                                               \
    "Stumpless "                                           \
    "في "                                                  \
    " Windows Event Log Source"

#define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE(PARAM) \
    "لا يمكن ربط" PARAM                               \
    "بالبيان"

#define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
    "قاعدة البيانات مشغولة ولا يمكن اتمام العملية"

#define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
    "لا يمكن غلق قاعدة بيانات "                 \
    "sqlite3"

#define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
    "فشل الاستدعاء المخصص للبيانات المُعدة"

#define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
    "لا يمكن فتح"                              \
    "قاعدة بيانات sqlite3"

#define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
    "فشلت "                                       \
    "sqlite3_prepare_v2"

#define L10N_SQLITE3_RESULT_CODE_TYPE \
    "فشل نداء "                       \
    "sqlite3"                         \
    "وقيمة الارجاع"

#define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
    "عدد المرات التي أعيدت فيها محاولة اتمام العملية"

#define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
    "فشلت "                                    \
    "sqlite3_step"

#define L10N_SQLITE3_TARGETS_UNSUPPORTED \
    "أهداف "                             \
    "sqlite3"                            \
    "غير مدعومة لهذه النسخة"

#define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
    "تعذر الكتابة إلى التدفق"

#define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
    "طول النص المخالف"

#define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
    "طول النص تجاوز الحد المسموح"

#define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
    " هذا الهدف مفتوح دائما"

#define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
    "النقل متاح فقط لأهداف الشبكة"

#define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
    "بروتوكول النقل المختار غير مدعوم"

#define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل في فتح"                              \
    "unix socket"                             \
    "مع دالة socket"

#define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
    "مراجعة ما ان تم فتح هدف غير مدعوم"

#define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
    "لا يمكن غلق "                           \
    "Windows Event Log"

#define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
    "لا يمكن فتح "                          \
    "Windows Event Log"

#define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
    "لا يمكن تحويل سلسلة الحروف الي نص "

#define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
    "رمز خطا "                              \
    "Windows "                              \
    "الذي أعاده النداء الفاشل"

#define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
    "رمز خطا"                               \
    "Windows Socket"

#define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
    "نتيجة "                                               \
    "GetLastError "                                        \
    "بعد النداء الفاشل"

#define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
    "فشل في فتح "                                 \
    "winsock2 socket"

#define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
    "نتيجة "                                 \
    "WSAGetLastError "                       \
    "بعد النداء الفاشل"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_AR_EG_H */
