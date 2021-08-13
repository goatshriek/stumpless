/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_JOURNALD_H
#  define __STUMPLESS_PRIVATE_TARGET_JOURNALD_H

#  include <stddef.h>
#  include <stumpless/element.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>
#  include <stumpless/target.h>

/**
 * Gets a journald-compliant field name from a given UTF-8 string.
 *
 * @return the number of bytes written to the flattened buffer.
 */
size_t
get_journald_field_name( char *flattened, const char *raw, size_t size );

void
init_fields( size_t field_count );

void
init_fixed_fields( void );

/**
 * Initializes an element's journald fields.
 *
 * @param element The element to initialize.
 */
void
journald_init_journald_element( struct stumpless_element *element );

/**
 * Initializes a param's journald fields.
 *
 * @param param The param to initialize.
 */
void
journald_init_journald_param( struct stumpless_param *param );

void
journald_free_thread( void );

size_t
load_sd_fields( const struct stumpless_entry *entry );

int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry );

void
set_field_bases( void );

#endif /* __STUMPLESS_PRIVATE_TARGET_JOURNALD_H */
