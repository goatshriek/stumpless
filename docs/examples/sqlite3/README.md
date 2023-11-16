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
this for you using `stumpless_create_default_sqlite3_table`. This will make a
table with the following schema:

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
$ sqlite3 stumpless_example.sqlite3
```