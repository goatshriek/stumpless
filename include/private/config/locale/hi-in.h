/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_HI_IN_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_HI_IN_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"स्थानीय यूनिक्स सॉकेट से नहीं जुड़ सका"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"दिए गए संदेश के लिए बफ़र बहुत छोटा है"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"एक असमर्थित लक्ष्य प्रकार को बंद करने का प्रयास किया गया"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction असफल"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"कनेक्ट एक sys/socket.h सॉकेट के साथ विफल रहा"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 सॉकेट के साथ कनेक्ट विफल रहा"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction असफल"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"गंतव्य केवल नेटवर्क लक्ष्यों के लिए मान्य है"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"इस प्रविष्टि में दिए गए नाम वाला एक तत्व पहले से मौजूद है"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"निर्दिष्ट विशेषताओं वाला एक तत्व नहीं मिला"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno विफल कॉल के बाद"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"निर्दिष्ट फ़ाइल नहीं खोल सका"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"फ़ाइल में नहीं लिख सका"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"अमान्य " ARG " प्रारूप"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"लॉग हैंडलर फ़ंक्शन का रिटर्न कोड"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"फ़ंक्शन लक्ष्य के लिए लॉग हैंडलर विफल रहा"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo प्रदान किए गए होस्टनाम पर विफल"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"असफल getaddrinfo कॉल का रिटर्न कोड"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName विफल"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname विफल"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"असफल कॉल के बाद GetLastError का परिणाम"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW विफल"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW विफल"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"अमान्य अनुक्रमणिका, या इसका -1 एक int . के रूप में प्रतिनिधित्व" \
" करने के लिए बहुत बड़ा है"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"अमान्य सुविधा"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"सुविधा कोड को RFC 5424 के अनुसार परिभाषित किया जाना चाहिए, इसके बाद" \
" 8 . से गुणा"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"अमान्य target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"अमान्य " INDEXED_THING " अनुक्रमणिका"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"एक MULTI_SZ रजिस्ट्री मान न तो खाली था और न ही दो NULL" \
" अक्षर "

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"अमान्य गंभीरता"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"गंभीरता कोड को RFC 5424 के अनुसार परिभाषित किया जाना चाहिए: 0 . " \
"के बीच के मान और 7 समावेशी"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"लक्ष्य प्रकार इस ऑपरेशन के साथ असंगत है"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"sd_journal_send का रिटर्न कोड"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv विफल"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"mkstemp का उपयोग करके चुने गए स्थानीय सॉकेट नाम के साथ फ़ाइल नहीं बना सका"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"अधिकतम संदेश आकार केवल UDP नेटवर्क लक्ष्यों के लिए मान्य है"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"असफल कॉल के बाद GetLastError का परिणाम"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"प्रदान की गई मल्टीबाइट स्ट्रिंग को एक विस्तृत चार स्ट्रिंग में" \
" परिवर्तित नहीं कर सका"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"एक स्मृति आवंटन कॉल विफल"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"संदेश का आकार जिसे भेजने का प्रयास किया गया थाt"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"संदेश एक डेटाग्राम में भेजने के लिए बहुत बड़ा है"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"चुना गया नेटवर्क प्रोटोकॉल असमर्थित है"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"नेटवर्क लक्ष्य इस बिल्ड द्वारा समर्थित नहीं हैं"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " NULL था"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"एक असमर्थित लक्ष्य प्रकार खोलने का प्रयास किया"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"निर्दिष्ट विशेषताओं वाला एक परम नहीं पाया जा सका"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"रजिस्ट्री उपकुंजी नहीं बनाई जा सकी"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"रजिस्ट्री उपकुंजी को हटाया नहीं जा सका"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"रजिस्ट्री उपकुंजी नहीं खोली जा सकी"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"एक रजिस्ट्री मान पढ़ा नहीं जा सका"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"रजिस्ट्री मान सेट नहीं किया जा सका"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto क यूनिक्स सॉकेट के साथ विफल रहा"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"एक असमर्थित लक्ष्य प्रकार में प्रविष्टि भेजने का प्रयास किया गया"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"एक असमर्थित लक्ष्य प्रकार को संदेश भेजने का प्रयास किया गया"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"एक sys/socket.h सॉकेट के साथ भेजना विफल रहा"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"winsock2 सॉकेट के साथ भेजना विफल रहा"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"सॉकेट खोलने में विफल"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"विंडोज इवेंट लॉग सोर्स का स्टंपलेस पंजीकरण"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"धारा को नहीं लिख सका"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"आपत्तिजनक स्ट्रिंग की लंबाई"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"स्ट्रिंग की लंबाई अधिकतम सीमा से अधिक है"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"यह लक्ष्य प्रकार हमेशा खुला रहता है"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"ट्रांसपोर्ट पोर्ट केवल नेटवर्क लक्ष्य के लिए मान्य हैं"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"चुना गया परिवहन प्रोटोकॉल असमर्थित है"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"सॉकेट फ़ंक्शन के साथ एक यूनिक्स सॉकेट खोलने में विफल रहा"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"यह देखने के लिए जाँच की गई कि क्या कोई असमर्थित लक्ष्य प्रकार खुला है"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"विंडोज इवेंट लॉग बंद नहीं कर सका"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"विंडोज इवेंट लॉग नहीं खोल सका"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"प्रदान की गई विस्तृत चार स्ट्रिंग को एक मल्टीबाइट स्ट्रिंग में परिवर्तित " \
"नहीं कर सका"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"विफल कॉल द्वारा लौटाया गया Windows त्रुटि कोड"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"विंडोज सॉकेट त्रुटि कोड"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"असफल कॉल के बाद GetLastError का परिणाम"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"एक winsock2 सॉकेट खोलने में विफल"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"विफल कॉल के बाद WSAGetLastError का परिणाम"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_HI_IN_H */
