# Windows Event Log
A Windows Event Log target (or as you may see in some code, a wel target)
provides a mechanism for interfacing with the Event Log on either the local
machine or a remote one. The target logs events in the same way as others (using
the `stumpless_add_entry` function), but there are some extra steps needed to
make sure that an entry is properly logged. This extra work arises from
differences between current Syslog standards (which stumpless is designed for)
and the Windows Event Log system. However, an entry that has been enhanced for
Windows Event Log compatibility can still be used with other targets with no
problems. For example, it is perfectly acceptable to send the same entry through
both a Windows Event Log target and a file target. And if you feel that this
work is too much, you can simply ignore it and stumpless will do its best to
get meaningful information into the Event Log based on what it already has.

Note that Windows Event Log targets will only be available in builds where they
are enabled (which requires the `windows.h` header). If you aren't sure whether
your build has the necessary fields and functions, you can check to see if
`STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED` is defined by inclusion of the
`stumpless.h` header (the exact definition will appear in `stumpless/config.h`).

For this example, we will consider an application that needs to record the types
of trees identified by children during a nature walk. Specifically, we will look
at the event that occurs when a child points out a tree.

Creation of a Windows Event Log target is done using either the
`stumpless_open_local_wel_target` or `stumpless_open_remote_wel_target` function
calls. The first opens an Event Log on the local machine with the given name,
while the second attempts to open an Event Log on a remote server with a
provided name.

```c
local_wel_target = stumpless_open_local_wel_target( "Stumpless Example" );

remote_wel_target = stumpless_open_remote_wel_target( "\\RemoteServerName",
                                                      "Stumpless Example" );
```

Windows Event Log entries have three extra properties that standard entries
do not. These are the event category, ID, and type. If you would like to know
more about the specific significance of any of these values, you should check
out the
[Microsoft documentation](https://docs.microsoft.com/en-us/windows/desktop/eventlog/event-logging-elements).
For the purposes of this example however, you can simply treat these as values
that are defined in your
[Message File](https://docs.microsoft.com/en-us/windows/desktop/eventlog/message-files)
and included via a generated header.

If all of that sounds like too much work though, you can simply send entries
straight to the Windows Event Log, and stumpless will apply some sensible
defaults. We'll cover that case first as it is simpler to use and understand,
and then show how you could log your own messages if you want to be a little
more thorough.


## Default Windows Event Log Messages
Stumpless comes with a set of Windows Event Log messages intended to convey
the information already provided with each log entry. If you send an entry to
a Windows Event Log target without setting the wel-specific fields, these values
will be used by default. This is intended to serve as a "good enough" solution
to get you off the ground, and you can always change to your own custom messages
later when you're ready.

But there is still a little bit of work required to get these default messages
to show up cleanly in the Event Viewer, unfortunately. Event sources must be
registered with the system so that it knows where to look for the category,
message, and other information. This is done via making some entries in the
registry. The Windows documentation mentioned above has the information you
need to make these entries yourself. But if that sounds like more than you want
to do, stumpless has a few functions that will do it for you.

`stumpless_add_default_wel_event_source` is the easiest to use, which installs
all of the appropriate registry entries for you for the default source. This
function creates a source named 'Stumpless', and points the message and category
files back to the file containing the currently executing stumpless library.
Note that this may be a DLL or an EXE, depending on how you've linked with
stumpless during compilation. Note that this also means that you should only
call this function with the appropriate permissions, and once the library or
executable is in its final location. If the registry keys already exist then
this doesn't duplicate anything, so you can call this during initialization
of your application each time if you want.
`stumpless_remove_default_wel_event_source` is the opposite of this function,
removing all of these registry entries, but _not_ the file itself of course!

Once this is done, you'll see a registry entry at
`HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Stumpless` with
the installation details. When you log to the `Stumpless` event source from a
wel target (the default target for Windows builds), you'll see the entries show
up here. The message will be a description of the form
`<Facility> <Severity> message: <message>` where the facility, wel severity, and
entry message are substituted, respectively. The complete syslog message in RFC
5424 format will also be written to the event's data field.

Note that the Windows Event Log severity is _different_ from the Syslog
severity! There are only four Windows Event severities: Success, Informational,
Warning, and Error. The syslog severity is mapped to the closest wel severity,
which may cause some confusion if you aren't expecting it. The syslog severity
is captured in the category for the message. So don't be confused if you see a
message with a category of "Alert" but the message says "Error"!


## Custom Windows Event Log Messages
If you take the jump to define your own messages, you'll need to write a message
file and compile it into a resource that you can then register. You can of
course make the necessary registry entries yourself, or you can use the
`stumpless_add_wel_event_source` function (or its `_w` sibling) to do this for
you, provided the necessary values. Likewise,
`stumpless_remove_wel_event_source` provides a way to remove these.

Each of the three wel-specific fields of an entry can then be set to use your
custom messages and categories before the entry is sent to the Windows Event Log
target for more tailored logs. This is done via the corresponding Windows Event
Log target-specific functions:

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


## Insertion Strings
Windows Event Log messages may contain placeholders for insertion strings,
which are intended to be filled in with some variable later on. These
simple placeholders are different from the structured elements and params
defined in the Syslog standard, and therefore require separate treatment to
work. For example the log message might appear like this in the message text
file:

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

Both of these functions have versions with `_w` appended to them that accept
wide character strings instead of multibyte ones. Both of these forms support
unicode (UTF-8 without the `_w`, UTF-16 with), but as Windows applications often
work with wide character strings, both options are available for you to choose
from depending on your specific situation. Other Windows Event Log support
functions also have `_w` suffix versions available as well.

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
change the insertion string value each time.


## Cleaning Up
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
