// SPDX-License-Identifier: Apache-2.0

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

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include <stumpless/error.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/validate.h"

bool validate_msgid_length(const char* msgid ) {
  size_t max_msgid_length = 32;
  size_t msgid_char_length = strlen( msgid );
  bool validation_status = true;

  if( msgid_char_length > max_msgid_length ) {
    raise_argument_too_big( L10N_STRING_TOO_LONG, 
                            msgid_char_length, 
                            L10N_STRING_LENGTH_ERROR_CODE_TYPE );

    validation_status = false;
  }

  return validation_status;
}
