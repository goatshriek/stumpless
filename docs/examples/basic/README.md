# Basic Usage

Stumpless is designed to make very basic usage as easy as possible, while still
allowing more complex usage to be added later. The most basic usage is the
`stumpless` function, which simply takes a format string and any optional
substitutions and sends these to the last opened target. This means that you
can start logging to a file with just two calls:

```c
file_target = stumpless_open_file_target( "example.log",
                                          STUMPLESS_OPTION_NONE,
                                          STUMPLESS_FACILITY_USER );
stumpless( "The hello world of stumpless." );
```

Using a format specifier to include extra information:

```c
stumpless( "Login failed for username %s", "example-username" );
```

If you need to have multiple targets open you can get the same functionality
from the `stumpless_add_message` function:

```c
net_target = stumpless_open_udp4_target( "network-target",
                                         "example.com",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
stumpless_add_message( net_target,
                       "Login failed for username %s",
                       "example-username" );
```

If you're currently using the standard library `syslog` function, then you can
ease your transition by using `stumplog` function, which has an identical
signature and the same principles of operation:

```c
syslog( LOG_INFO | LOG_USER, "Failed login for %s", username );

// the above can be directly replaced with:
stumplog( LOG_INFO | LOG_USER, "Failed login for %s", username );
```

Note that the standard library symbols `LOG_INFO` and `LOG_USER` still work. You
can freely interchange these and the `STUMPLESS_SEVERITY_<level>` and
`STUMPLESS_FACILITY_<level>` symbols. The `STUMPLESS_*` symbols are declared as
an alias of the standard library symbols when the `syslog.h` header is found on
the build system.

It's important to close the targets after you're finished with them to free up
resources they are using.

```c
stumpless_close_file_target( file_target );
stumpless_close_network_target( net_target );
```

If you really need to free all resources (such as caches that are created to
make some operations faster), then use the free all function. It is important
to make sure that you only do this _after_ you have closed all targets and
destroyed any other resources you've created through the library.

```c
stumpless_free_all(  );
```
