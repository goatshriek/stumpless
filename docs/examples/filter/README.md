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
setlogmask( LOG_UPTO( LOG_ERR ) );

// the minimum change to use stumpless would look like this:
stumplog_set_mask( LOG_UPTO( LOG_ERR ) );
```

When a `syslog.h` header is available, most syslog calls have a matching call
in stumpless that has the same signature and semantics. For `setlogmask`, that
function is `stumplog_set_mask`. It sets the log mask for the current target,
and returns the mask that was previously being used. That's what allows us to
make the substition in the above code so simple.

If you want to write code that is portable to systems without the `syslog.h`
header (Windows, for example), then you can remove the other syslog-specific
macros with the stumpless lookalikes:

```c
// portable to any system that stumpless supports (which is a lot!)
stumplog_set_mask( STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR ) );
```

Yes, this is a little more verbose, but it will work everyhere stumpless does.
Of course, you can combine masks with bitwise ors and everything else you would
expect from a mask as well.

```c
// this will allow EMERG, ALERT, CRIT, ERR, and DEBUG severity messages
stumplog_set_mask( STUMPLESS_SEVERITY_MASK( STUMPLESS_SEVERITY_DEBUG )
                     | STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR ) );
```

The default target filter will use the mask on the target to make these
decisions. If you want to work with a specific target instead of just using the
current one, you can use the `stumpless_get_target_mask` and
`stumpless_set_target_mask` functions to do this.

```c
// let's see what we have now
mask = stumpless_get_target_mask( target );

// and make sure that DEBUG messages are NOT included
new_mask = mask & ~STUMPLESS_SEVERITY_MASK( STUMPLESS_SEVERITY_DEBUG ) );
stumpless_set_target_mask( target, new_mask );
```

But perhaps we have some magical filtering that we'd like to do. Maybe we want
to make sure that no entries are logged that contain an element named `ignore`.
This seems reasonable.

Stumpless provides a simple way to accomplish this! First, we need to write a
filter function that takes the target and entry as parameters, and returns a
decision on whether to allow the entry. In our case, we just check for the
existence of an element with our chosen name.

```c
bool
ignore_element_filter( const struct stumpless_target *target,
                       const struct stumpless_entry *entry ) {
  return !stumpless_get_element_by_name( entry, "ignore" );
}
```

And then we apply the new filter to the target like so:

```c
stumpless_set_filter( target, ignore_element_filter );
```

That's it! Now any messages sent through this target will use our filter
function instead of the default mask filter. Just remember that if you want to
combine filters, you'll need to call the previous ones in your own filter as
well, using whatever logic you'd like. For example, if we wanted our filter to
do both mask filtering and element name filtering, it would look like this:

```c
bool
ignore_element_filter( const struct stumpless_target *target,
                       const struct stumpless_entry *entry ) {
  return !stumpless_get_element_by_name( entry, "ignore" )
           && stumpless_mask_filter( target, entry );
}
```

For a list of available filters provided by stumpless, check out the
`stumpless/filter.h` header installed with the library or in the
documentation.
