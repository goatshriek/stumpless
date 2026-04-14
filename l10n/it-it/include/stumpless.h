/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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

/** @mainpage Stumpless
 *
 * Stumpless è una libreria di log in C progettata per garantire prestazioni elevate
 * e con un'ampia gamma di funzionalità.
 *
 * \section basic-usage Basic Usage
 * The simplest way to get started is to use the `stumplog` function as a direct
 * replacement for the standard library's `syslog` function:
 *
 * \section basic-usage Utilizzo di base
 * Il modo più semplice per iniziare è utilizzare la funzione `stumplog` in
 * sostituzione alla funzione `syslog` della libreria standard:
 *
 * \code{.c}
 * // se sei abituato a fare questo:
 * syslog( LOG_INFO | LOG_USER, "My message #%d", count );
 *
 * / puoi iniziare sostituendo con questo:
 * stumplog( LOG_INFO | LOG_USER, "My message #%d", count );
 * \endcode
 *
 * Se non hai un target aperto per il log, i messaggi verranno salvati nel target
 * predefinito per ogni piattaforma: su Linux è \c /dev/log, sui sistemi Mac sarà
 * \c /var/run/syslog, e su Windows è nel Windows Event Log. Se hai uno o più target
 * aperti prima di richiamare `stumplog`, i log saranno salvati nel target aperto
 * più recentemente.
 *
 * Se vuoi una chiamata di funzione più breve, puoi usare la funzione stump()
 * per inviare un messaggio al target corrente. Puoi anche utilizzare gli
 * specificatori di formato proprio come faresti con \c printf.
 *
 * \code{.c}
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode
 *
 * Se non hai bisogno degli specificatori di formato, usa una delle varianti \c _str
 * come stump_str(): è sia più veloce che più sicuro!
 *
 * \code{.c}
 * stump_str( "Login failure! See structured data for info." );
 * \endcode
 *
 * Se vuoi aprire un target specifico invece di utilizzare quello predefinito, apri
 * semplicemente quello di cui hai bisogno e inizia a inviare messaggi. Per esempio,
 * per registrare i log su un file chiamato \c example.log
 *
 * \code{.c}
 * target = stumpless_open_file_target( "example.log" );
 *
 * // utilizza l'ultimo target aperto di default
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode 
 *
 * Inviare messaggi attraverso la rete a strumenti come Splunk o rsyslog è
 * altrettanto semplice:
 *
 * \code{.c}
 * target = stumpless_open_udp4_target( "send-to-splunk-example",
 *                                      "mylogserver.com" ); // oppure utilizza un IP
 * stump( "Login attempt failure #%d for user %s", count, username );
 * \endcode
 *
 * Se hai target multipli, puoi inviare messaggi a quello desiderato in questo modo:
 *
 * \code{.c}
 * stumpless_add_message( target,
 *                        "Login attempt failure #%d for user %s",
 *                        count,
 *                        username );
 * \endcode
 *
 * \section severity-shorthand Scorciatoie per i livelli di gravità
 * È comune specificare i livelli di gravità direttamente nelle chiamate di log,
 * stumpless fornisce delle funzioni macro per rendere questa pratica meno prolissa
 * e più efficiente. Per esempio, per registrare log con gravità di INFO, puoi
 * fare così:
 *
 * \code{.c}
 * stump_i( "this gets logged as an info message" );
 * \endcode
 *
 * Se desideri visualizzare anche il file sorgente , il numero di linea, e il nome della funzione
 * in ogni messaggio puoi usare stump_t() ('t' sta per 'trace'):
 *
 * \code{.c}
 * stump_t( "this includes source info" );
 * \endcode
 *
 * L'uso di queste funzioni ha l'ulteriore vantaggio di poterle rimuovere 
 * durante la fase di compilazione, semplicemente definendo i simboli  \c STUMPLESS_ENABLE_UPTO
 * o \c STUMPLESS_DISABLE_DOWNTO corretti. Questo rende semplice cambiare i livelli di logging
 * tra diverse build, per avere le versioni di produzione e di debug senza differenze nel 
 * codice sorgente.
 *
 * \code{.c}
 * // Assicurati di specificare questo prima di includere stumpless.h
 * #define STUMPLESS_ENABLE_UPTO_INFO
 *
 * // ...
 *
 * // questo log sarà preservato
 * stump_i( "I'm doing that thing you asked" );
 *
 * // questo messaggio di debug sarà completamente rimosso: nessun impatto a runtime
 * stump_d( "DEBUG info: %d, %d, %s", thing_1, thing_2, stringy_thingy );
 * \endcode
 *
 * Consulta gli headers nella cartella include/stumpless/level, che prendono il nome 
 * dai livelli di gravità (come per esempio \ref alert.h), per vedere l'elenco completo 
 * delle funzioni abbreviate, oppure guarda \ref severity_level_example.c per vedere 
 * un programma completo in esecuzione.
 *
 */

/** @example basic_example.c
 * Dimostra come utilizzare le funzioni di logging base (stump(), stump_str(),
 * stumpless_add_message(), stumplog()).
 */

/** @example cpp_example.cpp
 * Dimostra come utilizzare Stumpless attraverso un binding C++.
 */

/** @example entry_example.c
 * Dimostra modalità differenti per lavorare con stumpless_entry e le 
 * relative strutture.
 */

/** @example file_example.c
 * Dimostra come lavorare con un file target.
 */

/** @example filter_example.c
 * Dimostra come lavorare con i filtri a runtime nei target di log.
 */

/** @example function_example.c
 * Dimostra come lavorare con una funzione target.
 */

/** @example severity_level_example.c
 * Dimostra come lavorare con i livelli di gravità degli eventi di log.
 */

/** @example stream_example.c
 * Dimostra come lavorare con uno stream target.
 */

/** @file
 * Il file header principale della libreria di logging stumpless. A meno che tu non
 * stia cercando specificamente di includere SOLO gli header necessari, la scelta
 * migliore è includere semplicemente questo file per utilizzare stumpless.
 * Assicurerà che tutte le funzionalità disponibili siano dichiarate, oltre a
 * gestire l'ordine o le inclusioni condizionali che potrebbero essere necessarie
 * sulla piattaforma di destinazione.
 *
 * Se desideri includere solo file header specifici, puoi usare questo file
 * come modello. Nota che tutti gli header si trovano nella directory stumpless,
 * che deve essere presente nel percorso di inclusione (include path).
 */

#ifndef __STUMPLESS_H
#define __STUMPLESS_H

#include <stumpless/config.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/facility.h>
#include <stumpless/filter.h>
#include <stumpless/generator.h>
#include <stumpless/id.h>
#include <stumpless/level/alert.h>
#include <stumpless/level/crit.h>
#include <stumpless/level/debug.h>
#include <stumpless/level/emerg.h>
#include <stumpless/level/err.h>
#include <stumpless/level/info.h>
#include <stumpless/level/notice.h>
#include <stumpless/level/trace.h>
#include <stumpless/level/warning.h>
#include <stumpless/log.h>
#include <stumpless/memory.h>
#include <stumpless/option.h>
#include <stumpless/param.h>
#include <stumpless/prival.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/file.h>
#include <stumpless/target/function.h>
#include <stumpless/target/sqlite3.h>
#include <stumpless/target/stream.h>
#include <stumpless/version.h>

#ifdef STUMPLESS_CHAIN_TARGETS_SUPPORTED
/** @example chain_example.c
 * Dimostra come lavorare con una catena di target.
 */

#  include <stumpless/target/chain.h>
#endif

#ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/** @example journald_example.c
 * Dimostra come lavorare con un target journal.
 */

#  include <stumpless/config/journald_supported.h>
#  include <stumpless/target/journald.h>
#endif

#ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
/** @example tcp_example.c
 * Dimostra come lavorare con un target di rete che ha un endpoint TCP.
 */

/** @example udp_example.c
 * Dimostra come lavorare con un target di rete che ha un endpoint UDP.
 */

#  include <stumpless/target/network.h>
#endif

#ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
/** @example socket_example.c
 * Dimostra come lavorare con un socket target.
 */

#  include <stumpless/target/socket.h>
#endif

#ifdef STUMPLESS_SQLITE3_TARGETS_SUPPORTED
/** @example sqlite3_example.c
 * Dimostra come lavorare con un target sqlite3.
 *
 * @dalla versione v2.2.0
 */
#endif

#ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
/** @example wel_example.c
 * Demonstrates how to work with a Windows Event Log target.
 * Dimostra come lavorare con il Windows Event Log come target.
 */

#  include <stumpless/config/wel_supported.h>
#  include <stumpless/target/wel.h>
#  include <stumpless/windows/default_events.h>
#endif

#endif /* __STUMPLESS_H */
