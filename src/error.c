/*
 * Copyright 2017, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
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

void clear_error(){
  error_valid = 0;
}

void raise_memory_allocation_failure(){
  if( !last_error ){
    last_error = malloc(sizeof(struct stumpless_error));
    if( !last_error ){
      error_valid = 0;
      return;
    }
  }
  
  last_error->id = MEMORY_ALLOCATION_FAILURE;
  error_valid = 1;
}