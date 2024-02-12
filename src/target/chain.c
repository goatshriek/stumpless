// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/chain.h>
#include "private/config.h"
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/chain.h"
#include "private/validate.h"

void
stumpless_close_chain_and_contents( struct stumpless_target *target ) {
  if( unlikely( !target ) ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( unlikely( target->type != STUMPLESS_CHAIN_TARGET ) ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_chain_target( target->id );
  destroy_target( target );
  clear_error();
}

void
stumpless_close_chain_only( struct stumpless_target *target ) {
  if( unlikely( !target ) ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( unlikely( target->type != STUMPLESS_CHAIN_TARGET ) ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_chain_target( target->id );
  destroy_target( target );
  clear_error();
}

struct stumpless_target *
stumpless_new_chain( const char *name ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_CHAIN_TARGET, name );

  if( unlikely( !target ) ) {
    goto fail;
  }

  target->id = new_chain_target();
  if( unlikely( !target->id ) ) {
    goto fail_id;
  }

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

/* private definitions */

void
destroy_chain_target( const struct chain_target *target ) {
  config_destroy_mutex( &target->chain_mutex );
  free_mem( target->overflow_targets );
  free_mem( target );
}

struct chain_target *
new_chain_target( void ) {
  struct chain_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( unlikely( !target ) ) {
    return NULL;
  }

  target->target_count = 0;
  target->overflow_targets = NULL;
  config_init_mutex( &target->chain_mutex );

  return target;
}

int
sendto_chain( struct chain_target *target,
              struct stumpless_entry *entry ) {
  size_t i;
  int result;
  int final_result = 1;
  struct stumpless_target *sub_target;

  for( i = 0; i < target->target_count; i++ ) {
    if( i < CHAIN_TARGET_ARRAY_SIZE ) {
      sub_target = target->targets[i];
    } else {
      sub_target = target->overflow_targets[i - CHAIN_TARGET_ARRAY_SIZE];
    }

    result = stumpless_add_entry( sub_target, entry );
    if( unlikely( result < 0 ) ) {
      final_result = result;
    }
  }

  return final_result;
}
