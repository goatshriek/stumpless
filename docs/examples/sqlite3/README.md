# SQLite Targets
SQLite targets provide a way to send logs into a SQLite database, if you'd like
to store your logs there. A structured database provides a convenient place to
store data like logs, as well as a way to perform searches without setting up a
more complex sotrage and indexing system.

You can work with SQLite databases at three levels of abstraction in Stumpless,
each providing more control but requiring more effort in return. We'll go
through each option here in order of increasing complexity


# The `logs` Table
In the most basic SQLite target, logs are put into a table with the name given
in `STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING`, which defaults to `logs`. If
you open a target and immediately send an entry to it, this is the table that
it will go into. If the database doesn't exist, Stumpless will ask SQLite to
create it first.

The entry will be added using the insert statement given by
`STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL`, which is effectively something like
this:

```sql
INSERT INTO logs ( prival, version, timestamp, hostname, app_name, procid,
                   msgid, structured_data, message )
VALUES ( $prival, 1, $timestamp, $hostname, $app_name, $procid, $msgid,
        "$structured_data, $message );
```

Each variable is bound to the effective value held in the entry at the time that
it's logged.

If you don't want to bother creating the logs table, you can ask Stumpless to do
it for you by invoking `stumpless_create_default_sqlite3_table`. This will
create a table with the following schema:

```sql
CREATE TABLE logs (
  log_id INTEGER PRIMARY KEY,
  prival INTEGER NOT NULL,
  version INTEGER NOT NULL,
  timestamp TEXT,
  hostname TEXT,
  app_name TEXT,
  procid TEXT,
  msgid TEXT,
  structured_data TEXT,
  message TEXT
);
```

So, let's say we want to create a new database with the default logs table, and
log a few events. This would be done like so:

```c
struct stumpless_target *db_target;

// create the new database (or open the existing one)
db_target = stumpless_open_sqlite3_target( "stumpless_example.sqlite3" );

// create the default logs table (if it doesn't exist)
stumpless_create_default_sqlite3_table( db_target );

// send a simple message to our new logs table
stumpless_add_message( db_target, "cards are on the table" );
```

If we peeked into the database at this point, we would see an entry like
this for the message we added:

```
$ sqlite3 -header -column stumpless_example.sqlite3
SQLite version 3.22.0 2018-01-22 18:45:57
Enter ".help" for usage hints.
sqlite> SELECT * FROM logs;
log_id      prival      version     timestamp                    hostname    app_name    procid      msgid       structured_data  message
----------  ----------  ----------  ---------------------------  ----------  ----------  ----------  ----------  ---------------  ----------------------
1           14          1           2023-11-22T04:35:02.909888Z  Angus                   3090                                     cards are on the table
```

If you simply need to get entries into a database, then this usage might be all
that you need. Notice that you don't even need to use any SQLite3 functions or
headers: you can rely on Stumpless for that! But, if you need to customize this
a bit more, then you'll need to do a little more work.


# Custom `INSERT` Statements
If you only need to adjust the default behavior a little bit, you might be able
to accomplish this without much extra effort. The
`stumpless_set_sqlite3_insert_sql` function allows you to provide an alternate
SQL statement to run each time a log entry needs to be made. This allows you to
make changes like adjust the table name, fields included, or hard-code certain
values.

You might have noticed that the default SQL statement uses several named SQL
parameters for the entry values. You can use these in your custom SQL as well!
They are resolved by name (position is ignored) and if a name is not present
in the SQL then it is simply left out. In addition to the parameters listed in
the default statement, there are a few more available if you need them:

 * `$facility` is the facility portion of the entry as an integer. This is
   equivalent to the integer value of `stumpless_get_entry_facility` of the
   entry.
 * `$severity` is the severity portion of the entry as an integer. This is
   equivalent to the integer value of `stumpless_get_entry_severity` of the
   entry.

For this example, lets say that you have your own log table with the following
schema, and you want entries to go into it instead.

```sql

```

# Custom Prepared SQL Statements
TODO fill in
