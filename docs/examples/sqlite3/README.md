# SQLite Targets
SQLite targets provide a way to send logs into a SQLite database, if you'd like
to store your logs there. A structured database provides a convenient place to
store data like logs, as well as a way to perform searches without setting up a
more complex storage and indexing system.

You can work with SQLite databases at three levels of abstraction in Stumpless,
each providing more control but requiring more effort in return. We'll go
through each option in order of increasing complexity.


# The `logs` Table
In the most basic SQLite target, logs are put into a table with the name given
in `STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING`, which defaults to `logs`. If
you open a target and immediately send an entry to it, this is the table that
it will go into. If the database doesn't exist, Stumpless can ask SQLite to
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
in the SQL then it is simply left out. In addition to the parameters used in
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
CREATE TABLE card_logs (
  log_id INTEGER PRIMARY KEY,
  facility INTEGER NOT NULL,
  severity INTEGER NOT NULL,
  timestamp TEXT,
  structured_data TEXT,
  message TEXT
);
```

We've made a few adjustments to the default schema here. Of course, there is a
different table name to be more descriptive about the type of logs that are in
the table. We've also broken the prival into its separate parts, so that it is
easier to filter entries using SQL without needing to parse the prival first.
Finally, we've cut the columns down to specific things that our application
cares about.

The default insert statement won't work here of course, so we'll need to write
a new one to fit. This is pretty straightforward:

```sql
INSERT INTO card_logs ( facility, severity, timestamp, structured_data,
                        message )
VALUES ( $facility, $severity, $timestamp, $structured_data, $message )
```

Assuming this SQL is in a variable named `card_logs_insert`, all we need to do
is set this as our target's insert SQL:

```c
stumpless_set_sqlite3_insert_sql( db_target, card_logs_insert );
```

Now we can start putting logs into our new table! This time, we'll include some
structured data in our entry as well.

```c
entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                             STUMPLESS_SEVERITY_INFO,
                             "card-counter",
                             "card-played",
                             "a card was played" );

stumpless_add_new_param_to_entry( entry, "card", "suit", "hearts" );
stumpless_add_new_param_to_entry( entry, "card", "rank", "5" );
stumpless_add_new_param_to_entry( entry, "player", "name", "bill" );

stumpless_add_entry( db_target, entry );
```

Let's take a look in the database and see this looks like.

```
$ sqlite3 -header -column stumpless_example.sqlite3
SQLite version 3.22.0 2018-01-22 18:45:57
Enter ".help" for usage hints.
sqlite> SELECT * FROM card_logs;
log_id      facility    severity    timestamp                    structured_data                                    message
----------  ----------  ----------  ---------------------------  -------------------------------------------------  -----------------
1           8           6           2023-11-23T19:05:33.234523Z  [card suit="hearts" rank="5"][player name="bill"]  a card was played
```

Great! We got our logs into our own table with the fields we needed. But what
if we need even MORE control over the insertion? There's one more level of
customization that you can use to get Stumpless to suit your needs.


# Custom Prepared SQL Statements
There are some scenarios where just adjusting the insert SQL statement isn't
enough. If you need to execute multiple statements or perform your own logic on
the entry's data before making the insertion, you'll need more control over what
happens to make the insertion.

`stumpless_set_sqlite3_prepare` gives you a way to do this within a SQLite
target. You provide a function that take the entry and returns a number of
prepared statements to execute. When setting up, you can also provide a pointer
to anything you'd like, since you might need some extra information to create
the statements.

For this example, we'll break our relational database into a couple of tables.
When new entries come in, we'll pull out the structured data and put it into the
appropriate columns, so that it's easier to work with using standard SQL
methods. We'll also add a table that maintains some game state, and update this
whenever a card is played.

Our two new tables look like this:

```sql
CREATE TABLE played_cards (
  played_card_id INTEGER PRIMARY KEY,
  suit TEXT,
  rank TEXT
);

CREATE TABLE taken_turns (
  taken_turn_id INTEGER PRIMARY KEY,
  player_name TEXT
);
```

Custom prepare functions take three parameters: the entry to log, a pointer to
a data structure supplied when the function is set, and a pointer to a counter
where the number of prepared statements is written. The function returns a
pointer to an array of prepared statement pointers, or NULL if something went
wrong.

Our custom function will prepare two insert statements, one for each of our
tables. An abbreviated version looks like this (see `sqlite3_example.c` for
the full version).

```c
static sqlite3_stmt *card_stmts[2] = { NULL, NULL };

void *
card_played_prepare( const struct stumpless_entry *entry,
                     void *data,
                     size_t *count ) {
  sqlite3 *db = data;
  const char *card_insert_sql = "INSERT INTO played_cards ( suit, rank ) "
                                "VALUES ( $suite, $rank )";
  const char *player_insert_sql = "INSERT INTO taken_turns ( player_name ) "
                                  "VALUES ( $name )";
  const char *suit;
  const char *rank;
  const char *name;

  sqlite3_prepare_v2( db, card_insert_sql, -1, &card_stmts[0], NULL );
  sqlite3_prepare_v2( db, player_insert_sql, -1, &card_stmts[1], NULL );

  suit = stumpless_get_entry_param_value_by_name( entry, "card", "suit" );
  rank = stumpless_get_entry_param_value_by_name( entry, "card", "rank" );
  name = stumpless_get_entry_param_value_by_name( entry, "player", "name" );

  sqlite3_bind_text( card_stmts[0], 1, suit, -1, SQLITE_TRANSIENT );
  sqlite3_bind_text( card_stmts[0], 2, rank, -1, SQLITE_TRANSIENT );
  sqlite3_bind_text( card_stmts[1], 1, name, -1, SQLITE_TRANSIENT );

  free( ( char * ) suit );
  free( ( char * ) rank );
  free( ( char * ) name );

  *count = 2;
  return &card_stmts;
}
```

Setting this function to be used is almost trivial. Let's also send the same
entry as before so that we can see the new behavior.

```c
stumpless_set_sqlite3_prepare( db_target, &card_played_prepare, db );
stumpless_add_entry( db_target, entry );
```

And finally, a peek into the database to make sure everything is as we expect.

```
$ sqlite3 -header -column stumpless_example.sqlite3
SQLite version 3.22.0 2018-01-22 18:45:57
Enter ".help" for usage hints.
sqlite> SELECT * FROM played_cards;
played_card_id  suit        rank
--------------  ----------  ----------
1               hearts      5
sqlite> SELECT * FROM taken_turns;
taken_turn_id  player_name
-------------  -----------
1              bill
```

That's it!

One important thing to note about this last style of insertion is that it
requires you to have the SQLite headers and library linked against your own
executable. You'll want to make sure that you have the same version of SQLite
that Stumpless is configured with, or you could run into strange issues!

This is especially relevant if you've compiled Stumpless by directly embedding
SQLite into it via the `SQLITE3_SRC_PATH` CMake variable. Doing this and then
writing a separate prepare function in your own code will mean that SQLite will
be built in two separate places: in Stumpless itself and in your code. This
means that there will also be different static variable locations, and could
cause serious problems if a single database handle is shared between these two
SQLite instances. A good rule of thumb to avoid these issues is to dynamically
link SQLite to Stumpless and your own code if you're going this route.

If you need more control than this, you're probably better off writing your own
SQLite code to do insertions, and handing this to a function target to invoke it
when entries are added. Check out the [function target](../function/README.md)
example if you want to see what setting up a custom function target is like
(spoiler: it's easy).
