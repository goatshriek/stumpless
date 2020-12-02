// SPDX-License-Identifier: Apache-2.0

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

#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include "private/config/have_unistd_gethostname.h"
#include "private/config/locale/wrapper.h"
#include "private/error.h"

int
unistd_gethostname( char *buffer, size_t namelen ) {
  int result;

  result = gethostname( buffer, namelen );
  buffer[namelen - 1] = '\0';

  if( result == -1 ) {
    raise_gethostname_failure( L10N_GETHOSTNAME_FAILED_ERROR_MESSAGE,
                               errno,
                               L10N_ERRNO_ERROR_CODE_TYPE );
  }

  return result;
}
