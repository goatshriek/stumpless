---
title: Stumpless
description: "Homepage of the Stumpless logging library"
tags: "stumpless c logging library syslog journald sqlite"
layout: default
---

[简体中文](./zh-CN/index.html)


# Stumpless at a glance
Stumpless is a C logging library built for high performance and a rich feature
set.

Stumpless has lots of features that make logging in C fast and easy:
 * log to lots of things including Splunk, rsyslog, journald, the Windows
   Event Log, sqlite, and more!
 * structured and unstructured logging to suit your needs
 * builds on Linux, Windows, Mac, FreeBSD, MinGW, MSYS2, Cygwin, DOS, and more!
 * thread safe
 * can be adjusted or removed during compilation for zero runtime cost
 * localized for multiple languages &#127462;&#127473; &#127463;&#127479; &#127463;&#127468; &#127464;&#127475;
   &#127464;&#127487; &#127465;&#127466; &#127465;&#127472; &#127466;&#127480; &#127467;&#127479; &#127468;&#127479; &#127469;&#127482; &#127470;&#127475;
   &#127470;&#127473; &#127470;&#127481; &#127471;&#127477; &#127472;&#127466; &#127477;&#127473; &#127480;&#127472; &#127473;&#127472; &#127480;&#127466; &#127481;&#127479; &#127482;&#127480;
 * easy-access
   [documentation](https://goatshriek.github.io/stumpless/docs/c/latest/index.html),
   [examples](https://github.com/goatshriek/stumpless/tree/latest/docs/examples),
   and [support](https://gitter.im/stumpless/community).

Check out our [vision](./vision.html) to see our ultimate goal! To see where
we're heading in the near future, check out the project
[roadmap](./roadmap.html).


### What can it log to?
A primary goal of this library is to provide a consistent logging interface to
a wide variety of log targets. This means you can focus on defining events
and where you want them to go, without finding other SDKs or adding daemons
and plugins to get them where you want. Stumpless can write logs to:
 * Simple character buffers
 * Files and streams
 * Unix sockets (such as a local syslog daemon)
 * Network servers (IPv4 or IPv6, TCP or UDP)
 * Systemd Journald service
 * Sqlite3 databases
 * Windows Event Log
 * Custom functions, for whatever else you may need!

Don't see what you need? Create an
[issue](https://github.com/goatshriek/stumpless/issues/new?template=feature_request.md)
with your request and we'll work it into our plans!


# Examples and Documentation
If you're just looking to start out, then take a look at some of the examples
below. There is source code for each of these in the `docs/examples` folder of
the repository if you want to actually compile and run them.

 * [Basic Usage](./examples/basic.html)
 * [Using Severity Levels](./examples/severity_level.html)
 * [Working with Entries](./examples/entry.html)
 * [Filtering Logs](./examples/filter.html)
 * [Chain Targets](./examples/chain.html)
 * [File Targets](./examples/file.html)
 * [Journald Targets](./examples/journald.html)
 * [Network Targets](./examples/network.html)
 * [Unix Socket Targets](./examples/socket.html)
 * [Sqlite Targets](./examples/sqlite3.html)
 * [Stream Targets](./examples/stream.html)
 * [Windows Event Log Targets](./examples/wel.html)
 * [Custom Function Targets](./examples/function.html)
 * [C++ Bindings](./examples/cpp.html)

Detailed documentation of each function is included in the header files, and is
written using standard Doxygen syntax. You can generate the documentation
yourself with the `docs` build target, or you can look at one of the online
builds below:

 * [C Doxygen Documentation](./docs/c/latest/en-US/index.html)
 * [C++ Doxygen Documentation](./docs/cpp/latest/index.html)


# Source and Contributing
If you want to check out the source code and/or look into becoming a contributor
to stumpless, head over to the project's
[github repository](https://github.com/goatshriek/stumpless) to find out more!
