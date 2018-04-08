/*
 * Copyright 2018 Joel E. Anderson
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
#include <stdlib.h>
#include <stumpless/error.h>
#include "private/error.h"

static struct stumpless_error *last_error=NULL;
static short error_valid=0;

struct stumpless_error *stumpless_get_error(){
  if(error_valid)
    return last_error;
  else
    return NULL;
}

/* private functions */

void clear_error(){
  error_valid = 0;
}

void raise_argument_empty(){
  raise_error(STUMPLESS_ARGUMENT_EMPTY);
}

void raise_argument_too_big(){
  raise_error(STUMPLESS_ARGUMENT_TOO_BIG);
}

void raise_error(enum stumpless_error_id id){
  if( !last_error ){
    last_error = malloc(sizeof(struct stumpless_error));
    if( !last_error ){
      error_valid = 0;
      return;
    }
  }
  
  last_error->id = id;
  error_valid = 1;
}

void raise_memory_allocation_failure(){
  raise_error(STUMPLESS_MEMORY_ALLOCATION_FAILURE);
}
