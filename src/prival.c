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

#include <stddef.h>
#include <string.h>
#include <stumpless/prival.h>
#include <stumpless/severity.h>
#include <stumpless/facility.h>
#include "private/prival.h"
#include "private/severity.h"
#include "private/facility.h"
#include "private/prival.h"
#include "private/strhelper.h"
#include "private/memory.h"
#include "private/validate.h"

static char stumpless_get_prival_string( int prival ) {
	VALIDATE_ARG_NOT_NULL( prival );
	
	const char *severity = stumpless_get_severity_string( get_severity( prival ) );
	const char *facility = stumpless_get_facility_string( get_facility( prival ) );
	
	size_t prival_string_length = ( strlen( severity ) + strlen( facility ) + 3); //+3 for formatting
	const char *prival_string = alloc_mem( prival_string_length );
	
	snprintf(prival_string, prival_string_length + 3, "%s | %s", severity, facility);
	
	return prival_string;
}

static char *severity_enum_to_string[] = {
  STUMPLESS_FOREACH_SEVERITY( GENERATE_STRING )
};
