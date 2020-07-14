# Severity Level Logging

Severity levels exist in most logging APIs as a convenient way to categorize messages at a broad level. The severities in stumpless directly match those specified in the syslog standard ([RFC 5424](https://tools.ietf.org/html/rfc5424)), which are common to most languages and platforms.

 | Name    | Shorthand | Description                      |
 |---------|-----------|----------------------------------|
 | EMERG   | em        | system is unusable               |
 | ALERT   | a         | action must be taken immediately |
 | CRIT    | c         | critical conditions              |
 | ERR     | er        | error conditions                 |
 | WARNING | w         | warning conditions               |
 | NOTICE  | n         | normal but significant condition |
 | INFO    | i         | informational messages           |
 | DEBUG   | d         | debug-level messages             |

Each of these can be referred to by the `STUMPLESS_SEVERITY_<NAME>` symbol in order to specify them whenever a severity is required. Because each severity must be combined with a facility code to be useful in a message, this results in long-winded code snippets like this:

```c
stumplog( STUMPLESS_FACILITY_DAEMON | STUMPLESS_SEVERITY_ERR,
          "the cheese daemon failed again..." );
```

Whew, that is a lot of characters to express only two pieces of information! Facility codes can be determined by the default facility of the target messages are logged to, but if you need to specify a particular severity it has to either be set in the above fashion or you must create an entry object with the require facility and severity levels set. This is a pain when you just need some quick logging messages.

It is also a common requirement to only log messages of a certain level. Perhaps the most obvious use case is to support different builds: a production build which only needs to log messages up to a certain point, and a debug build which needs to log all possible messages to facilitate troubleshooting and execution tracing.

Whatever the needs are, stumpless provides a family of macro functions that operate at one of the severity levels and can be removed at compile time if desired. These functions use the shorthand abbreviation for the level, and are replaced with an equivalent call to a logging function if enabled. If they are instead disabled, they are replaced with a no-op or constant return value which removes the runtime impact of the logging call. These functions are detailed in the following table:

 | Function Name               | Equivalent Function     |
 |-----------------------------|-------------------------|
 | `stump_<shorthand>`         | `stump`                 |
 | `stump_<shorthand>_entry`   | `stumpless_add_entry`   |
 | `stump_<shorthand>_log`     | `stumpless_add_log`     |
 | `stump_<shorthand>_message` | `stumpless_add_message` |
 | `stumplog_<shorthand>`      | `stumplog`              |

By default, all severity levels are logged. If you decide that you don't want messages from a specific severity level, then you just need to define `STUMPLESS_DISABLE_<LEVEL_NAME>_LEVEL`. For example, to remove NOTICE level logs (and NOTICE level logs only) you could define `STUMPLESS_DISABLE_NOTICE_LEVEL`. This allows you to selectively remove logging levels that you don't want while leaving others.

If you want to enable logs of higher importance but disable lower ones, you can define the `STUMPLESS_ENABLE_UPTO_<LEVEL_NAME>` or `STUMPLESS_DISABLE_DOWNTO_<LEVEL_NAME>` symbols. These provide a faster way to disable one group of messages while leaving the others.

It is important to note that not all of these functions result log a message with their severity when enabled. For example, the `stump_i_entry` function may log a message with severity EMERG if the provided entry has this severity set. Similarly, the `stumplog_a` function may log a message with DEBUG severity if this is provided as the first argument. Consult the documentation if you aren't sure what the severity will reflect, but you can generally assume that if the severity isn't set by an argument then it will reflect the severity of the call.

```c
// as you would expect, this has info severity
stump_i( "this message will have INFO severity" );

// this one has a severity of EMERG though, despite being an INFO level call
stumplog_i( STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_EMERG,
            "THE SYSTEM IS DOWN!!!" );
```

The easiest way to see how these functions operate is to experiment with them. The following block logs a message at each level: compile this code with different symbols defined to see how the logged messages change to reflect the levels.

```c
stump_em( "emergency!" );
stump_a( "alert!" );
stump_c( "critical!" );
stump_er( "error!" );
stump_w( "warning!" );
stump_n( "notice" );
stump_i( "informational" );
stump_d( "debug" );

// without any extra symbols defined, this will result in these messages:

// if you define the following symbols:
// this will result in these messages:

// if you define the following symbols:
// this will result in these messages:

// if you define the following symbols:
// this will result in these messages:
```