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

Be careful when you are destroying an entry, as there are two ways to do this.
The first function, `stumpless_destroy_entry_and_contents`, destroys the entry
as well as all elements and params in it. In most cases this is the simplest
and fastest option.

```c
// everything must go!
stumpless_destroy_entry_and_contents( entry );
```

However, if you're sharing elements or params between entries, then you will
need to be a little more careful about destroying these to avoid double-free
errors. For this reason, the `stumpless_destroy_entry_only` function will
tear down the entry but leave all elements and params intact. These can then
be destroyed individually.

This snippet illustrates this concept, where two entries share a context element
with details about a session. The individual entries are torn down separately,
and the element is then destroyed on its own.

```c
// using the same context in any entry that needs it
refresh_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_NOTICE,
                                     "company-web-portal",
                                     "refresh-request",
                                     "user requested a refresh" );
stumpless_add_element( refresh_entry, context );

logout_entry = stumpless_new_entry( STUMPLESS_FACILITY_AUTH,
                                    STUMPLESS_SEVERITY_NOTICE,
                                    "company-web-portal",
                                    "logout",
                                    "user logged out" );
stumpless_add_element( logout_entry, context );

// the entries are used throughout the program...

// cleanup is done separately to avoid double-free of the element
stumpless_destroy_entry_only( logout_entry );
stumpless_destroy_entry_only( refresh_entry );
stumpless_destroy_element_and_contents( context );
```
