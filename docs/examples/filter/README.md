# Runtime Filters
Stumpless offers a number of functions that allow logging calls to be filtered
out at compile time, meaning that there is zero performance impact to running
workloads. However, sometimes you need the added flexibility to set and adjust
these filters in an existing binary, and compile-time filters are not feasible.
Fortunately, there is also a runtime filtering mechanism that you can use to
do just that.

By default, all targets have a runtime filter set that inspects the severity
mask that's been set on a target. These masks are set to allow any entry
severity through by default, so if you haven't messed with them then it's like
they aren't even there. This default filter mimics that available in the
standard `syslog.h` `setlogmask` capability, and is even compatible with these
masks if you're using them already.

```c
// the syslog.h code would look like this:
setlogmask( LOG_UPTO( LOG_ERROR ) );

// the minimum change to use stumpless would look like this:
stumplog_setmask( LOG_UPTO( LOG_ERROR ) );
```

When a `syslog.h` header is available, most syslog calls have a matching call
in stumpless that has the same signature and semantics. For `setlogmask`, that
function is `stumplog_set_mask`. It sets the log mask for the current target,
and returns the mask that was previously being used.


