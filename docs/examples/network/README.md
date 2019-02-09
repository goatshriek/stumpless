# Network Targets

Network targets allow logs to be sent over a network to some remote log collector or relay. There are a number of popular options for the remote end including Splunk, rsyslog, and syslog-ng. Stumpless can send messages to these and others, provided they adhere to some basic standards or common practices.

You'll need to decide what network and transport protocols that you want to use. There are enums for the supported options, though IPv4 and IPv6 are the most likely network protocols, and UDP and TCP are the most likely transport ones. The code below opens up a simple target to a UDP target over IPv4:

    new_target = stumpless_open_network_target( "new-udp4-target",
                                                "example.com",
                                                STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                                STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                                STUMPLESS_OPTION_NONE,
                                                STUMPLESS_FACILITY_USER );

If you want to be a little more concise, then you can use the open function for the network and transport protocol you've chosen:

    new_target = stumpless_open_udp4_target( "new-udp4-target",
                                             "example.com",
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );

Both of these functions create a target pointing to the `example.com` server. UDP targets don't necessarily need a response to be opened due to the nature of the UDP, but TCP targets do. If you try to open a TCP target to a destination that isn't responding or isn't in DNS, for example, it will fail.

    new_target= stumpless_open_tcp4_target( "new-tcp4-target",
                                            "example.com",
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    if( !new_target ) {
      error = stumpless_get_error(  );
      printf( "%s\n", error->message ); // "getaddrinfo failed on name" might mean a DNS failure
                                        // "connect failed with socket" might mean no TCP response
    }

If for some reason you want to open a target that isn't responding just yet, then you can use the builder style of target creation instead of directly opening it.
