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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_FR_FR_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_FR_FR_H

#  define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"impossible de se lier au socket local unix"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"le tampon est trop petit pour le message donné"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative de fermeture d'un type de cible no supporté"

// todo translate
#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket winsock2"

// todo translate
#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destination valide uniquement pour les cibles réseaux"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un élément avec le nom fourni est déjà présent dans cette entrée"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un élément avec les caractéristiques spécifiées est introuvable"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno après l'échec d'appel"

// todo translate
#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the specified file"

// todo translate
#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the file"

// todo translate
#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"invalid " ARG " format"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"return code of the log handler function"

// todo translate
#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"the log handler for a function target failed"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"echec de getaddrinfo sur le hostname fourni"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"code de retour de l'échec d'appel getaddrinfo"

// todo translate
#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"GetComputerName failed"

// todo translate
#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"gethostname failed"

// todo translate
#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW failed"

// todo translate
#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW failed"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"l'index invalide, ou son -1 est trop grand pour être représenté comme un int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"l'installation invalide"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"les codes d'installations doivent être définis confirmément au RFC 5424," \
" après la multiplication par 8"

// todo translate
#  define L10N_INVALID_ID_ERROR_MESSAGE \
"invalid target id"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"index " INDEXED_THING " invalide"

// todo translate
#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ registry value was neither empty nor terminated with two NULL"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la sévérité invalide"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"les codes de sévérité doivent être définis conformément au RFC 5424:" \
" valeurs entre 0 et 7 inclus"

// todo translate
#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"target type is incompatible with this operation"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"return code of sd_journal_sendv"

// todo translate
#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"sd_journal_sendv failed"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"échec de création de fichier avec le nom de socket local choisi utilisant" \
" mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"taille maximale des messages valide uniquement pour les cibles réseaux UDP"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"could not convert the provided multibyte string to a wide char string"

// todo translate
#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"a memory allocation call failed"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"la taille du message qui a été tenté d'être envoyé"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"message trop grand pour être envoyé en un seul datagramme"

// todo translate
#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen network protocol is unsupported"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"les cibles réseaux ne sont pas supportés par cette build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " a été NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"essai d'ouverture d'un type de cible non supporté"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un paramètre avec les caractéristiques spécifiées est introuvable"

// todo translate
#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be created"

// todo translate
#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"a registry subkey could not be deleted"

// todo translate
#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"a registry subkey could not be opened"

// todo translate
#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"a registry value could not be read"

// todo translate
#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"a registry value could not be set"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto échoué avec un socket unix"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative d'envoi d'une entrée à un type de cible non supporté"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative d'envoi d'un message à un type de cible non supporté"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"envoi échoué avec un socket sys/socket.h"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"envoi échoué avec un socket winsock2"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket"

// todo translate
#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION \
L"Stumpless registration of Windows Event Log Source"

// todo translate
#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"could not write to the stream"

// todo translate
#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"the length of the offending string"

// todo translate
#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"length of string exceeded maximum limit"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ce type de cible est toujours ouvert"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"ports de transport valides uniquement pour les cibles réseaux"

// todo translate
#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"chosen transport protocol is unsupported"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket unix avec la fonction socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"vérification pour voir si un type de cible non supporté a été ouvert"

// todo translate
#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"could not close the Windows Event Log"

// todo translate
#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"could not open the Windows Event Log"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

// todo translate
#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Code d'erreur Windows Socket"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"le résultat de WSAGetLastError après l'échec de l'appel"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_FR_FR_H */
