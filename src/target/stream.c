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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/severity.h>
#include <stumpless/entry.h>
#include <stumpless/target/stream.h>
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/stream.h"
#include "private/validate.h"
#include "private/severity.h"

void
stumpless_close_stream_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_STREAM_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  clear_error(  );
  destroy_stream_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_stderr_target( const char *name ) {
  struct stumpless_target *target = stumpless_open_stream_target( name, stderr );

  if (target == NULL) return NULL;
  
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_EMERG_VALUE  , STUMPLESS_SEVERITY_EMERG_DEFAULT_COLOR  );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_ALERT_VALUE  , STUMPLESS_SEVERITY_ALERT_DEFAULT_COLOR  );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_CRIT_VALUE   , STUMPLESS_SEVERITY_CRIT_DEFAULT_COLOR   );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_ERR_VALUE    , STUMPLESS_SEVERITY_ERR_DEFAULT_COLOR    );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_WARNING_VALUE, STUMPLESS_SEVERITY_WARNING_DEFAULT_COLOR);
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_NOTICE_VALUE , STUMPLESS_SEVERITY_NOTICE_DEFAULT_COLOR );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_INFO_VALUE   , STUMPLESS_SEVERITY_INFO_DEFAULT_COLOR   );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_DEBUG_VALUE  , STUMPLESS_SEVERITY_DEBUG_DEFAULT_COLOR  );

  return target;
}

struct stumpless_target *
stumpless_open_stdout_target( const char *name ) {
  struct stumpless_target *target = stumpless_open_stream_target( name, stdout );

  if (target == NULL) return NULL;

  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_EMERG_VALUE  , STUMPLESS_SEVERITY_EMERG_DEFAULT_COLOR  );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_ALERT_VALUE  , STUMPLESS_SEVERITY_ALERT_DEFAULT_COLOR  );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_CRIT_VALUE   , STUMPLESS_SEVERITY_CRIT_DEFAULT_COLOR   );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_ERR_VALUE    , STUMPLESS_SEVERITY_ERR_DEFAULT_COLOR    );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_WARNING_VALUE, STUMPLESS_SEVERITY_WARNING_DEFAULT_COLOR);
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_NOTICE_VALUE , STUMPLESS_SEVERITY_NOTICE_DEFAULT_COLOR );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_INFO_VALUE   , STUMPLESS_SEVERITY_INFO_DEFAULT_COLOR   );
  stumpless_set_severity_color(target, STUMPLESS_SEVERITY_DEBUG_VALUE  , STUMPLESS_SEVERITY_DEBUG_DEFAULT_COLOR  );


  return target;
}

struct stumpless_target *
stumpless_open_stream_target( const char *name, FILE *stream ) {
  struct stumpless_target *target;

  clear_error(  );

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( stream );

  target = new_target( STUMPLESS_STREAM_TARGET, name );

  if( !target ) {
    goto fail;
  }

  target->id = new_stream_target( stream );
  if( !target->id ) {
    goto fail_id;
  }

  for (unsigned short i = 0; i < 8; i++)
    ((struct stream_target *)(target->id))->escape_codes[i][0] = 0;

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

void
stumpless_set_severity_color( struct stumpless_target *target, enum stumpless_severity severity, const char *escape_code )
{
  if (severity_is_invalid(severity)) {
    raise_invalid_severity(severity);
    return;
  }

  lock_target(target);
  if (target->type != STUMPLESS_STREAM_TARGET) {
    raise_target_unsupported(
      L10N_SEVERITY_COLORS_UNSUPPORTED_TARGET_ERROR_MESSAGE );
    return;
  }

  struct stream_target *starget = (struct stream_target *)target->id;

  strncpy(starget->escape_codes[severity], escape_code, 32);
  starget->escape_codes[severity][31] = 0;

  unlock_target(target);
  clear_error();
}


/* private definitions */

void
destroy_stream_target( const struct stream_target *target ) {
  config_destroy_mutex( &target->stream_mutex );
  free_mem( target );
}

struct stream_target *
new_stream_target( FILE *stream ) {
  struct stream_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  config_init_mutex( &target->stream_mutex );
  target->stream = stream;

  return target;
}

int
sendto_stream_target( struct stream_target *target,
                      const char *msg,
                      size_t msg_length,
                      const struct stumpless_entry *entry ) {
  size_t fwrite_result;
  enum stumpless_severity severity = stumpless_get_entry_severity(entry);
  const char *sev_code = target->escape_codes[severity];
  unsigned short sev_code_len = strlen(sev_code);
  const char *reset_code = "\33[0m";
  unsigned short reset_code_len = strlen(reset_code);
  
  config_lock_mutex( &target->stream_mutex );
  if (sev_code_len != 0)
  {
    fwrite_result = fwrite( sev_code, sizeof( char ), sev_code_len, target->stream );

    if( fwrite_result != sev_code_len ) {
      goto write_failure;
    }
  }

  fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  if (sev_code_len != 0)
  {
    fwrite_result = fwrite( reset_code, sizeof( char ), reset_code_len, target->stream );

    if( fwrite_result != reset_code_len ) {
      goto write_failure;
    }
  }

  config_unlock_mutex( &target->stream_mutex );
  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  config_unlock_mutex( &target->stream_mutex );
  raise_stream_write_failure(  );
  return -1;
}
