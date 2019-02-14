# Network Targets

Network targets allow logs to be sent over a network to a remote log collector
or relay. There are a number of popular options for the remote end including
Splunk, rsyslog, and syslog-ng. Stumpless can send messages to these and others,
provided they adhere to some basic standards or at least common practices.

You'll need to decide what network and transport protocols that you want to use.
There are enums listing all supported options, but IPv4 and IPv6 are the most
common network protocols, and UDP and TCP the most common transport ones. The
code below opens up a simple target to a UDP collector over IPv4:

    new_target = stumpless_open_network_target( "new-udp4-target",
                                                "example.com",
                                                STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                                STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                                STUMPLESS_OPTION_NONE,
                                                STUMPLESS_FACILITY_USER );

If you want to be a little more concise, then you can use the open function for
the network and transport protocol you've chosen. This is the approach that the
UDP example uses.

    new_target = stumpless_open_udp4_target( "new-udp4-target",
                                             "example.com",
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );

Both of these functions create a target pointing to the `example.com` server.
UDP targets don't necessarily need a response to be opened due to the nature of
the UDP, but TCP targets do. If you try to open a TCP target to a destination
that isn't responding, it will fail.

    new_target= stumpless_open_tcp4_target( "new-tcp4-target",
                                            "example.com",
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    if( !new_target ) {
      stumpless_perror( "dangit" ); // "getaddrinfo failed on name" might mean a DNS failure
                                    // "connect failed with socket" might mean no TCP response
    }

If for some reason you want to open a target to a server that isn't responding
just yet, then you can use the builder style of target creation instead of
directly opening it. This will create a target with the given parameters, but
won't try to open it right away. This allows you to create the target, set any
necessary options, and then attempt to open it when the time is right. The TCP
example uses this approach.

    new_target = stumpless_new_network_target( "new-tcp4-target",
                                               STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                               STUMPLESS_TCP_TRANSPORT_PROTOCOL );
    stumpless_target_is_open( new_target ); // will return false
    stumpless_set_destination( new_target, "example.com" );
    stumpless_set_transport_port( new_target, "6514" );
    stumpless_open_target( new_target );
    stumpless_target_is_open( new_target ); // will return true, assuming success

And of course if you want to be more concise, there is a matching new function
just like for the open functions:

    new_target = stumpless_new_tcp4_target( "new-tcp4-target" );

The options of a network target can be set at any time, but it's important to
know that some of them may re-open the target. For example, setting the maximum
message size of a UDP target will be transparent to the network connection:

    stumpless_set_udp_max_message_size( my_target, 1400 ); // this will have no effect on the session

However, setting the destination will reset the connection, which could fail if
the new target isn't listening. You can detect this by looking at the return
value, the error code, or checking to see if the target is open.

    stumpless_set_destination( my_target, "example2.com" );
    stumpless_target_is_open( my_target ); // will be true if the new destination responds

As a general rule, targets that are open when such an option is set will be
re-opened if possible. If the target is not open (a state referred to as paused
in the documentation), then it will be left as is until an explicit call to
`stumpless_target_open` is made.

Targets opened throuth both the open and new families of functions are closed
using the standard close function:

    stumpless_close_network_target( my_target );
