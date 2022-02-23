// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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
#include <stumpless/log.h>
#include <stumpless/target.h>
#include "private/target.h"

int
stump( const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump( message, subs );
  va_end( subs );

  return result;
}

int
stump_str( const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return stumpless_add_message( target, message );
}

int
stump_trace( const char *file,
             int line,
             const char *func,
             const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump_trace( file, line, func, message, subs );
  va_end( subs );

  return result;
}

int
stump_trace_str( const char *file,
                 int line,
                 const char *func,
                 const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return stumpless_trace_message_str( target, file, line, func, message );
}

void
stumplog( int priority, const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog( priority, message, subs );
  va_end( subs );
}

int
stumplog_set_mask( int mask ) {
  struct stumpless_target *target;
  int old_mask;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return 0;
  }

  lock_target( target );
  old_mask = target->mask;
  target->mask = mask;
  unlock_target( target );

  return old_mask;
}

void
stumplog_str( int priority, const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  stumpless_add_log_str( target, priority, message );
}

void
stumplog_trace( int priority,
                const char *file,
                int line,
                const char *func,
                const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog_trace( priority, file, line, func, message, subs );
  va_end( subs );
}

void
stumplog_trace_str( int priority,
                    const char *file,
                    int line,
                    const char *func,
                    const char *message ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  stumpless_trace_log_str( target, priority, file, line, func, message );
}

int
vstump( const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_add_message( target, message, subs );
}

int
vstump_trace( const char *file,
              int line,
              const char *func,
              const char *message,
              va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_trace_message( target, file, line, func, message, subs );
}

void
vstumplog( int priority, const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_add_log( target, priority, message, subs );
}

void
vstumplog_trace( int priority,
                 const char * file,
                 int line,
                 const char *func,
                 const char *message,
                 va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_trace_log( target, priority, file, line, func, message, subs );
}
