![Stumpless logo](./assets/logo-and-name.svg)

**A C logging library built for high performance and a rich feature set.**

[![Linux Builds](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml)
[![Windows Builds](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml)
[![Mac Builds](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/latest/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![Gitter](https://badges.gitter.im/stumpless/community.svg)](https://gitter.im/stumpless/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.1-ff69b4.svg)](https://github.com/goatshriek/stumpless/blob/latest/docs/CODE_OF_CONDUCT.md)


[한국어](./l10n/ko-kr/README.md) | [简体中文](./l10n/zh-cn/自述.md)


[Key Features](#key-features) |
[Build and Install](#quick-build-and-install) |
[Basic Usage](#basic-usage) |
[Contributing](#contributing)


## Key Features
Stumpless has lots of features that make logging in C fast and easy:
 * log to [lots of things](#what-can-it-log-to) like Splunk, rsyslog,
   journald, the Windows Event Log, sqlite, and more!
 * structured and unstructured logging to suit your needs
 * builds on Linux, Windows, Mac, FreeBSD, MinGW, MSYS2, Cygwin, DOS, and more!
 * thread safe
 * can be adjusted or removed during compilation for zero runtime cost
 * localized for multiple languages 🇦🇱 🇧🇷 🇧🇬 🇨🇳 🇨🇿 🇩🇪 🇩🇰 🇪🇸 🇫🇷 🇬🇷 🇭🇺 🇮🇳 🇮🇱 🇮🇹
   🇯🇵 🇰🇪 🇰🇷 🇵🇱 🇸🇰 🇱🇰 🇸🇪 🇹🇷 🇺🇸
   ([add yours!](https://github.com/goatshriek/stumpless/blob/latest/docs/localization.md))
 * easy-access
   [documentation](https://goatshriek.github.io/stumpless/docs/c/latest/),
   [examples](https://github.com/goatshriek/stumpless/tree/latest/docs/examples),
   and [support](https://gitter.im/stumpless/community).


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
with your request and we'll work it into our
[roadmap](https://github.com/goatshriek/stumpless/blob/latest/docs/roadmap.md)!


## Quick Build and Install
Stumpless only requires cmake and a cmake-supported build toolchain (like GCC
or Visual Studio) to build.

```sh
# cloning the latest version of the source tree
git clone git@github.com:goatshriek/stumpless.git

# creating a new build directory
mkdir build
cd build

# configuring the new build
cmake ../stumpless

# building stumpless (with 4 threads - adjust as desired)
cmake --build . --parallel 4

# install the library (you probably need sudo to do this)
sudo cmake --install .
```

Check out the [Installation Instructions](INSTALL.md) for more detail on
building and installing stumpless in different environments and/or with other
toolchains.


## Basic Usage
The simplest way to get started is to use the `stumplog` function as a direct
replacement for the standard library's `syslog` function:

```c
// if you're used to doing this:
syslog( LOG_INFO | LOG_USER, "My message #%d", count );

// then you can start by changing to this:
stumplog( LOG_INFO | LOG_USER, "My message #%d", count );
```

If you haven't opened a target, this will log messages to the default target for
the platform: on Linux this is `/dev/log`, on a Mac system this will be
`/var/run/syslog`, and on a Windows machine it is the Windows Event Log. If you
open a target or even a few before calling `stumplog`, then logs will be sent to
the most recently opened target.

If you want an even shorter function call, you can use the `stump` function
to send a message to the current target. You can also use format specifiers just
as you would with `printf`:

```c
stump( "Login attempt failure #%d for user %s", count, username );
```

If you don't need format specifiers, use one of the `_str` variants:
it's both faster and safer!

```c
stump_str( "Login failure! See structured data for info." );
```

If you want to open a specific target rather than using the default, then just
open the one you need and start sending messages. For example, to log to
a file named `example.log`:

```c
target = stumpless_open_file_target( "example.log" );

// uses the last opened target by default
stump( "Login attempt failure #%d for user %s", count, username );
```

Sending messages over the network to something like Splunk or rsyslog is just
as easy:

```c
target = stumpless_open_udp4_target( "send-to-splunk-example",
                                     "mylogserver.com" ); // or use an IP
stump( "Login attempt failure #%d for user %s", count, username );
```

If you have multiple targets, you can send messages to a chosen target like
this:

```c
stumpless_add_message( target,
                       "Login attempt failure #%d for user %s",
                       count,
                       username );
```


### Severity Shorthand
It's common to specify severity levels directly in logging calls, so stumpless
provides some macro functions to make this less verbose and more efficient. For
example, to log messages with a severity of INFO, you can do this:

```c
stump_i( "this gets logged as an info message" );
```

And if you want to also see source file, line number, and function name info in
each message you can use `_t` (the 't' is for trace):

```c
stump_t( "this includes source info" );
```

Using these functions has the added benefit that they can be removed at
compile time by simply defining the `STUMPLESS_ENABLE_UPTO` or
`STUMPLESS_DISABLE_DOWNTO` symbols. This makes it easy to change logging levels
between builds, for example to have prod and debug versions without differences
in their source code.

```c
// be sure to define this before stumpless.h gets included
#define STUMPLESS_ENABLE_UPTO_INFO

// ...

// this log will go through just fine
stump_i( "I'm doing that thing you asked" );

// this debugging message is completely removed: no runtime impact whatsoever
stump_d( "DEBUG info: %d, %d, %s", thing_1, thing_2, stringy_thingy );
```

Check out the headers in
[stumpless/level](https://github.com/goatshriek/stumpless/tree/latest/include/stumpless/level)
to see the full list of severity shorthand functions, or the
[severity level example](https://github.com/goatshriek/stumpless/tree/latest/docs/examples/severity_level)
to see a complete program in action.


### Even more examples
For more detailed examples of the above scenarios, usage of specific target
types, how to handle more complicated message structures, and more check out the
[examples](docs/examples). These include annoted example code files to compile,
run, and modify to get you started.


## Contributing
Notice a problem or have a feature request? Just create an issue using one of
the templates, and we will respond as quickly as we can. You can also look at
the project's [Contribution Guidelines](docs/CONTRIBUTING.md) for more details
on the different ways you can give back to the open source community!

If you want to actually write some code or make an update yourself, take a look
at the [development guide](docs/development.md) to get a detailed orientation.
There are a few options based on your level of experience and familiarity with
making contributions.

The first option is to browse the list of issues that are marked with the label
[good first issue](https://github.com/goatshriek/stumpless/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22).
These issues are selected to be a small but meaningful amount of work, and
include details on the general approach that you can take to complete them. They
are a great place to start if you are just looking to test the waters of this
project or open source contribution in general.

More experienced developers may prefer to look at the full list of issues on the
project, as well as the
[roadmap](https://github.com/goatshriek/stumpless/blob/latest/docs/roadmap.md).
If an item catches your interest, drop a comment in the existing issue or open
a new one if it doesn't exist yet and state your intent to work on it so that
others will have a way to know it is underway.


## Documentation and Community
If you're curious about how something in stumpless works that isn't explained
here, you can check the appropriate section of the documentation, stored in the
[docs](https://github.com/goatshriek/stumpless/blob/latest/docs/) folder.
Folders in the repository contain their own README files that detail what they
contain and any other relevant information. The documentation for each function
is also hosted on the
[project website](https://goatshriek.github.io/stumpless/), for both the C
library as well as the other language bindings like C++.

Stumpless also includes documentation in local installations in the form of
`man` pages. Once you've installed the library, you can check the documentation
for any header file (and the functions it contains) by running man with the
name of the header with directories replaced with underscores, for example
`man stumpless_log.h` to see documentation for functions that log simple string
messages.

There are also plenty of ways that you can reach out to the project team and
broader community for support.
 * [Issues](https://github.com/goatshriek/stumpless/issues) and
   [discussions](https://github.com/goatshriek/stumpless/discussions) on Github
   are good ways to get a response if you have a specific question or
   suggestion.
 * There is a persistent chat on [gitter](https://gitter.im/stumpless/community)
   where you can find announcements and ask questions.
 * News about the project are typically announced on Twitter as well by
   [goatshriek](https://twitter.com/goatshriek), using
   [#StumplessLib](https://twitter.com/search?q=%23StumplessLib).
 * You can reach the primary maintainer via [email](mailto:joel@goatshriek.com)
   if you want private communication. This is the preferred method for
   [notifying](https://github.com/goatshriek/stumpless/blob/latest/docs/SECURITY.md#reporting-a-vulnerability)
   us of security issues with the project, so that we can address them as
   quickly as possible to reduce the risk of abuse.
