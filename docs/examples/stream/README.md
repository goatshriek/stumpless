# Stream Targets

Stream targets provide a simple way to send logs to any stream. This differs
from file targets in that it allows the user of the library to open the stream
and use it afterwards, or use a stream that has already been opened by another
portion of code. Stream targets can also be used for logging to standard streams
stdout and stderr, and there are even helper functions to create these targets.

If you already have a `FILE` pointer, then you can open a stream target using it
with the `stumpless_open_stream_target` function call, like this:

    my_file = fopen( "myfile.log", "w+" );
    myfile_target = stumpless_open_stream_target( "myfile", my_file, 0, STUMPLESS_FACILITY_USER );

Note that the file will need to be opened in write or append mode. If it is not,
then any attempts to send entries to it will fail with a write error.

If you would like to simply log to the stdout or stderr streams, there are
convenience functions that allow you to open these targets:

    // equivalent to stumpless_open_stream_target( "normal-stuff", stdout, 0, ...
    console_target = stumpless_open_stdout_target( "normal-stuff", 0, STUMPLESS_FACILITY_USER );
    // equivalent to stumpless_open_stream_target( "bad-stuff", stderr, 0, ...
    error_target = stumpless_open_stderr_target( "bad-stuff", 0, STUMPLESS_FACILITY_USER );

Logging to a stream target is the same as any other target:

    stumpless_add_entry( myfile_target, entry );

Stream targets are closed with the `stumpless_close_stream_target` function. It
is important to note that this does NOT close the stream itself, only the target
that logs to it. The stream must be closed separately by the caller, like this:

    stumpless_close_stream_target( myfile_target );
    fclose( myfile );
