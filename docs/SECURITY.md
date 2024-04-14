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
project owner, [Joel Anderson](mailto:joel@goatshriek.com). The issue will be
investigated as soon as possible and you will receive a response within 14 days
of the message.

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
Stumpless provides a number of functions with similar functionality but
different mechanics in an effort to give users the most efficient way to
accomplish what they need. For example, in some cases, a structure like a log
entry will only be needed within a short or well-defined scope, and therefore
does not need to be allocated on the heap. The `load` functions allow the caller
to provide a pointer to a structure, avoiding the heap allocation for the entry
that would otherwise occur in a `new` function.

However, this performance boost does come with a risk. Users need to make sure
that they are using the matching `unload` functions with structures initialized
this way. In particular, the recursive destructors need to be careful matched so
that for example `stumpless_destroy_entry_and_contents` isn't called on an entry
that had a param created with `stumpless_load_param`.

Failure to adhere to these rules can result in issues ranging from memory leaks
to serious security risks like
[double free](https://cwe.mitre.org/data/definitions/415.html) and
[attempting to free memory not on the heap](https://cwe.mitre.org/data/definitions/590.html).
The best way to mitigate this is to follow a single convention in your project,
and stick with that. Avoid mixing styles of allocation unless you absolutely
must.
