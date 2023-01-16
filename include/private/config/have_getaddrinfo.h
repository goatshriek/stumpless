/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2023 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_HAVE_GETADDRINFO_H
#  define __STUMPLESS_PRIVATE_CONFIG_HAVE_GETADDRINFO_H

/**
 * Resolves the provided hostname, and attempts to connect to the resulting
 * address on a newly-created socket.
 *
 * **Thread Safety: MT-Safe race:destination race:port env locale**
 * This function is thread safe, with some caveats. The destination and port
 * must not be changed during execution. getaddrinfo also uses env and locale
 * variables, which may cause issues for some usages.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as socket handles may not be cleaned up in this case.
 *
 * @since release v2.2.0
 *
 * @param destination The hostname or address to connect to.
 *
 * @param port The port to connect to on the given host.
 *
 * @param domain The socket domain to use for the connection.
 *
 * @param type The type of socket to create.
 *
 * @param protocol The protocol to use for the connection.
 *
 * @return The connected socket, or -1 if an error is encountered.
 */
int
getaddrinfo_int_connect( const char *destination,
                         const char *port,
                         int domain,
                         int type,
                         int protocol );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_GETADDRINFO_H */
