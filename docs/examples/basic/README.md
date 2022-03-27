# Basic Usage

Stumpless is designed to make basic usage as easy as possible, while still
allowing use of more complex features. The most basic usage is the `stump`
function, which simply takes a format string and any optional substitutions
and sends these to the last opened target. This means that you can start
logging to a file with just two calls:

```c
file_target = stumpless_open_file_target( "example.log" );
stump( "The hello world of stumpless." );
```

Using a format specifier to include extra information:

```c
stump( "Login failed for username %s", "example-username" );
```

If you don't need format specifiers, then you should use the `_str` version
of the logging function you need. These are available for any function that
supports a format specifier string and variable arguments, and simply take a
raw string instead. This is both faster and safer, as you no longer need to
worry about escaping format specifiers, a common cause of bugs and
[vulnerabilities](https://owasp.org/www-community/attacks/Format_string_attack).

```c
// this can cause a (perhaps unexpected) problem
stump( "Detected the use of %s to print a string!" );

// much safer!
stump_str( "Detected the use of %s to print a string!" );
```

Try to use the `_str` functions whenever you can. If you need to include
information in your log message, consider using
[structured data](../entry/README.md) to do this instead of format specifiers.
This will improve the security and performance of your logging code, and likely
improve the indexing/searchability of your logs as well.

If you need to have multiple targets open you can get the same functionality
from the `stumpless_add_message` function:

```c
net_target = stumpless_open_udp4_target( "network-target", "example.com" );
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
