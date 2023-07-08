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
 * Hebrew localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_HE_IL_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_HE_IL_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"המקומי Unix-לא ניתן היה להתחבר לשקע ה"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"החוצץ קטן מידי עבור ההודעה הנתונה"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ניסה להיסגר טיפוס יעד שאינו נתמך"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"נכשל CommitTransaction"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"נכשל sys/socket.h חיבור עם שקע"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"נכשל winsock2 חיבור עם שקע"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"נכשל CreateTransaction"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"יעד חוקי מוגדר רק עבור יעדי רשת"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"פריט עם השם שהתקבל כבר קיים ברשומה זו"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"לא נמצא פריט עם המאפיינים שצוינו"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"בעקבות הקריאה שכשלה (errno) מספר שגיאה"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"לא ניתן היה לפתוח את הקובץ שצוין"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"לא ניתן לכתוב לקובץ"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"אינה חוקית " ARG " התבנית"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"קוד חזרה של פונקציית הלוג-הנדלר"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"הלוג-הנדלר נכשל עבור פונקציית יעד"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"עם השם המארח שסופק, נכשל - getaddrinfo"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"שכשלה getaddrinfo-קוד חזרה של הקריאה ל"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"נכשל GetComputerName"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"נכשל gethostname"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"לאחר הקריאה שכשלה GetLastError התוצאה של"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"נכשל GetModuleFileNameW"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"נכשל GetModuleHandleExW"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"int-האינדקס, שאינו חוקי או שערכו 1-, גדול מידי מכדי להיות מיוצג כ"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"המתקן שאינו חוקי"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"לאחר כפל ב-8 ,RFC 5424-יש להגדיר קודי מתקן בהתאם ל"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"מזהה היעד אינו חוקי"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"אינו חוקי " INDEXED_THING " אינדקס"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"NULL לא היה ריק ולא הסתיים עם שני תווי MULTI_SZ ערך רישום של"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"שאינו חוקי Severity-ה"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"ערכים בין 0 ל-7 כולל :RFC 5424-בהתאם ל (Severity) יש להגדיר קודי חומרה"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"UTF-8 מצב לא חוקי התקבל במהלך ניתוח מחרוזת"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"טיפוס היעד אינו תואם עם פעולה זו"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_sendv קוד חזרה של"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"נכשל sd_journal_sendv"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp לא ניתן ליצור קובץ עם שם השקע המקומי שנבחר באמצעות"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"UDP גודל מקסימלי של הודעה הוא חוקי רק עבור יעדי רשת מסוג"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"לאחר הקריאה שכשלה GetLastError התוצאה של"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"wide char שהתקבלה למחרוזת מסוג multibyte לא יכל להמיר את המחרוזת מסוג"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"נכשלה בקשה להקצאת זיכרון"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"גודל ההודעה שניסתה להישלח"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"יחיד datagram-ההודעה גדולה מידי מכדי להישלח ב"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"לא הצליחו לפתור שם זה gethostbyname[2] וגם inet_pton"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"פרוטוקול הרשת שנבחר אינו נתמך"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"זה build יעדי רשת אינם נתמכים עם"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
"NULL היה " ARG_NAME

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ניסה לפתוח טיפוס יעד שאינו נתמך"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"עם המאפיינים שצוינו param לא נמצא"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"registry subkey לא ניתן היה ליצור"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"registry subkey לא ניתן היה למחוק"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"registry subkey לא ניתן היה לפתוח"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"registry value לא ניתן היה לקרא"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"registry value לא ניתן היה להגדיר"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"Unix נכשל עם שקע sendto"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ניסה לשלוח רשומה לטיפוס יעד שאינו נתמך"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ניסה לשלוח הודעה לטיפוס יעד שאינו נתמך"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h נכשל עם השקע send"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 נכשל עם השקע send"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"נכשל בפתיחת שקע"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Windows Event Log Source של Stumpless רישום"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"stream-לא ניתן היה לכתוב ל"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"האורך של המחרוזת הפוגענית"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"אורך של מחרוזת חרג מהמגבלה המקסימלית"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"טיפוס יעד זה פתוח תמיד"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"שליחת פורטים היא חוקית עבור יעדי רשת בלבד"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"פרוטוקול השליחה שנבחר אינו נתמך"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"עם פונקציית שקע unix נכשל בפתיחת שקע"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"בדק האם היה פתוח טיפוס יעד שאינו נתמך"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"Windows Event Log לא יכל לסגור את"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"Windows Event Log לא יכל לפתוח את"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"multibyte שהתקבלה למחרוזת מסוג wide char לא יכל להמיר את המחרוזת מסוג"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"הוחזר על ידי הקריאה שנכשלה Windows קוד השגיאה של"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Windows Socket קוד שגיאה של"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"אחרי הקריאה שנכשלה GetLastError התוצאה של"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 נכשל בניסיון לפתוח שקע"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"אחרי הקריאה שנכשלה WSAGetLastError התוצאה של"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_HE_IL_H */
