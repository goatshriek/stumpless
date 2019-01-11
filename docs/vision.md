# Make debug all possible

This is a lofty goal. Keeping logging at a higher level and only turning on debug when needed and then only for troublesome components is the current norm, and for good reason. Consider the pitfall of issuing the `debug all` command to a network device, only to have the processor overwhelmed and the box crash under the deluge of messages. Many administrators even go so far as to specifically blacklist the command to prevent junior admins from unintentionally wreaking havoc.

But does this have to be the state of things? Logging is often an afterthought, assumed to be a minimum load on the system, and when it isn't then we simply throttle back the messages we see, potentially missing out on valuable troubleshooting information and causing application restarts just to adjust levels.

The stumpless project aims to make logging more efficient and less of a hassle for developers to include. This is the primary design goal: a rich and intuitive interface that is as unobtrusive as possible while still being flexible enough to range from a simple "log this string" to logging structured data. All of this will also comply with existing standards, to facilitate interoperability with existing collection and analysis tools.

Efficiency and performance are pillars of the design as well, so that logging statements are able to give troubleshooting information as often as possible. Faster execution, multi-thread and multi-process support, and strong compression are all tactics that will be brought to bear to keep logging overhead to an absolute minimum.

# stumpless does one thing

The only thing this library aims to do is generate logs and send them on the beginning of their journey home.

# What makes stumpless different?

There are a number of other logging libraries for C, boasting a variety of features including header-only, various target selections, and structured data options. Stumpless aims to bring the most useful of these features together in a single performant library built with modern development practices including test driven development and continuous integration. We hope to create a viable option for developers needing a lightweight and standardized logging library.
