# Entries

Entries are at the heart of all logging performed by Stumpless. While they may
not be explicitly seen in calls like the `stumpless` function, they are
still involved behind the scenes. Understanding how to use them leads to
cleaner and more performant code.

Entries are modeled directly after the hierarchy defined in
[RFC 5424](https://tools.ietf.org/html/rfc5424), including most fields of the
message as well as the structured data. When creating a new entry the mandatory
fields are supplied, and then any structured data is added to the entry
afterwards.

```c
entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                             STUMPLESS_SEVERITY_INFO,
                             "my-app-name",
                             "my-msgid",
                             "my event message" );
```

Fields such as the timestamp and the process id will be automatically filled
in when the message is actually logged to a target. Note that there is no need
to end the message with a newline, as delimitting is taken care of by the
library itself.

The message can take any format specifiers that are valid in printf, so messages
can be crafted to contain extra information, like this:

```c
entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                             STUMPLESS_SEVERITY_INFO,
                             "my-app-name",
                             "my-msgid",
                             "message by user %s",
                             username );
```

If you need to update the message with a different user later, you'll need to
reset the message of the entry like this:

```c
stumpless_set_entry_message( entry, "message by user %s", username );
```

While this creates an entry with a message containing specific information, it's
often more useful to separate fields into structured data so that it can be
easily parsed and indexed efficiently by a remote collector such as Splunk. For
the above example of a username, you could add this information to the entry
like this:

```c
element = stumpless_new_element( "user" );
param = stumpless_new_param( "username", username );
stumpless_add_param( element, param );
stumpless_add_element( entry, element );
```

This is certainly much more verbose than using the format string style, but it
does result in a more structured message that can be cleanly parsed. There are
also a number of convenience functions that make this much more concise. Using
these we can shorten the four calls above to a single function:

```c
stumpless_add_new_param_to_entry( entry, "user", "name", username );
```

In more complex messages with many pieces of information, using structured data
may actually be a cleaner option. Consider the following snippet to log a failed
login attempt event. The entry has been created once and saved, so that when the
event is logged all that happens is the parameters are updated and the entry
logged. This code could be packaged into a simple `log_failed_login` function
to further encapsulate it wherever it is needed.

```c
stumpless_set_param_value_by_name_from_entry( entry, "user", "name", username );
stumpless_set_param_value_by_name_from_entry( entry, "user", "id", user_id );
stumpless_set_param_value_by_name_from_entry( entry, "user", "locked", locked );
stumpless_set_param_value_by_name_from_entry( entry, "try", "number", try_num );
stumpless_add_entry( aaa_target, entry );
```
