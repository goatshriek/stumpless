# Performance Testing

Performance testing of the library consists of throughput testing.

## `throughput.c`

Sends several basic messages directly to the daemon service. Records the time
required for both the stumpless library and the standard library syslog function
and outputs these to a results file in CSV format.