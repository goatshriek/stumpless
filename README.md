# Stumpless

[![Travis Build Status](https://travis-ci.org/goatshriek/stumpless.svg?branch=master)](https://travis-ci.org/goatshriek/stumpless)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/uwied5cn5jujl4d2/branch/master?svg=true)](https://ci.appveyor.com/project/goatshriek/stumpless)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/master/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

A logging library built with a [vision](docs/vision.md): a rich and intuitive
interface, standards compliance, fast performance, and a small footprint.

Currently stumpless offers [standardized](https://tools.ietf.org/html/rfc5424)
logging to the following targets:
 * network servers ([UDP](https://tools.ietf.org/html/rfc5426) or
   [TCP](https://tools.ietf.org/html/rfc6587) over IPv4 or IPv6)
 * files
 * streams
 * Linux sockets
 * the Windows Event Log
 * character buffers

## Basic Usage
If you want to start off slow, then you can use the `stumplog` function as a
direct replacement for the syslog function:

    syslog( LOG_INFO | LOG_USER, "My message" );
    // can be directly replaced with:
    stumplog( LOG_INFO | LOG_USER, "My message" );

If you haven't opened a target, this will log messages to the default target for
the platform: on a Linux this is `/dev/log`, on a Mac system this will be
`/var/run/syslog`, and on a Windows machine it is the Windows Event Log. If you
open a target or a few before calling `stumplog`, then logs will be sent to the
most recently opened target.

If you want to open your own target, then you simply open the target that you
want and start sending messages. For example, to log to a file:

    target = stumpless_open_file_target( "example.log",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    // uses the last opened target by default
    stumpless( "Login attempt failure #%d for user %s", count, username );

Sending messages over the network to something like Splunk or rsyslog is just
as easy:

    target = stumpless_open_udp4_target( "send-to-splunk-example",
                                         "mylogserver.com", // or use an IP
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    stumpless( "Login attempt failure #%d for user %s", count, username );

If you have multiple targets, you can send messages to a chosen target:

    stumpless_add_message( target,
                           "Login attempt failure #%d for user %s",
                           count,
                           username );

It's as easy as that! For more detailed examples of different targets and more
complicated message structures, check out the [examples](docs/examples).

## Documentation
If you're curious about how something in stumpless works, you can check the
appropriate section of the documentation, stored in the `docs` folder. You can
also look in the `docs/examples` folder for in-depth walkthroughs and annotated
example code for using various features of the library.

## scripts
The `scripts` directory contains single-file tools useful for the development
of the project, such as file formatting scripts and header inclusion checks.

## tools
The `tools` directory contains files to support third-party tools used by
stumpless, such as cmake.
