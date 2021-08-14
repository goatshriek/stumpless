// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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

#include <stumpless/config/journald_supported.h>
#include <stumpless/element.h>
#include <stumpless/param.h>
#include <stumpless/target/journald.h>
#include "private/config/journald_supported.h"
#include "private/element.h"
#include "private/param.h"
#include "private/validate.h"

stumpless_element_namer_func_t
stumpless_get_element_journald_namer( const struct stumpless_element *e ) {
  stumpless_element_namer_func_t result;

  VALIDATE_ARG_NOT_NULL( e );

  lock_element( e );
  result = e->get_journald_name;
  unlock_element( e );

  return result;
}

stumpless_param_namer_func_t
stumpless_get_param_journald_namer( const struct stumpless_param *param ) {
  stumpless_param_namer_func_t result;

  VALIDATE_ARG_NOT_NULL( param );

  lock_param( param );
  result = param->get_journald_name;
  unlock_param( param );

  return result;
}

struct stumpless_element *
stumpless_set_element_journald_namer( struct stumpless_element *element,
                                      stumpless_element_namer_func_t namer ) {
  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( namer );

  lock_element( element );
  element->get_journald_name = namer;
  unlock_element( element );

  return element;
}

struct stumpless_param *
stumpless_set_param_journald_namer( struct stumpless_param *param,
                                    stumpless_param_namer_func_t namer ) {
  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( namer );

  lock_param( param );
  param->get_journald_name = namer;
  unlock_param( param );

  return param;
}

/* private definitions */

void
journald_init_journald_element( struct stumpless_element *element ) {
  element->get_journald_name = stumpless_flatten_element_name;
}

void
journald_init_journald_param( struct stumpless_param *param ) {
  param->get_journald_name = stumpless_flatten_param_name;
}
