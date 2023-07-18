/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2020-2021 Muhammed Abiola
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
 * Swahili (Kenyan) localization strings.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_SW_KE_H
#define __STUMPLESS_PRIVATE_CONFIG_LOCALE_SW_KE_H

#define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"haikuweza kushikamana na soketi ya unix ya ndani" 

#define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"buffer ni ndogo sana kwa ujumbe uliotolewa"

#define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"kujaribu kufunga aina isiyoungwa mkono ya lengo"

#define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"muunganisho umeshindwa na soketi ya sys/socket.h"

#define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"muunganisho umeshindwa na soketi ya winsock2"

#define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"marudio ni sahihi tu kwa malengo ya mtandao"

#define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"kuna kipengele na jina lililotolewa tayari limo katika kuingia hii"

#define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"kipengele na sifa zilizotajwa hazikuweza kupatikana"

#define L10N_ERRNO_ERROR_CODE_TYPE \
"errno baada ya wito ulioshindwa"

#define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"haikuweza kufungua faili iliyotajwa"

#define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"haikuweza kuandika kwenye faili"

#define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"kodi ya kurudi ya kazi ya kushughulikia logi"

#define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"mshughulikiaji logi kwa lengo la kazi umeshindwa"

#define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"haikuweza kuunda faili yenye jina la soketi ya ndani iliyochaguliwa kwa kutumia mkstemp"

#define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"getaddrinfo imeshindwa kwenye jina la mwenyeji lililotolewa"

#define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"kodi ya kurudi ya getaddrinfo iliyoshindwa"

#define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName imefeli"

#define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname imefeli"

#define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"matokeo ya GetLastError baada ya wito ulioshindwa"

#define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"nafasi batili, au -1 ikiwa ni kubwa sana kuwakilishwa kama int"

#define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"kituo batili"

#define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"nambari za vituo lazima zitajwe kulingana na RFC 5424, baada ya kuzidishwa na 8"

#define L10N_INVALID_ID_ERROR_MESSAGE \
"kitambulisho batili cha lengo"

#define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"nafasi batili ya " INDEXED_THING

#define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"ukali batili"

#define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"nambari za ukali lazima zitajwe kulingana na RFC 5424: thamani kati ya 0 na 7 kwa pamoja"

#define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"kodi ya kurudi ya sd_journal_sendv"

#define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv imeshindwa"

#define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"ukubwa wa ujumbe ni sahihi tu kwa malengo ya mtandao ya UDP"

#define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"wito wa kutengeneza kumbukumbu umeshindwa"

#define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"ujumbe ni mkubwa sana kupelekwa kwa datagram moja"

#define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"ukubwa wa ujumbe uliojaribu kutumwa"

#define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"itifaki ya mtandao iliyochaguliwa haikungwi mkono"

#define L10N_NETWORK_TARGETS_UNSUPPORTED \
"malengo ya mtandao hayangwi mkono na ujenzi huu"

#define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " ilikuwa NULL"

#define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"kujaribu kufungua aina isiyoungwa mkono ya lengo"

#define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"paramu na sifa zilizotajwa hazikuweza kupatikana"

#define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"kujaribu kutuma kuingia kwenye aina isiyoungwa mkono ya lengo"

#define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"kujaribu kutuma ujumbe kwenye aina isiyoungwa mkono ya lengo"

#define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"tuma umeshindwa na soketi ya sys/socket.h"

#define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"tuma kwa soketi ya unix imefeli"

#define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"tuma umeshindwa na soketi ya winsock2"

#define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"kushindwa kufungua soketi"

#define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"haikuweza kuandika kwenye mtiririko"

#define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"aina hii ya lengo daima imefunguliwa"

#define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"bandari za usafirishaji ni sahihi tu kwa malengo ya mtandao"

#define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"itifaki ya usafirishaji iliyochaguliwa haikungwi mkono"

#define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"kushindwa kufungua soketi ya unix kwa kutumia kazi ya soketi"

#define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"imechunguza kuona ikiwa aina isiyoungwa mkono ya lengo imefunguliwa"

#define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"haikuweza kufunga Windows Event Log"

#define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"haikuweza kufungua Windows Event Log"

#define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"kodi ya hitilafu ya Soketi ya Windows"

#define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"kushindwa kufungua soketi ya winsock2"

#define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"matokeo ya WSAGetLastError baada ya wito ulioshindwa"

#define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"urefu wa herufi umekuwa zaidi ya kikomo cha juu"

#define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"urefu wa herufi uliohusika"

#define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"muundo usiofaa wa " ARG

#define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"UJUMBE WA HITILAFU YA AINA YA LENGWAO BATILI"

#endif //STUMPLESS_SW_KE_H