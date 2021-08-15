# Journald Targets
Journald targets provide a way to send logs to systemd's logging service of the
same name. A discussion of all of the things that journald provides is outside
the scope of this example, but can be found in the `systemd-journald.service`
[man page](https://www.linux.org/docs/man8/systemd-journald.html). This
example shows how to send information to the service in both structured and
unstructured ways, along with some basic commands to see what the data looks
like once it's in journald.

Since the name implies a journal, we'll make log entries out of things that
have happened in our day that are worthy of remembering. First, we need to
set up a target to our local service.

```c
my_journal = stumpless_open_journald_target( "daily-journal" );

// this is optional, but makes our messages easier to find later
stumpless_set_target_default_app_name( my_journal, "daily-journal" );
```

And now, we can send messages as with any other target.

```c
stumpless_add_message( my_journal, "rode my bike with no handlebars" );
stumpless_add_message( my_journal, "curled up with a book to read" );
stumpless_add_message( my_journal, "designed an engine with 64 mpg" );
```

That's it! If you want to see your messages in journald, you can use the
`journalctl` tool to query for them like this:

```sh
journalctl --identifier daily-journal

# sample output:
# -- Logs begin at Sat 2021-07-31 20:05:12 EDT, end at Sat 2021-07-31 20:17:01 EDT. --
# Jul 31 20:11:04 debian-10-9 daily-journal[763]: rode my bike with no handlebars
# Jul 31 20:11:04 debian-10-9 daily-journal[763]: curled up with a book to read
# Jul 31 20:11:04 debian-10-9 daily-journal[763]: designed an engine with 64 mpg
```

Okay, maybe that's not _all_ that there is to see. Journald supports structured
logging, and it would be handy if we could take advantage of that. Let's see how
that looks by creating an entry with a few fields and sending that to our
target.

```c
entry = stumpless_new_entry( STUMPLESS_FACILITY_DAEMON,
                             STUMPLESS_SEVERITY_INFO,
                             "daily-journal",
                             "detailed-status",
                             "alive and on top" );
stumpless_add_new_param_to_entry( entry, "my", "reach", "global" );
stumpless_add_new_param_to_entry( entry, "my", "tower", "secure" );
stumpless_add_new_param_to_entry( entry, "my", "cause", "noble" );
stumpless_add_new_param_to_entry( entry, "my", "power", "pure" );

stumpless_add_entry( my_journal, entry );
```

If we do the same journalctl command, we'll just see the message from our entry.
If we want to see our structured data, we'll need to see more of the fields. We
can do that by specifying that we want json output.

```sh
journalctl --identifier daily-journal --output json-pretty
```

This shows you the below output, in which you can see fields for each of the
params that we added above. Note that the element and param names have been
converted to uppercase and combined to be valid journald field names.

```json
{
	"_BOOT_ID" : "e62cf00fedf64d9d8021aa4c62982cb3",
	"MY_REACH" : "global",
	"MY" : "",
	"PRIORITY" : "6",
	"__REALTIME_TIMESTAMP" : "1627776664688160",
	"MY_TOWER" : "secure",
	"__CURSOR" : "s=f7b7ebc77b4b4a23883ba6adf6976ca3;i=278;b=e62cf00fedf64d9d8021aa4c62982cb3;m=151ec212;t=5c87449df5620;x=addbc8df5d0f316c",
	"SYSLOG_TIMESTAMP" : "2021-08-01T00:11:04.687283Z",
	"SYSLOG_IDENTIFIER" : "daily-journal",
	"__MONOTONIC_TIMESTAMP" : "354337298",
	"SYSLOG_MSGID" : "detailed-status",
	"MY_CAUSE" : "noble",
	"_UID" : "1000",
	"_GID" : "1000",
	"_PID" : "763",
	"_TRANSPORT" : "journal",
	"SYSLOG_PID" : "763",
	"_SOURCE_REALTIME_TIMESTAMP" : "1627776664687293",
	"MESSAGE" : "alive and on top",
	"SYSLOG_FACILITY" : "3",
	"MY_POWER" : "pure",
	"_MACHINE_ID" : "6e82c858acbd49a0802be698e8f3cb10",
	"_HOSTNAME" : "debian-10-9"
}
```

You can define your own functions to change the way the field names are
generated if the default doesn't suit you. Just take a look at the documentation
for `stumpless_set_element_journald_namer` and
`stumpless_set_param_journald_namer` to see how that can be done.
