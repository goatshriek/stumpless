The vision of the stumpless project can be defined as simply

## Make debug all possible.

This is a lofty goal. Keeping logging at a higher level and only turning on debug when needed and only for troublesome components is the current norm, and for good reason. A perfect example of this is the pitfall of issuing the `debug all` command to a network device, only to have the processor overwhelmed and the box crash under the deluge of messages. Many administrators even go so far as to specifically blacklist the command to prevent junior admins from unintentionally wreaking havoc.

But does this have to be the state of things? Logging is often an afterthought, assumed to be a minimum load on the system, and when it isn't then we simply throttle back the messages we see, potentially missing out on valuable troubleshooting information and causing application restarts just to adjust levels.
