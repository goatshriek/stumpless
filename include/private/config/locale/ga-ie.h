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

 //see more Irish Gaelic computing terminology aid here: https://www3.smo.uhi.ac.uk/oduibhin/tearmai/liosta.htm 

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"níorbh fhéidir ceangal leis an soicéad Unix áitiúil"

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"maolán a úsáidtear chun an teachtaireacht a stóráil"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"tá an maolán róbheag don teachtaireacht seo"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"ní thacaítear le spriocanna slabhra sa leagan seo"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"rinneadh iarracht spriocchineál nach dtacaítear leis a dhúnadh"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"Theip ar CommitTransaction"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar an nasc le soicéad sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar an nasc le soicéad winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"Theip ar CreateTransaction"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"níl an ceann scríbe bailí ach do spriocanna líonra"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"tá eilimint leis an ainm seo cheana san iontráil seo"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"níor aimsíodh eilimint leis na saintréithe sonraithe"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno tar éis an ghlao theipthe"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"níorbh fhéidir an comhad sonraithe a oscailt"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"níorbh fhéidir scríobh chuig an gcomhad"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"formáid neamhbhailí " ARG

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"cód fillte na feidhme láimhseála loga"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"theip ar an láimhseálaí loga do sprioc feidhme"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"theip ar getaddrinfo don óstainm a soláthraíodh"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"cód fillte an ghlao getaddrinfo a theip"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"Theip ar GetComputerName"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"Theip ar gethostname"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"toradh GetLastError tar éis an ghlao theip"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"Theip ar GetModuleFileNameW"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"Theip ar GetModuleHandleExW"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"an t-innéacs neamhbhailí, nó -1 má tá sé ró-mhór le léiriú mar int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"an tsaoráid neamhbhailí"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"caithfear cóid saoráide a shainiú de réir RFC 5424, tar éis iad a iolrú faoi 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"aitheantas sprice neamhbhailí"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"innéacs neamhbhailí " INDEXED_THING

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"ní raibh luach clárlainne MULTI_SZ folamh ná críochnaithe le dhá charachtar NULL"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"níl an teaghrán sa bhformáid name=\"value\""

#  define L10N_INVALID_PRIVAL_ERROR_CODE_TYPE \
"an prival neamhbhailí"

#  define L10N_INVALID_PRIVAL_ERROR_MESSAGE \
"caithfear cóid prival a shainiú de réir RFC 5424: luachanna idir 0 agus 255 san áireamh"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"an déine neamhbhailí"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"caithfear cóid déine a shainiú de réir RFC 5424: luachanna idir 0 agus 7 san áireamh"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"baineadh staid neamhbhailí amach le linn parsála UTF-8"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"níl an cineál sprice comhoiriúnach leis an oibríocht seo"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"cód fillte sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"Theip ar sd_journal_sendv"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"níorbh fhéidir comhad a chruthú leis an ainm soicéid áitiúil roghnaithe le mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"níl uasmhéid na teachtaireachta bailí ach do spriocanna líonra UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"toradh GetLastError tar éis an ghlao theip"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"níorbh fhéidir an teaghrán ilbheart a thiontú go teaghrán carachtar leathan"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"theip ar leithdháileadh cuimhne"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"méid na teachtaireachta a rinneadh iarracht a sheoladh"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"tá an teachtaireacht ró-mhór le seoladh i ndataghram amháin"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"theip ar gethostbyname[2] agus inet_pton an t-ainm a réiteach"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"tá an nasc líonra dúnta"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"ní thacaítear leis an bprótacal líonra roghnaithe"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"ní thacaítear le spriocanna líonra sa leagan seo"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " bhí NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"rinneadh iarracht spriocchineál nach dtacaítear leis a oscailt"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"níor aimsíodh paraiméadar leis na saintréithe sonraithe"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"níorbh fhéidir fo-eochair chlárlainne a chruthú"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"níorbh fhéidir fo-eochair chlárlainne a scriosadh"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"níorbh fhéidir fo-eochair chlárlainne a oscailt"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"níorbh fhéidir luach clárlainne a léamh"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"níorbh fhéidir luach clárlainne a shocrú"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar sendto le soicéad Unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"rinneadh iarracht iontráil a sheoladh chuig spriocchineál nach dtacaítear leis"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"rinneadh iarracht teachtaireacht a sheoladh chuig spriocchineál nach dtacaítear leis"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar sheoladh le soicéad sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar sheoladh le soicéad winsock2"

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"ní thacaítear le dathanna déine ach do spriocanna srutha"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar oscailt soicéid"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Clárú Stumpless ar Fhoinse Loga Imeachtaí Windows"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"níorbh fhéidir " PARAM " a cheangal leis an ráiteas"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"bhí an bunachar sonraí gnóthach agus níorbh fhéidir an t-idirbheart a chríochnú"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"níorbh fhéidir bunachar sonraí sqlite3 a dhúnadh"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"theip ar aisghlao saincheaptha do ráitis ullmhaithe"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"níorbh fhéidir bunachar sonraí sqlite3 a oscailt"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"Theip ar sqlite3_prepare_v2"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"cód fillte an ghlao sqlite3 a theip"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"líon na n-uaireanta a rinneadh iarracht arís"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"Theip ar sqlite3_step"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"ní thacaítear le spriocanna sqlite3 sa leagan seo"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"níorbh fhéidir scríobh chuig an sruth"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"fad an teaghráin chiontaigh"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"sháraigh fad an teaghráin an teorainn uasta"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"bíonn an cineál sprice seo oscailte i gcónaí"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"níl calafoirt iompair bailí ach do spriocanna líonra"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"ní thacaítear leis an bprótacal iompair roghnaithe"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar oscailt soicéid Unix leis an bhfeidhm socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"rinneadh seiceáil an raibh spriocchineál nach dtacaítear leis oscailte"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"níorbh fhéidir Loga Imeachtaí Windows a dhúnadh"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"níorbh fhéidir Loga Imeachtaí Windows a oscailt"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"níorbh fhéidir an teaghrán carachtar leathan a thiontú go teaghrán ilbheart"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"cód earráide Windows a cuireadh ar ais ón nglao theip"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"cód earráide Soicéid Windows"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"toradh GetLastError tar éis an ghlao theip"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"theip ar oscailt soicéid winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"toradh WSAGetLastError tar éis an ghlao theip"


#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_EN_US_H */
