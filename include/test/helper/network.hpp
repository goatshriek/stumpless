/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_TEST_HELPER_NETWORK_HPP
#  define __STUMPLESS_TEST_HELPER_NETWORK_HPP

#  include <stumpless.h>
#  include "test/helper/server.hpp"

void
TestSetDestinationOnOpenTarget( struct stumpless_target *target,
                                const char *original_destination,
                                const char *new_destination,
                                socket_handle_t new_dest_server );

void
TestSetDestinationOnPausedTarget( struct stumpless_target *target,
                                  const char *new_destination,
                                  socket_handle_t new_dest_server );

void
TestSetTransportPortOnOpenTarget( struct stumpless_target *target,
                                  const char *new_port,
                                  socket_handle_t new_port_server );

void
TestSetTransportPortOnPausedTarget( struct stumpless_target *target,
                                    const char *destination,
                                    const char *new_port,
                                    socket_handle_t new_port_server );

void TestTruncatedMessage( struct stumpless_target *target );

#endif /* __STUMPLESS_TEST_HELPER_NETWORK_HPP */
