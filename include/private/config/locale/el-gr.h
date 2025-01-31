/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2023 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_EL_GR_H
# define __STUMPLESS_PRIVATE_CONFIG_LOCALE_EL_GR_H

# define L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"αδυναμία δέσμευσης στην τοπική υποδοχή unix"

// todo translate
#  define L10N_BUFFER_SIZE_ERROR_CODE_TYPE \
"buffer used to store the message"

# define L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE \
"το μέγεθος του αποθηκευτικού μέσου δεν επαρκεί για το δοθέν μήνυμα"

// todo translate
#  define L10N_CHAIN_TARGETS_UNSUPPORTED \
"chain targets are not supported by this build"

# define L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"προσπάθεια κλεισίματος ανυποστήρικτου τύπο στόχου"

// todo translate
#  define L10N_COMMIT_TRANSACTION_FAILED_ERROR_MESSAGE \
"CommitTransaction failed"

# define L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχής σύνδεση με τον υποδοχέα sys/socket.h"

# define L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχής σύνδεση με τον υποδοχέα winsock2"

// todo translate
#  define L10N_CREATE_TRANSACTION_FAILED_ERROR_MESSAGE \
"CreateTransaction failed"

# define L10N_DESTINATION_NETWORK_ONLY_ERROR_MESSAGE \
"ο προορισμός είναι έγκυρος μόνο για δίκτυα"

# define L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE \
"ένα στοιχείο με το παρεχόμενο όνομα υπάρχει ήδη στις καταχωρήσεις"

# define L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE \
"αδυναμία εύρεσης στοιχείου με τα καθορισμένα χαρακτηριστικά"

# define L10N_ERRNO_ERROR_CODE_TYPE \
"η αποτυχής συνάρτηση επέστρεψε errno"

# define L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE \
"αδυναμία ανοίγματος του συγκεκριμένου αρχείου"

# define L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE \
"αδυναμία εγγραφής στο αρχείο"

# define L10N_FORMAT_ERROR_MESSAGE(ARG) \
"Μη έγκυρο μορφή" ARG

# define L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE \
"κωδικός της συνάρτησης χειριστής των καταγραφών"

# define L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE \
"αποτυχία χειριστής καταγραφών για μία συνάρτηση στόχου"

# define L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE \
"αποτυχία του getaddrinfo στο δοθέν hostname"

# define L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE \
"κωδικός επιστροφής της συνάρτησης getaddrinfo"

# define L10N_GETCOMPUTERNAME_FAILED_ERROR_MESSAGE \
"αποτυχία GetComputerName"

# define L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE \
"αποτυχία gethostname"

# define L10N_GETLASTERROR_ERROR_CODE_TYPE \
"αποτέλεσμα του GetLastError εφόσον της αποτυχημένης κλήσης της συνάρτησης"

// todo translate
#  define L10N_GETMODULEFILENAMEW_FAILED_ERROR_MESSAGE \
"GetModuleFileNameW failed"

// todo translate
#  define L10N_GETMODULEHANDLEXW_FAILED_ERROR_MESSAGE \
"GetModuleHandleExW failed"

# define L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE \
"μη έγκυρη δείκτης, ή το αποτέλεσμα της αφαίρεση του δείκτη κατά 1 είναι" \
" υπερβολικά μεγάλο για να αναπαρασταθεί ως int"

# define L10N_INVALID_FACILITY_ERROR_CODE_TYPE \
"μη έγκυρο εγκατάσταση"

# define L10N_INVALID_FACILITY_ERROR_MESSAGE \
"ο κωδικός εγκατάστασης πρέπει να είναι καθορισμένο σε σχέση με το RFC" \
" 5424, εφόσον πολλαπλασιαστεί με το 8"

# define L10N_INVALID_ID_ERROR_MESSAGE \
"μη έγκυρη ταυτότητα στόχου"

# define L10N_INVALID_INDEX_ERROR_MESSAGE( INDEXED_THING ) \
"μη έγκυρος " INDEXED_THING " δείκτης"

// todo translate
#  define L10N_INVALID_MULTI_SZ_ERROR_MESSAGE \
"a MULTI_SZ registry value was neither empty nor terminated with two NULL" \
" characters"

// todo translate
#  define L10N_INVALID_PARAM_ERROR_MESSAGE \
"the string is not of the name=\"value\" format"

# define L10N_INVALID_SEVERITY_ERROR_CODE_TYPE \
"μη έγκυρη σοβαρότητα"

# define L10N_INVALID_SEVERITY_ERROR_MESSAGE \
"οι κωδικοί σοβαρότητας πρέπει να είναι καθορισμένοι με βάση το RFC 5424" \
" και οι τιμές να είναι στο εύρος 0 έως 7"

// todo translate
#  define L10N_INVALID_STATE_DURING_UTF8_PARSING \
"invalid state reached during UTF-8 string parsing"

# define L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE \
"ΣΦΑΛΜΑ: ΜΗ ΕΓΚΥΡΟΣ ΤΥΠΟΣ ΣΤΟΧΟΥ"

# define L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE \
"κωδικός επιστροφής της sd_journal_sendv"

# define L10N_JOURNALD_FAILURE_ERROR_MESSAGE \
"αποτυχία sd_journal_sendv"

# define L10N_LOCAL_SOCKET_NAME_FILE_OPEN_ERROR_MESSAGE \
"αδυναμία δημιουργίας ενός αρχείου με το επιλεγόμενο όνομα υποδοχέα και την" \
" χρήση του mkstemp"

# define L10N_MAX_MESSAGE_SIZE_UDP_ONLY_ERROR_MESSAGE \
"το μέγιστο μέγεθος μηνυμάτων είναι έγκυρο μόνο για στόχους UDP"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

// todo translate
#  define L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE \
"could not convert the provided multibyte string to a wide char string"

# define L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE \
"αποτυχία συνάρτησης τροποποίησης μνήμης"

# define L10N_MESSAGE_SIZE_ERROR_CODE_TYPE \
"το μέγεθος του μηνύματος που επιχειρήθηκε να σταλθεί"

# define L10N_MESSAGE_TOO_BIG_FOR_DATAGRAM_ERROR_MESSAGE \
"το μέγεθος του μηνύματος είναι υπερβολικά μεγάλο για να σταλθεί σε ένα" \
" διάγραμμα"

// todo translate
#  define L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE \
"gethostbyname[2] and inet_pton failed to resolve the name"

// todo translate
#  define L10N_NETWORK_CLOSED_ERROR_MESSAGE \
"the network connection is closed"

# define L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"το πρωτόκολλο του δικτύου που επιλέχθηκε δεν υποστηρίζεται"

# define L10N_NETWORK_TARGETS_UNSUPPORTED \
"οι στόχοι του δικτύου δεν υποστηρίζονται σε αυτήν την έκδοση"

# define L10N_NULL_ARG_ERROR_MESSAGE( ARG_NAME ) \
ARG_NAME " κατέχει την τιμή NULL"

# define L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"προσπάθεια ανοίγματος μη υποστηριζόμενου τύπου στόχου"

# define L10N_PARAM_NOT_FOUND_ERROR_MESSAGE \
"αδυναμία εύρεσης παράμετρος με τα καθορισμένα χαρακτηριστικά"

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

# define L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχία συνάρτησης sendto σε υποδοχέα unix"

# define L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"προσπάθεια αποστολής μίας εγγραφής σε μη υποστηριζόμενο τύπο στόχου"

# define L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"προσπάθεια αποστολής ενός μηνύματος σε μη υποστηριζόμενο τύπο στόχου"

# define L10N_SEND_SYS_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχία συνάρτησης send σε υποδοχέα sys/socket.h"

# define L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχία συνάρτησης send σε υποδοχέα winsock2"

// todo translate
#  define L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE \
"severity colors are only supported for stream targets"

# define L10N_SOCKET_FAILED_ERROR_MESSAGE \
"αποτυχία ανοίγματος υποδοχέα"

// todo translate
#  define L10N_SOURCE_REGISTRATION_TRANSACTION_DESCRIPTION_W \
L"Stumpless registration of Windows Event Log Source"

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

# define L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE \
"αδυναμία εγγραφής στη ροή δεδομένων (stream)"

# define L10N_STRING_LENGTH_ERROR_CODE_TYPE \
"το μήκος της παραπάνω συμβολοσειράς"

# define L10N_STRING_TOO_LONG_ERROR_MESSAGE \
"το μήκος της συμβολοσειράς υπερβαίνει το ανώτερο μήκος"

# define L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE \
"ο στόχος είναι πάντα ανοικτός"

# define L10N_TRANSPORT_PORT_NETWORK_ONLY_ERROR_MESSAGE \
"οι θύρες μεταφοράς είναι έγκυρες μόνο για στόχους του δικτύου"

# define L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE \
"το πρωτόκολλο που επιλέχθηκε δεν υποστηρίζεται"

# define L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE \
"αδυναμία ανοίγματος ενός υποδοχέα unix με την χρήση μίας συνάρτησης υποδοχής"

# define L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE \
"έλεγχος αν ένας μη υποστηριζόμενος τύπος στόχου έχει ανοίξει"

# define L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE \
"αδυναμία κλεισίματος του Windows Event Log"

# define L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE \
"αδυναμία ανοίγματος του Windows Event Log"

// todo translate
#  define L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE \
"could not convert the provided wide char string to a multibyte string"

// todo translate
#  define L10N_WINDOWS_RETURN_ERROR_CODE_TYPE \
"the Windows error code returned by the failed call"

# define L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE \
"Κωδικός σφάλματος σε υποδοχέα των Windows"

// todo translate
#  define L10N_WINDOWS_WIDE_TO_MB_CONVERSION_ERROR_CODE_TYPE \
"the result of GetLastError after the failed call"

# define L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE \
"αδυναμία ανοίγματος ενός υποδοχέα winsock2"

# define L10N_WSAGETLASTERROR_ERROR_CODE_TYPE \
"το αποτέλεσμα της WSAGetLastError εφόσον απότυχε η κλήση της συνάρτησης"

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_EL_GR_H */
