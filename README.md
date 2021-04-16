![Stumpless logo](assets/logo-and-name.png)

**A C logging library built for high performance and a rich feature set.**

[![Github Actions Build Status](https://github.com/goatshriek/stumpless/workflows/build/badge.svg)](https://github.com/goatshriek/stumpless/actions?query=workflow%3Abuild)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/latest/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![CodeQL](https://github.com/goatshriek/stumpless/workflows/CodeQL/badge.svg)](https://github.com/goatshriek/stumpless/security/code-scanning)
[![Gitter](https://badges.gitter.im/stumpless/community.svg)](https://gitter.im/stumpless/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.0-ff69b4.svg)](https://github.com/goatshriek/stumpless/blob/latest/docs/CODE_OF_CONDUCT.md)

[Key Features](#key-features) |
[Download and Build](#quick-build-and-install) |
[Basic Usage](#basic-usage) |
[Contributing](#contributing)


## Key Features
Stumpless offers a robust set of features to make logging in C faster and
easier:
 * cross-platform builds on Linux, Windows, Mac, Cygwin, and more
 * easy logging to network targets like Splunk or rsyslog servers
 * completely thread safe
 * can be adjusted or removed during compilation for zero runtime impact
 * interoperability with standard syslog daemons and library functions
 * a continuously-run extensive test suite to ensure proper functionality
 * localized for multiple languages :bulgaria: :de: :fr: :it: :sweden: :slovakia: :us:
   ([add yours!](https://github.com/goatshriek/stumpless/blob/latest/docs/localization.md))
 * easy-access
   [documentation](https://goatshriek.github.io/stumpless/docs/c/latest/index.html),
   [examples](https://github.com/goatshriek/stumpless/tree/latest/docs/examples),
   and [support](https://gitter.im/stumpless/community).


## Quick Build and Install
Stumpless only requires cmake and a cmake-supported build toolchain (like GCC
or Visual Studio) to build. For a system using the standard GNU make toolchain,
you can simply do:

```sh
# cloning the latest version of the source tree
git clone git@github.com:goatshriek/stumpless.git

# creating a new build directory
mkdir build
cd build

# configuring the new build
cmake ../stumpless

# building stumpless (with 4 threads - adjust as desired)
make -j 4 all

# install the library (you probably need sudo to do this)
sudo make install
```

Check out the [Installation Instructions](INSTALL.md) for more detail on
building and installing stumpless in different environments and/or with other
toolchains.


## Basic Usage
The following code snippets show the most common ways to use stumpless.


### Basic Logging Functions
The simplest way to get started is to use the `stumplog` function as a direct
replacement for the standard library's `syslog` function:

```c
// if you're used to doing this:
syslog( LOG_INFO | LOG_USER, "My message" );

// then you can start doing this:
stumplog( LOG_INFO | LOG_USER, "My message" );
```

If you haven't opened a target, this will log messages to the default target for
the platform: on Linux this is `/dev/log`, on a Mac system this will be
`/var/run/syslog`, and on a Windows machine it is the Windows Event Log. If you
open a target or a few before calling `stumplog`, then logs will be sent to the
most recently opened target.

If you want an even shorter function call, you can use the `stump` function
to send a message to the current target:

```c
stump( "My message" );
```

And of course, you can use format specifiers in both functions just as you would
with `printf`:

```c
stump( "Login attempt failure #%d for user %s", count, username );
```

If you want to open a specific target rather than using the default, then just
open the target that you need and start sending messages. For example, to log to
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

Check out the headers in [stumpless/level](include/stumpless/level) to see the
full list of severity shorthand functions, or the
[severity level example](docs/examples/severity_level) to see a complete program
in action.


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

Or perhaps you are just looking for a way to say thanks! If that's the case or
if there is something that you would prefer to drop me a private message about,
please feel free to do so on Twitter with
[#StumplessLib](https://twitter.com/search?q=%23StumplessLib), or in an
[email](mailto:joelanderson333@gmail.com)! I'd love to see you share the project
with others or just hear your thoughts on it.


## Further Documentation
If you're curious about how something in stumpless works that isn't explained
here, you can check the appropriate section of the documentation, stored in the
docs folder of the repository. Folders in the repository contain their own
README files that detail what they contain and any other relevant information.
If you still can't find an answer, submit an issue or head over to
[gitter](https://gitter.im/stumpless/community) and ask for some help.

