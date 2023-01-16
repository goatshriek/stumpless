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

/** @file
 * Functionality to perform name resolution for a given host and connecting
 * to it, based on `gethostbyname` functions.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_GETHOSTBYNAME_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_GETHOSTBYNAME_SUPPORTED_H

/**
 * Resolves the provided hostname, and attempts to connect to the resulting
 * address on a newly-created socket.
 *
 * If gethostbyname2 is available, it will be used for the name resolution. If
 * not, then gethostbyname is used instead.
 *
 * If gethostbyname[2] cannot resolve the name, then inet_pton is tried. If both
 * of these fail to return an address, then this function returns -1 and raises
 * an error that the name could not be resolved.
 *
 * **Thread Safety: MT-Safe race:destination race:port env locale**
 * This function is thread safe, with some caveats. The destination and port
 * must not be changed during execution. gethostbyname and inet_pton also uses
 * env and locale variables, which may cause issues for some usages.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * static pointers returned by gethostbyname.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
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
gethostbyname_int_connect( const char *destination,
                           const char *port,
                           int domain,
                           int type,
                           int protocol );

#endif /* __STUMPLESS_PRIVATE_CONFIG_GETHOSTBYNAME_SUPPORTED_H */
