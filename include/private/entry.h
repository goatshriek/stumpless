/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_ENTRY_H
#  define __STUMPLESS_PRIVATE_ENTRY_H

#  include <stdbool.h>
#  include <stumpless/entry.h>
#  include "private/strbuilder.h"

void
entry_free_all( void );

int
get_prival( int facility, int severity );

int
lock_entry( const struct stumpless_entry *entry );

struct stumpless_entry *
locked_add_element( struct stumpless_entry *entry,
                    struct stumpless_element *element );

struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder );

struct strbuilder *
strbuilder_append_msgid( struct strbuilder *builder,
                         const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_message( struct strbuilder *builder,
                           const struct stumpless_entry *entry );

struct strbuilder *
strbuilder_append_procid( struct strbuilder *builder );

struct strbuilder *
strbuilder_append_structured_data( struct strbuilder *builder,
                                   const struct stumpless_entry *entry );

void
unchecked_destroy_entry( const struct stumpless_entry *entry );

bool
unchecked_entry_has_element( const struct stumpless_entry *entry,
                             const char *name );

int
unlock_entry( const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_ENTRY_H */
