// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <stumpless/config.h>
#include <stumpless/version.h>
#include "private/config/wrapper/locale.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strbuilder.h"
#include "private/validate.h"

struct stumpless_version *
stumpless_get_version( void ) {
  struct stumpless_version *version;

  clear_error(  );

  version = alloc_mem( sizeof( struct stumpless_version ) );
  if( !version ) {
    return NULL;
  }

  version->major = STUMPLESS_MAJOR_VERSION;
  version->minor = STUMPLESS_MINOR_VERSION;
  version->patch = STUMPLESS_PATCH_VERSION;

  return version;
}

int
stumpless_version_cmp ( const struct stumpless_version * version_x,
                        const struct stumpless_version * version_y ) {
  if( !version_x ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "version_x" ) );
    return INT_MAX;
  }

  if( !version_y ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "version_y" ) );
    return INT_MAX;
  }

  if( version_x->major != version_y->major ) {
    return ( version_x->major - version_y->major ) /
           abs( version_x->major - version_y->major ) * 100;
  }

  if( version_y->minor != version_x->minor ) {
    return ( version_x->minor - version_y->minor ) /
           abs( version_x->minor - version_y->minor ) * 10;
  }

  if( version_x->patch != version_y->patch ) {
    return ( version_x->patch - version_y->patch ) /
          abs( version_x->patch - version_y->patch );
  }

  return 0;
}

char *
stumpless_version_to_string( const struct stumpless_version *version ) {
  struct strbuilder *builder;
  struct strbuilder *aggregate;
  char *version_string;

  clear_error(  );

  VALIDATE_ARG_NOT_NULL( version );

  builder = strbuilder_new(  );

  aggregate = strbuilder_append_positive_int( builder, version->major );
  aggregate = strbuilder_append_char( aggregate, '.' );
  aggregate = strbuilder_append_positive_int( aggregate, version->minor );
  aggregate = strbuilder_append_char( aggregate, '.' );
  aggregate = strbuilder_append_positive_int( aggregate, version->patch );

  version_string = strbuilder_to_string( aggregate );

  strbuilder_destroy( builder );

  return version_string;
}
