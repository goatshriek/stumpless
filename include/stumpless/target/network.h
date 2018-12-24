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

/** @file
 * Functions for working with network targets.
 */

#ifndef __STUMPLESS_TARGET_NETWORK_H
#  define __STUMPLESS_TARGET_NETWORK_H

#  include <stumpless/target.h>

/**
 * The default message size for UDP network targets. This is set to account for
 * an MTU of 1500 byes, a 20 byte IP header, and an 8 byte datagram header. If
 * you wish to change this value for a particular target, then you must use the
 * stumpless_set_udp_max_message_size function on the target.
 */
#define STUMPLESS_DEFAULT_UDP_MAX_MESSAGE_SIZE 1472

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Network protocols used by a network target.
 */
enum stumpless_network_protocol {
  STUMPLESS_IPV4_NETWORK_PROTOCOL /**< Internet Protocol version 4, RFC 791 */
};

/**
 * Transport protocols used by a network target.
 */
enum stumpless_transport_protocol {
  STUMPLESS_TCP_TRANSPORT_PROTOCOL, /**< TCP, RFC 793 */
  STUMPLESS_UDP_TRANSPORT_PROTOCOL  /**< UDP, RFC 768 */
};

/**
 * Closes a network target.
 *
 * This function does NOT close the stream associated with the target. It does
 * destroy all memory allocated for the target, including the target struct
 * itself.
 *
 * @param target The stream target to close.
 */
void
stumpless_close_network_target( struct stumpless_target *target );

/**
 * Gets the destination of a network target.
 *
 * @param target The target to get the destination from.
 *
 * @return The current destination of the network target. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
const char *
stumpless_get_destination( const struct stumpless_target *target );

/**
 * Gets the transport port number of a network target.
 *
 * @param target The target to get the port number from.
 *
 * @return The current port number of the network target, encoded as a string.
 * In the event of an error, NULL is returned and an error code is set
 * appropriately.
 */
const char *
stumpless_get_transport_port( const struct stumpless_target *target );

/**
 * Gets the current maximum message size of a UDP network target.
 *
 * @param target The target to be get the message size from.
 *
 * @return The current maximum message size of the supplied target if no error
 * is encountered. In the event of an error, 0 is returned and an error code is
 * set appropriately.
 */
size_t
stumpless_get_udp_max_message_size( struct stumpless_target *target );

/**
 * Creates a network target, but does not open it.
 *
 * A network target can be created with this function if the target needs to be
 * created without initiating a network session. This also allows parameters
 * that are not available in the open function to be set before initiating the
 * session, instead of restarting the session on each change.
 *
 * The target will stay in a paused state until it is opened using the
 * stumpless_open_target function.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param network The network protocol to use.
 *
 * @param transport The transport protocol to use.
 *
 * @return The new target if no error is encountered. In the event of an error,
 * NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_new_network_target( const char *name,
                              enum stumpless_network_protocol network,
                              enum stumpless_transport_protocol transport );

/**
 * Opens a network target.
 *
 * Network targets allow traditional syslog messages to be sent to a remote
 * server. This function allows the type of network target to be specified by
 * parameters, but if you know that you want a specific type then it is easier
 * to use the simplified functions that specify the type by name, such as the
 * stumpless_open_udp4_target function.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param destination The destination to send the messages to. This could be a
 * hostname or an IP address.
 *
 * @param network The network protocol to use.
 *
 * @param transport The transport protocol to use.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them. This should be a \c STUMPLESS_FACILITY value.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_network_target( const char *name,
                               const char *destination,
                               enum stumpless_network_protocol network,
                               enum stumpless_transport_protocol transport,
                               int options,
                               int default_facility );

/**
 * Opens a network target for remote logging over IPv4 and TCP.
 *
 * A TCP4 target will use Syslog over TCP, as defined in RFC 6587.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param destination The destination to send the messages to. This could be a
 * hostname or an IP address.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them. This should be a \c STUMPLESS_FACILITY value.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_tcp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility );

/**
 * Opens a network target for remote logging over IPv4 and UDP.
 *
 * A UDP4 target will use Syslog over UDP, as defined in RFC 5426.
 *
 * @param name The name of the target to open. This is only used for
 * identification of the target.
 *
 * @param destination The destination to send the messages to. This could be a
 * hostname or an IP address.
 *
 * @param options The options to use for the logging target. This is a bit-wise
 * or of one or more \c STUMPLESS_OPTION values.
 *
 * @param default_facility The facility code to use for entries that do not have
 * a facility value set on them. This should be a \c STUMPLESS_FACILITY value.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_open_udp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility );

/**
 * Sets the destination of a network target.
 *
 * @param target The target to be modified.
 *
 * @param destination The new destintion to send messages to. This could be a
 * hostname or an IP address.,
 *
 * @return The modified target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_set_destination( struct stumpless_target *target,
                           const char *destination );

/**
 * Sets the transport port number of a network target.
 *
 * @param target The target to be modified.
 *
 * @param port The new transport port number to use. This is an ASCII string,
 * and will be copied by the function. After the call returns, the parameter
 * will not be referenced again and can be destroyed as needed.
 *
 * @return The modified target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_set_transport_port( struct stumpless_target *target,
                              const char *port );

/**
 * Sets the maximum message size of a UDP network target.
 *
 * Messages that are longer than the maximum size are truncated to this length.
 * If the underlying transport for a network target can support a larger
 * datagram and you need support for longer messages, then you can use this
 * option to increase the size. Likewise, the option can be used to force
 * smaller datagrams if needed, for example in the case of extra overhead in the
 * IP header beyond the typical 20 bytes.
 *
 * Without calling this function, UDP targets start with a maximum message size
 * set to \c STUMPLESS_DEFAULT_UDP_MAX_MESSAGE_SIZE.
 *
 * @param target The target to be modified.
 *
 * @param max_msg_size The new maximum message size for the supplied target.
 *
 * @return The modified target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_set_udp_max_message_size( struct stumpless_target *target,
                                    size_t max_msg_size );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_NETWORK_H */
