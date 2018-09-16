# Stumpless

[![Travis Build Status](https://travis-ci.org/goatshriek/stumpless.svg?branch=master)](https://travis-ci.org/goatshriek/stumpless)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/uwied5cn5jujl4d2/branch/master?svg=true)](https://ci.appveyor.com/project/goatshriek/stumpless)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/master/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

A simple logging library.

Current features include:
* RFC 5424 compliant logging to the following targets:
  * files
  * character buffers
  * Linux sockets

## Documentation
If you're curious about how something in stumpless works, you can check the
appropriate section of the documentation, stored in the `doc` folder.

### Syslog v2 Specification
An RFC-style definition of the Syslog v2 protocol is given in the `doc/syslogv2`
folder. An XML file is included which can be used to generate the desired RFC
document using the `xml2rfc` tool.

## scripts
The `scripts` directory contains single-file tools useful for the development
of the project, such as file formatting scripts and header inclusion checks.

## tools
The `tools` directory contains files to support third-party tools used by
stumpless, such as cmake.
