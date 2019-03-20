# Windows Event Log

A Windows Event Log target (or as you may see in some code, a wel target)
provides a mechanism for interfacing with the Event Log on either the local
machine or a remote one. While the target logs events in the same way as others
(using the `stumpless_add_entry` function), there are some extra steps needed to
make sure that an `entry` struct can be properly logged. This extra code arises
from differences between current Syslog standards (which stumpless is designed
for) and the Windows Event Log system. However, an entry that has been enhanced
for Windows Event Log compatibility can still be used with other targets with no
problems. For example, it is perfectly acceptable to send the same entry through
both a Windows Event Log target and a file target.

Note that Windows Event Log targets will only be available in builds where they
are enabled (which requires the `windows.h` header to be available). If you
aren't sure whether your build has the necessary fields and functions, you can
check to see whether `STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED` is defined
by inclusion of the `stumpless.h` header (the exact definition will appear in
`stumpless/config.h`).

For this example, we will consider an application that needs to record the types
of trees identified by children during a nature walk. Specifically, we will look
at the event that occurs when a child points out a tree.

Creation of a Windows Event Log target is done using either the
`stumpless_open_local_wel_target` or `stumpless_open_remote_wel_target` function
calls. The first opens an Event Log on the local machine with the given name,
while the second attempts to open an Event Log on a remote server with a
provided name.

```c
local_wel_target = stumpless_open_local_wel_target( "Stumpless Example",
                                                    STUMPLESS_OPTION_NONE );
remote_wel_target = stumpless_open_remote_wel_target( "\\RemoteServerName",
                                                      "Stumpless Example",
                                                      STUMPLESS_OPTION_NONE );
```

Windows Event Log-compatible entries have three extra properties that standard
entries do not. These are the event category, ID, and type. If you would like to
know more about the specific significance of any of these values, you should
check out the [Microsoft documentation](https://docs.microsoft.com/en-us/windows/desktop/eventlog/event-logging-elements).
For the purposes of this example however, you can simply treat these as values
that are defined in your [Message File](https://docs.microsoft.com/en-us/windows/desktop/eventlog/message-files)
and included via a generated header.

Each of these three extra fields of an entry must be set before the entry is
sent to the Windows Event Log target. This can be done via the corresponding
Windows Event Log target-specific functions:

 * `stumpless_set_wel_category`
 * `stumpless_set_wel_event_id`
 * `stumpless_set_wel_type`

So, with an already created entry, we could make it ready for a Windows Event
Log target like this (assuming the symbols used are defined in an included
message header):

```c
stumpless_set_wel_category( entry, CATEGORY_TREE );
stumpless_set_wel_event_id( entry, MSG_TREE_IDENTIFIED_BY_CHILD );
stumpless_set_wel_type( entry, EVENTLOG_SUCCESS );
```

These three fields are all that are required for success with a Windows Event
Log target. Note that this means that fields used by other targets (such as the
message) are ignored by Windows Event Log targets.

However, Windows Event Log messages may contain placeholders for insertion
strings, which are intended to be filled in with some variable later on. These
simple placeholders are different from the structured elements and params
defined in the Syslog standard, and therefore require some special treatment to
be used correctly. For example the log message might appear like this in the
message text file:

    %1 found a %2 tree!

The simplest way to specify the value of an insertion string is simply to set it
manually via the `stumpless_set_wel_insertion_string` function. This function
accepts the entry to be modified, the index of the placeholder to replace
(starting with 0 as the first), and the string to use as the replacement. So, to
set the two placeholders with the name and tree type, you would write the
following:

```c
stumpless_set_wel_insertion_string( entry, 0, "cynthia" );
stumpless_set_wel_insertion_string( entry, 1, "oak" );
```

A potentially faster approach is to use the plural version of this function to
set multiple insertion strings at once. It takes a variable number of arguments
preceded by the count of strings that will be provided. The following function
call has identical results to the previous two:

```c
stumpless_set_wel_insertion_strings( entry, 2, "cynthia", "oak" );
```

In the case where you would like to send a single entry through multiple
targets, you may have already done the work to put the value into a param
structure, and would like to avoid the repetition of setting the insertion
string as well. This is accomplished by using the
`stumpless_set_wel_insertion_param` function, which instead of a string literal
takes a param. The value of this param is then used for the substitution when
the logging occurs. So, to accomplish the same as the previous example:

```c
// assuming the values of param_1 and param_2 are "cynthia" and "oak"
stumpless_set_wel_insertion_param( entry, 0, param_1 );
stumpless_set_wel_insertion_param( entry, 1, param_2 );
```

This approach is more flexible, because updates to the value of param will be
reflected in subsequent logs. This allows an entry and supporting params to be
created once, updated as needed, and used continuously. This will be much more
performant, as it avoids unnecessary memory allocation and repetitive calls to
change the insertion string value as needed.

Entries can be logged as with any other target once the category, id, and type
are set as well as any insertion strings desired.

```c
stumpless_add_entry( wel_target, entry );
```

When the target is no longer needed, it can be closed via the
`stumpless_close_wel_target` for both local and remote targets. Keep in mind
that this function destroys any memory associated with the target, so the
structure should not be referenced after calling this function.

```c
stumpless_close_wel_target( wel_target );
```

And of course if you'd like to type a little less:

```c
stumpless_close_target( wel_target );
```
