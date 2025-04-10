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

#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"le tampon utilisé pour stocker le message"

#  define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"le tampon est trop petit pour le message donné"

#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"les cibles chaînées ne sont pas supportées par ce build"

#  define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative de fermeture d'un type de cible no supporté"

#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"échec de CommitTransaction"

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket winsock2"

#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"échec de CreateTransaction"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destination valide uniquement pour les cibles réseaux"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un élément avec le nom fourni est déjà présent dans cette entrée"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un élément avec les caractéristiques spécifiées est introuvable"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno après l'échec d'appel"

#  define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"échec de l'ouverture du fichier spécifié"

#  define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"échec de l'écriture sur le fichier"

#  define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"le format pour " ARG " est invalid"

#  define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"code retourné par la fonction du gestionnaire de log"

#  define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"le gestionnaire de log pour une cible fonction à échoué"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"échec de getaddrinfo sur le hostname fourni"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"code de retour de l'échec d'appel getaddrinfo"

#  define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"échec de GetComputerName"

#  define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"échec de gethostname"

#  define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"le résultat de GetLastError après l'échec de l'appel"

#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"échec de GetModuleFileNameW"

#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"échec de GetModuleHandleExW"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"l'index invalide, ou son -1 est trop grand pour être représenté comme un int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"l'installation invalide"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"les codes d'installations doivent être définis confirmément au RFC 5424," \
" après la multiplication par 8"

#  define L10N_INVALID_ID_ERROR_MESSAGE \
"id cible invalide"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"index " INDEXED_THING " invalide"

#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"la valeur d'un registre MULTI_SZ n'était ni vide ni terminée par deux NULL"

#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"la chaîne de caractères n'est pas au format nom=\"valeur\""

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la sévérité invalide"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"les codes de sévérité doivent être définis conformément au RFC 5424:" \
" valeurs entre 0 et 7 inclus"

#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"état invalide atteint pendant UTF-8 string parsing"

#  define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"le type de la cible est incompatible avec cette opération"

#  define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"code retourné par sd_journal_sendv"

#  define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"échec de sd_journal_sendv"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"échec de création de fichier avec le nom de socket local choisi utilisant" \
" mkstemp"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"taille maximale des messages valide uniquement pour les cibles réseaux UDP"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"le résultat de GetLastError après l'échec de l'appel"

#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"échec de la conversion du multibyte string fourni en un wide char string"

#  define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"un appel à l'allocation de la mémoire a échoué"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"la taille du message qui a été tenté d'être envoyé"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"message trop grand pour être envoyé en un seul datagramme"

#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] et inet_pton échec de résolvez le nom"

#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"la connection réseau est fermée"

#  define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"le protocol réseau choisi n'est pas supporté"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"les cibles réseaux ne sont pas supportés par ce build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " a été NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"essai d'ouverture d'un type de cible non supporté"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un paramètre avec les caractéristiques spécifiées est introuvable"

#  define L10N_REGISTRY_SUBKEY_CREATION_FAILED_ERROR_MESSAGE \
"une sous-clé de registre n'a pas pu être créée"

#  define L10N_REGISTRY_SUBKEY_DELETION_FAILED_ERROR_MESSAGE \
"une sous-clé de registre n'a pas pu être supprimée"

#  define L10N_REGISTRY_SUBKEY_OPEN_FAILED_ERROR_MESSAGE \
"une sous-clé de registre n'a pas pu être ouverte"

#  define L10N_REGISTRY_VALUE_GET_FAILED_ERROR_MESSAGE \
"une valeur de registre n'a pas pu être lue"

#  define L10N_REGISTRY_VALUE_SET_FAILED_ERROR_MESSAGE \
"une valeur de registre n'a pas pu être définie"

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

#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"les couleurs de sévérité sont uniquement supportées pour " \
"les cibles de type stream"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket"

#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"enregistrement Stumpless de Windows Event Log Source"

#  define L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( PARAM )  \
"n'a pas pu lier " PARAM " à la déclaration"

#  define L10N_SQLITE3_BUSY_ERROR_MESSAGE \
"la base de données était occupée et n'a pas pu terminer la transaction"

#  define L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE \
"n'a pas pu fermer la base de données sqlite3"

#  define L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE \
"une callback personnalisée pour la préparation a échoué"

#  define L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE \
"n'a pas pu ouvrir la base de données sqlite3"

#  define L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE \
"sqlite3_prepare_v2 a échoué"

#  define L10N_SQLITE3_RESULT_CODE_TYPE \
"le code de retour de l'appel sqlite3 qui a échoue"

#  define L10N_SQLITE3_RETRY_COUNT_CODE_TYPE \
"le nombre de fois que l'opération a été tenté"

#  define L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE \
"sqlite3_step a échoué"

#  define L10N_SQLITE3_TARGETS_UNSUPPORTED \
"les cibles sqlite3 ne sont pas supportées par ce build"

#  define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"impossible d'écrire dans le flux"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"la longueur du string offensant"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"la longueur du string a excédée la limite maximale"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ce type de cible est toujours ouvert"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"ports de transport valides uniquement pour les cibles réseaux"

#  define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"le protocol de transport choisi n'est pas supporté"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket unix avec la fonction socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"vérification pour voir si un type de cible non supporté a été ouvert"

#  define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"échec de la fermeture de Windows Event Log"

#  define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"échec de l'ouverture de Windows Event Log"

#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"échec de la conversion du wide char string fourni en un multibyte string"

#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"le code d'erreur Windows retourné par l'échec de l'appel"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Code d'erreur Windows Socket"

#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"le résultat de GetLastError après l'échec de l'appel"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"le résultat de WSAGetLastError après l'échec de l'appel"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_FR_FR_H */
