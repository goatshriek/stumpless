# Stumpless Security Policy
This document describes the security support for Stumpless, including versions
that will be patched and the procedure for submitting vulnerabilities. It also
includes security-relevant guidance on how to use the library, and particular
pitfalls that must be avoided to ensure that vulnerabilities are not introduced
into the system.


## Supported Versions
The table below lists the current supported versions of Stumpless. Generally,
the current and previous major versions are supported at their highest minor
version.

| Version | Supported          |
| ------- | ------------------ |
| 2.2.x   | :heavy_check_mark: |
| 2.1.x   | :x:                |
| 2.0.x   | :x:                |
| 1.6.x   | :heavy_check_mark: |
| <= 1.5  | :x:                |


## Reporting a Vulnerability
If you discover a problem with Stumpless, please report it immediately to the
project owner, [Joel Anderson](mailto:joelanderson333@gmail.com). The issue
will be investigated as soon as possible and you will receive a response within
14 days of the message.

A fix will be deployed to all affected supported versions with a high priority.
However, there is currently no guaranteed timeline for the patch as the project
does not have any dedicated resources.

You can increase the speed and effectiveness of the response by including as
much detail in your report as possible. Suggested fixes are welcome as well,
though we ask that you keep your fixes limited to private correspondence until
a fix can be deployed to limit the risk to users of the library in the meantime.


## Secure Use
The following aspects of use should be carefully considered by anyone using
stumpless. Mistakes in these areas can lead to vulnerabilities in an application
using the library.


### Understand `new` vs. `load` lifetimes
?
