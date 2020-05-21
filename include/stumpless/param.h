/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2020 Joel E. Anderson
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

/** @file
 * Types and functions for creating and modifying params.
 */

#ifndef __STUMPLESS_PARAM_H
#  define __STUMPLESS_PARAM_H

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * A parameter within a structured data element.
 *
 * A parameter must have both a name and a value in compliance with RFC 5424.
 */
struct stumpless_param {
/**
 * The name of the parameter.
 *
 * The name must be between 1 and 32 characters long and consist only of ASCII
 * characters between '!' and '~', inclusive, with the exception of the '=',
 * ' ', ']', and '"' characters, which are not allowed.
 *
 * Note that the name will _not_ be NULL-terminated.
 */
  char *name;
/** The number of characters in name. */
  size_t name_length;
/**
 * The value may be any UTF-8 string.
 *
 * As specified in RFC 5424, the characters '"' (ABNF %d34), '\' (ABNF %d92),
 * and ']' (ABNF %d93) MUST be escaped by placing a backslash character '\'
 * directly before them.
 *
 * Unlike the name field, value will be NULL-terminated. This is done to support
 * their use for wel insertion strings.
 */
  char *value;
/** The number of characters in value. */
  size_t value_length;
};

/**
 * Destroys a param, freeing any allocated memory.
 *
 * @param param The param to destroy.
 */
void
stumpless_destroy_param( struct stumpless_param *param );

const char *
stumpless_get_param_name( const struct stumpless_param *param );

const char *
stumpless_get_param_value( const struct stumpless_param *param );

/**
 * Creates a new param with the given name and value.
 *
 * @param name The name of the new param.
 *
 * @param value The value of the new param.
 *
 * @return The created param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code set appropriately.
 */
struct stumpless_param *
stumpless_new_param( const char *name, const char *value );

struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name );

struct stumpless_param *
stumpless_set_param_value( struct stumpless_param *param, const char *value );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif /* __STUMPLESS_PARAM_H */
