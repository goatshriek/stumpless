/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_ERROR_H
#  define __STUMPLESS_PRIVATE_ERROR_H

#  include <stumpless/error.h>

void
clear_error( void );

void
raise_argument_empty( void );

void
raise_argument_too_big( void );

void
raise_error( enum stumpless_error_id id );

void
raise_file_open_failure( void );

void
raise_file_write_failure( void );

void
raise_invalid_id( void );

void
raise_memory_allocation_failure( void );

void
raise_socket_bind_failure( void );

void
raise_stream_write_failure( void );

void
raise_target_unsupported( void );

void
raise_wel_close_failure( void );

void
raise_wel_open_failure( void );

#endif /* __STUMPLESS_PRIVATE_ERROR_H */
