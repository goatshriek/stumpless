# Network Targets

Network targets allow logs to be sent over a network to some remote log collector or relay. There are a number of popular options for the remote end including Splunk, rsyslog, and syslog-ng. Stumpless can send messages to these and others, provided they adhere to some basic standards or common practices.

You'll need to decide what network and transport protocols that you want to use. There are enums for the supported options, though IPv4 and IPv6 are the most likely network protocols, and UDP and TCP are the most likely transport ones. The code below opens up a simple target to a UDP target over IPv4:

    new_target = stumpless_open_network_target( "new-udp4-target",
                                                STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                                STUMPLESS_UDP_TRANSPORT_PROTOCOL );
