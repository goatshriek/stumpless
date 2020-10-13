/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2020 Joel E. Anderson
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

#  define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket sys/socket.h"

#  define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"échec de connexion avec un socket winsock2"

#  define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"destination valide uniquement pour les cibles réseaux"

#  define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"un élément avec le nom fourni est déjà présent dans cette entrée"

#  define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"un élément avec les caractéristiques spécifiées est introuvable"

#  define L10N_ERRNO_ERROR_CODE_TYPE \
"errno après l'échec d'appel"

#  define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"échec de création de fichier avec le nom de socket local choisi utilisant mkstemp"

#  define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"echec de getaddrinfo sur le hostname fourni"

#  define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"code de retour de l'échec d'appel getaddrinfo"

#  define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"l'index invalide, ou son -1 est trop grand pour être représenté comme un int"

#  define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"l'installation invalide"

#  define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"les codes d'installations doivent être définis confirmément au RFC 5424, après la" \
" multiplication par 8"

#  define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"index " INDEXED_THING " invalide"

#  define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"la sévérité invalide"

#  define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"les codes de sévérité doivent être définis conformément au RFC 5424: valeurs entre 0" \
" et 7 inclus"

#  define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"taille maximale des messages valide uniquement pour les cibles réseaux UDP"

#  define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"message trop grand pour être envoyé en un seul datagramme"

#  define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"la taille du message qui a été tenté d'être envoyé"

#  define L10N_NETWORK_TARGETS_UNSUPPORTED \
"les cibles réseaux ne sont pas supportés par cette build"

#  define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " a été NULL"

#  define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"essai d'ouverture d'un type de cible non supporté"

#  define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"un paramètre avec les caractéristiques spécifiées est introuvable"

#  define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative d'envoi d'une entrée à un type de cible non supporté"

#  define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"tentative d'envoi d'un message à un type de cible non supporté"

#  define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"envoi échoué avec un socket sys/socket.h"

#  define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"sendto échoué avec un socket unix"

#  define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"envoi échoué avec un socket winsock2"

#  define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket"

#  define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ce type de cible est toujours ouvert"

#  define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"ports de transport valides uniquement pour les cibles réseaux"

#  define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket unix avec la fonction socket"

#  define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"vérification pour voir si un type de cible non supporté a été ouvert"

#  define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Code d'erreur Windows Socket"

#  define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"échec d'ouverture d'un socket winsock2"

#  define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"le résultat de WSAGetLastError après l'échec de l'appel"

#  define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"STRING TOO LONG"

#  define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"STRING LENGTH ERROR CODE TYPE"

#  define L10N_MSGID_FORMAT_ERROR_MESSAGE \
"invalid msgid format"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_FR_FR_H */
