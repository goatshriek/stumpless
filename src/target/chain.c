// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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

#include <stddef.h>
#include <stdio.h>
#include <stumpless/target.h>
#include <stumpless/target/file.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/file.h"
#include "private/validate.h"
#include "private/config/wrapper/fopen.h"

void
stumpless_close_chain( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_CHAIN ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_target( target );
  clear_error(  );

  // TODO finish
}

struct stumpless_target *
stumpless_new_chain( void ) {
  // TODO finish

  return NULL;
}
