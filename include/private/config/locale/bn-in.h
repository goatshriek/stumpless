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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_BN_IN_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_BN_IN_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"স্থানীয় ইউনিক্স সকেটের"\
 "সাথে আবদ্ধ করা যায়নি"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"প্রদত্ত বার্তার জন্য"\
 "বাফারটি খুবই ছোট"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"একটি অসমর্থিত টার্গেট টাইপ"\
 "বন্ধ করার চেষ্টা করা হয়েছে"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction অসফল"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"sys/socket.h সকেটের সাথে সংযোগ ব্যর্থ হয়েছে"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 সকেটের সাথে সংযোগ ব্যর্থ হয়েছে"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction অসফল"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"গন্তব্য শুধুমাত্র নেটওয়ার্ক লক্ষ্যের জন্য বৈধ"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"প্রদত্ত নামের একটি উপাদান ইতিমধ্যে"\
 "এই এন্ট্রিতে উপস্থিত রয়েছে৷"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"নির্দিষ্ট বৈশিষ্ট্য সহ একটি উপাদান খুঁজে পাওয়া যায়নি"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"ব্যর্থ কলের পরে ত্রুটি নম্বর"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"নির্দিষ্ট ফাইল খোলা যায়নি"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"ফাইলে লেখা যায়নি"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"লগ হ্যান্ডলার ফাংশনের রিটার্ন কোড"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"একটি ফাংশন লক্ষ্যের জন্য লগ হ্যান্ডলার ব্যর্থ হয়েছে"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo প্রদত্ত হোস্টনামে ব্যর্থ হয়েছে"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"ব্যর্থ getaddrinfo কলের রিটার্ন কোড"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName অসফল"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname অসফল"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW অসফল"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW অসফল"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"অবৈধ সূচক, বা এর -1টি একটি int হিসাবে"\
 "উপস্থাপন করার জন্য খুব বড়"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"বাতিল প্রণালী"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"সুবিধা কোডগুলি অবশ্যই RFC 5424 অনুসারে"\
 "সংজ্ঞায়িত করতে হবে, এর পরে 8 দ্বারা গুণ"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"অসফল target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"অসফল " INDEXED_THING " index"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"একটি MULTI_SZ রেজিস্ট্রি মান খালি ছিল না" \
"বা দুটি NULL অক্ষর দিয়ে শেষ করা হয়নি"

// todo translate
#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"the string is not of the name=\"value\" format"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"অসফল severity"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"তীব্রতা কোড অবশ্যই RFC 5424 অনুসারে"\
"সংজ্ঞায়িত করা উচিত: 0 এর মধ্যে মান" \
" এবং 7 সহ"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"টার্গেট টাইপ এই অপারেশনের সাথে বেমানান"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_send এর রিটার্ন কোড"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv অসফল"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp ব্যবহার করে নির্বাচিত স্থানীয় সকেট"\
 "নাম দিয়ে একটি ফাইল তৈরি করা যায়নি"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"সর্বাধিক বার্তা আকার শুধুমাত্র UDP নেটওয়ার্ক লক্ষ্যগুলির জন্য বৈধ"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"ব্যর্থ কলের পরে GetLastError এর ফলাফল"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"প্রদত্ত মাল্টিবাইট স্ট্রিংকে একটি প্রশস্ত চর স্ট্রিং-এ রূপান্তর করতে পারেনি"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"একটি মেমরি বরাদ্দ কল অসফল"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"বার্তার আকার যা পাঠানোর চেষ্টা করা হয়েছিল"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"একটি একক ডেটাগ্রামে পাঠানোর জন্য বার্তাটি খুব বড়"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"নির্বাচিত নেটওয়ার্ক প্রোটোকল অসমর্থিত"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"নেটওয়ার্ক লক্ষ্যগুলি এই বিল্ড দ্বারা সমর্থিত নয়"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " NULL ছিল"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"একটি অসমর্থিত লক্ষ্য টাইপ খোলার চেষ্টা"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"নির্দিষ্ট বৈশিষ্ট্য সহ একটি প্যারাম পাওয়া যায়নি"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"একটি রেজিস্ট্রি সাবকি তৈরি করা যায়নি"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"একটি রেজিস্ট্রি সাবকি মোছা যাবে না"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"একটি রেজিস্ট্রি সাবকি খোলা যাবে না"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"একটি রেজিস্ট্রি মান পড়া যাবে না"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"একটি রেজিস্ট্রি মান সেট করা যায়নি"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"একটি ইউনিক্স সকেট দিয়ে ব্যর্থ হয়েছে"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"একটি অসমর্থিত লক্ষ্য টাইপ একটি এন্ট্রি পাঠানোর চেষ্টা"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"একটি অসমর্থিত লক্ষ্য ধরনের একটি বার্তা পাঠানোর চেষ্টা করা হয়েছে"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"একটি sys/socket.h সকেট দিয়ে পাঠাতে ব্যর্থ হয়েছে"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"একটি winsock2 সকেট দিয়ে পাঠাতে ব্যর্থ হয়েছে"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"একটি সকেট খুলতে ব্যর্থ"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"উইন্ডোজ ইভেন্ট লগ সোর্সের স্টাম্পলেস রেজিস্ট্রেশন"

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
"স্রোতে লিখতে পারিনি"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"আপত্তিকর স্ট্রিং এর দৈর্ঘ্য"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"স্ট্রিংয়ের দৈর্ঘ্য সর্বাধিক সীমা অতিক্রম করেছে৷"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"এই লক্ষ্য টাইপ সবসময় খোলা"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"পরিবহন পোর্ট শুধুমাত্র নেটওয়ার্ক টার্গেটের জন্য বৈধ"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"নির্বাচিত পরিবহন প্রোটোকল অসমর্থিত"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"সকেট ফাংশন সহ একটি ইউনিক্স সকেট খুলতে ব্যর্থ হয়েছে"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"একটি অসমর্থিত টার্গেট টাইপ খোলা ছিল কিনা তা দেখতে পরীক্ষা করা হয়েছে"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"উইন্ডোজ ইভেন্ট লগ বন্ধ করতে পারেনি"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"উইন্ডোজ ইভেন্ট লগ খুলতে পারেনি"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"প্রদত্ত প্রশস্ত অক্ষর স্ট্রিংটিকে মাল্টিবাইট স্ট্রিং-এ রূপান্তর করতে পারেনি"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"ব্যর্থ কল দ্বারা ফিরে উইন্ডোজ ত্রুটি কোড"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"উইন্ডোজ সকেট ত্রুটি কোড"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"ব্যর্থ কলের পরে GetLastError এর ফলাফল"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"একটি winsock2 সকেট খুলতে ব্যর্থ হয়েছে"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"ব্যর্থ কলের পরে WSAGEtLastError এর ফলাফল"

#endif  /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_BN_IN_H */
