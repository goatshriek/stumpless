# Make debug all possible
This is a lofty goal. The current standard practice is to keep logging at a high
level and only turn on debug when needed, and even then only for troublesome
components. And this is for good reason. Consider the pitfall of issuing the
`debug all` command to a network device, only to have the processor overwhelmed
and the box crash under the deluge of messages. Administrators may even go so
far as to specifically blacklist the command to prevent junior admins from
unintentionally wreaking havoc.

But does this have to be the state of things? Logging is often implemented as
an afterthought, assumed to be a minimum load on the system. And when it isn't,
we simply throttle back the messages we record, potentially missing out on
valuable information and causing application restarts just to adjust levels.

The Stumpless project aims to make logging more efficient while less of a hassle
for developers to include. This is the primary design goal: a rich and intuitive
interface that is as unobtrusive as possible while still being flexible enough
to range from a simple "log this string" to logging structured data. All of this
in compliance with existing standards, to facilitate interoperability with
existing collection and analysis tools.

Efficiency and performance are pillars of the design as well, so that logging
statements are able to give as much troubleshooting information as possible.
Faster execution, multi-thread and multi-process support, and strong compression
are all tactics brought to bear to keep logging overhead to an absolute minimum.

By offering these functions directly from the library, stumpless allows
applications to converge log generation and transmission into the application
itself. This removes the need for a separate logging daemon for the same
functionality, reducing integration points and interdependencies and making for
a more robust and efficient end product.


# What makes this special?
There are a number of other logging libraries for C, boasting a variety of
features including header-only, various target selections, and structured data
options. Stumpless aims to bring the most useful of these features together in a
single performant library built with modern development practices including test
driven development and continuous integration. We hope to create a viable option
for developers needing a lightweight and standardized logging library.


# Things this isn't
The only problem this library aims to solve is how to create log messages and
send them on their journey home. There are certainly other logging-related tasks
that are important, but this project doesn't do them. Most notably:


### Log Analysis
Log parsing, indexing, storage, and analysis are huge tasks that already have
a number of high-profile solutions focused on them. While stumpless is built to
complement them, it certainly does not provide any of their features. You should
instead look to projects like [Splunk](https://www.splunk.com/) or
[ELK stack](https://www.elastic.co/elk-stack) for this.


### Log Management
While stumpless can send logs in a variety of ways, it does not necessarily
manage end-to-end transport or the final storage. There are plenty of log
forwarding and collection solutions already available such as
[rsyslog](https://www.rsyslog.com/), [syslog-ng](https://www.syslog-ng.com/),
and
[Splunk log forwarders](https://www.splunk.com/en_us/download/universal-forwarder.html).
If you find yourself looking for a way to manage log files, for example to
receive and forward logs, then you should consider using something like these
instead.

There are some features of stumpless that might overlap with these tools, such
as log file rotation. If this is truly all that you need, then rejoice! However,
take care that you are able to recognize when you are looking for a feature that
is out of scope of what stumpless provides and begin to look elsewhere.
