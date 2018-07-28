# File Targets

File targets send logs to a given file, a critical function for any logging
library. File targets offer a simple and straightforward mechanic for writing
logs, but note that you will still need a separate system for other functions
like rotating them, encrypting them, or shipping them to another location.

The name of the target that is created will also be used as the filename. This
should include any paths as well:

```c
file_target = stumpless_open_file_target( "path/to/myfile.log",
                                          STUMPLESS_OPTION_NONE,
                                          STUMPLESS_FACILITY_USER );
```

Of course logging to file targets is done as with any other:

```c
stumpless_add_entry( file_target, entry );
```

Targets are closed in the usual way:

```c
stumpless_close_file_target( file_target );
```

Or, using the generic (and slightly slower) function:

```c
stumpless_close_target( file_target );
```
