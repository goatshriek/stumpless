# Socket Targets

Socket targets can send logs to a process that is listening on a Unix domain
socket. It is up to the remote end to do something with the log once it has been
received. The most common use case for this is to send logs to /dev/log on which
the system logging daemon is listening.

Opening a target is straightforward, with the first argument being the name of
the target as well as the socket to send logs to. You can ignore the second
argument in most cases.

```c
target = stumpless_open_socket_target( "/dev/log", NULL );
```

This will create a local socket with a randomized name that sends logs to the
specified socket. If you need to be more specific and choose the name of the
local socket that is created, then you can use the second argument to the open
function to do this.

```c
target = stumpless_open_socket_target( "/dev/log", "my-local-socket" );
```

Once the target is created, logs are sent to it as usual:

```c
stumpless_add_entry( target, entry );
```

And of course, closing is just as typical. The local socket will be cleaned up
when the target is closed.

```c
stumpless_close_socket_target( target );
```

And, even less typing at the cost of performance:

```c
stumpless_close_target( target );
```
