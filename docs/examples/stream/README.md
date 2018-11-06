# Stream Targets

Stream targets provide a simple way to send logs to any stream. This differs
from file targets in that it allows the user of the library to open the stream
and use it afterwards, or use a stream that has already been opened by another
portion of code. Stream targets can also be used for logging to standard streams
stdout and stderr, and there are even helper functions to create these targets.
