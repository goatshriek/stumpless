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
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/chain.h>
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/chain.h"
#include "private/validate.h"


struct stumpless_target *
stumpless_add_target_to_chain( struct stumpless_target *chain,
                               struct stumpless_target *target ){
  size_t count;
  struct chain_target *internal_chain;
  size_t overflow_count;
  size_t old_size;
  size_t new_size;
  struct stumpless_target **new_targets;
  struct stumpless_target *result = chain;

  VALIDATE_ARG_NOT_NULL( chain );
  VALIDATE_ARG_NOT_NULL( target );

  clear_error();

  lock_target( chain );

  if( chain->type != STUMPLESS_CHAIN_TARGET ){
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    result = NULL;
    goto finish;
  }

  internal_chain = chain->id;
  lock_chain_target( internal_chain );

  count = internal_chain->target_count;
  if( unlikely( count >= STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH ) ){
    overflow_count = count - STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH;
    old_size = overflow_count * sizeof( target );
    new_size = old_size + sizeof( target );
    new_targets = realloc_mem( internal_chain->overflow_targets, new_size );
    if( !new_targets ){
      result = NULL;
      goto internal_finish;
    }

    new_targets[overflow_count] = target;
    internal_chain->overflow_targets = new_targets;
  } else {
    internal_chain->targets[internal_chain->target_count] = target;
  }

  internal_chain->target_count++;

internal_finish:
  unlock_chain_target( internal_chain );
finish:
  unlock_target( chain );
  return result;
}

void
stumpless_close_chain_and_contents( struct stumpless_target *chain ){
  const struct chain_target *internal_target;
  size_t i;
  size_t index;
  struct stumpless_target *curr;

  VALIDATE_ARG_NOT_NULL_VOID_RETURN( chain );

  if( unlikely( chain->type != STUMPLESS_CHAIN_TARGET ) ){
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  internal_target = chain->id;
  for( i = 0; i < internal_target->target_count; i++ ){
    if( unlikely( i >= STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH ) ){
      index = i - STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH;
      curr = internal_target->overflow_targets[index];
    } else {
      curr = internal_target->targets[i];
    }

    stumpless_close_target( curr );
  }

  destroy_chain_target( internal_target );
  destroy_target( chain );
  clear_error();
}

void
stumpless_close_chain_only( struct stumpless_target *chain ){
  VALIDATE_ARG_NOT_NULL_VOID_RETURN( chain );

  if( unlikely( chain->type != STUMPLESS_CHAIN_TARGET ) ){
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_chain_target( chain->id );
  destroy_target( chain );
  clear_error();
}

size_t
stumpless_get_chain_length( const struct stumpless_target *chain ){
  struct chain_target *internal_chain;
  size_t result;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( chain );

  if( unlikely( chain->type != STUMPLESS_CHAIN_TARGET ) ){
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return 0;
  }

  if( unlikely( !chain->id ) ){
    raise_invalid_id(  );
    return 0;
  }

  clear_error();
  internal_chain = chain->id;
  lock_chain_target( internal_chain );
  result = internal_chain->target_count;
  unlock_chain_target( internal_chain );
  return result;
}

struct stumpless_target *
stumpless_new_chain( const char *name ){
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_CHAIN_TARGET, name );

  if( unlikely( !target ) ){
    goto fail;
  }

  target->id = new_chain_target();
  if( unlikely( !target->id ) ){
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
destroy_chain_target( const struct chain_target *chain ){
  config_destroy_mutex( &chain->chain_mutex );
  free_mem( chain->overflow_targets );
  free_mem( chain );
}

void
lock_chain_target( struct chain_target *chain ){
  config_lock_mutex( &chain->chain_mutex );
}

struct chain_target *
new_chain_target( void ){
  struct chain_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( unlikely( !target ) ){
    return NULL;
  }

  target->target_count = 0;
  target->overflow_targets = NULL;
  config_init_mutex( &target->chain_mutex );

  return target;
}

int
send_entry_to_chain_target( struct chain_target *chain,
                            const struct stumpless_entry *entry ){
  size_t i;
  int result;
  int final_result = 1;
  size_t index;
  struct stumpless_target *sub_target;

  lock_chain_target( chain );

  for( i = 0; i < chain->target_count; i++ ){
    if( i < STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH ){
      sub_target = chain->targets[i];
    } else {
      index = i - STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH;
      sub_target = chain->overflow_targets[index];
    }

    result = stumpless_add_entry( sub_target, entry );
    if( unlikely( result < 0 ) ){
      final_result = result;
    }
  }

  unlock_chain_target( chain );
  return final_result;
}

void
unlock_chain_target( struct chain_target *chain ){
  config_unlock_mutex( &chain->chain_mutex );
}
