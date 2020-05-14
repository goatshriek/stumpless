---
layout: default
---

# Stumpless at a glance

Stumpless is a logging library built with a [vision](./vision.html): a rich and
intuitive interface, standards compliance, fast performance, and a small
footprint.

Currently stumpless offers [standardized](https://tools.ietf.org/html/rfc5424)
logging to the following targets:
 * network servers ([UDP](https://tools.ietf.org/html/rfc5426) or
   [TCP](https://tools.ietf.org/html/rfc6587) over IPv4 or IPv6)
 * files
 * streams
 * Linux sockets
 * the Windows Event Log
 * character buffers


# More info

If you're just looking to start out, then take a look at some of the examples
below. There is source code for each of these in the `docs/examples` folder of
the repository if you want to actually compile and run them.

 * [Basic Usage](./examples/basic.html)
 * [Working with Entries](./examples/entry.html)
 * [File Targets](./examples/file.html)
 * [Network Targets](./examples/network.html)
 * [Unix Socket Targets](./examples/socket.html)
 * [Stream Targets](./examples/stream.html)
 * [Windows Event Log Targets](./examples/wel.html)

Detailed documentation of each function is included in the header files, and is
written using standard Doxygen syntax. You can generate the documentation
yourself with the `docs` build target, or you can look at one of the online
lists below:

[C Doxygen Documentation](./docs/c/latest)
[CPP Doxygen Documentation](./docs/cpp/latest)
