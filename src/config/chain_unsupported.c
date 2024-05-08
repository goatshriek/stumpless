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
#include <stumpless/target.h>
#include <stumpless/target/chain.h>
#include "private/config/wrapper/locale.h"
#include "private/error.h"

struct stumpless_target *
stumpless_add_target_to_chain( struct stumpless_target *chain,
                               struct stumpless_target *target ){
  raise_target_unsupported( L10N_CHAIN_TARGETS_UNSUPPORTED );
  return NULL;
}

void
stumpless_close_chain_and_contents( struct stumpless_target *chain ){
  raise_target_unsupported( L10N_CHAIN_TARGETS_UNSUPPORTED );
}

void
stumpless_close_chain_only( struct stumpless_target *chain ){
  raise_target_unsupported( L10N_CHAIN_TARGETS_UNSUPPORTED );
}

size_t
stumpless_get_chain_length( const struct stumpless_target *chain ){
  raise_target_unsupported( L10N_CHAIN_TARGETS_UNSUPPORTED );
  return 0;
}

struct stumpless_target *
stumpless_new_chain( const char *name ){
  raise_target_unsupported( L10N_CHAIN_TARGETS_UNSUPPORTED );
  return NULL;
}
