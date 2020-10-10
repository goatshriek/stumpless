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

#ifndef __STUMPLESS_PRIVATE_VALIDATE_H
#  define __STUMPLESS_PRIVATE_VALIDATE_H

#  include <stddef.h>
#  include "private/config/locale/wrapper.h"
#  include "private/error.h"

#  define VALIDATE_ARG_NOT_NULL( ARG_NAME )                         \
if( ARG_NAME == NULL ) {                                            \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) ); \
  return NULL;                                                      \
}

bool validate_msgid_length( size_t *msgid );

#endif /* __STUMPLESS_PRIVATE_VALIDATE_H */
