# Basic Usage

Stumpless is designed to make very basic usage as easy as possible, while still
allowing more complex usage to be added later. The most basic usage is the
`stumpless` function, which simply takes a format string and any optional
substitutions and sends these to the last opened target. This means that you
can start logging to a file with just two calls:

    file_target = stumpless_open_file_target( "example.log",
                                              STUMPLESS_OPTION_NONE,
                                              STUMPLESS_FACILITY_USER );
    stumpless( "The hello world of stumpless." );

Using a format specifier to include extra information:

    stumpless( "Login failed for username %s", "example-username" );

If you need to have multiple targets open you can get the same functionality
from the `stumpless_add_message` function:

    net_target = stumpless_open_udp4_target( "network-target",
                                             "example.com",
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );
    stumpless_add_message( net_target,
                           "Login failed for username %s",
                           "example-username" );

It's important to close the targets after you're finished with them to free up
resources they are using.

    stumpless_close_file_target( file_target );
    stumpless_close_network_target( net_target );

If you really need to free all resources (such as caches that are created to
make some operations faster), then use the free all function. It is important
to make sure that you only do this _after_ you have closed all targets and
destroyed any other resources you've created through the library.

    stumpless_free_all(  );
