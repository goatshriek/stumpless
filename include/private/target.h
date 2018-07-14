/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_TARGET_H
#  define __STUMPLESS_PRIVATE_TARGET_H

void *
get_priv_target( stumpless_id_t id );

stumpless_id_t
register_priv_target( void *target );

void
unregister_priv_target( stumpless_id_t id );

int
target_unsupported( const struct stumpless_target *target,
                    const char *msg );

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
