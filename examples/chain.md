# Chain Targets
Stumpless offers a lot of targets for different types of logging. These targets
are all carefully confined to a single endpoint though - you can't easily create
a target that will send log messages to multiple places. For example a file
target that logs to two files isn't possible.

Instead of manually sending messages to each desired target, you can instead use
a chain to compose several different targets together. Log entries sent to the
chain will be sent to each of the targets within, allowing for a sequence of
targets that can simplify the logging calls in your own application.

The interface for chain targets themselves is simple but effective. Chains can
be nested within one another, and when combined with other features such as
filters can be used to create relatively complex logging chains.


## A Simple Sequence
Making a basic chain with just a few targets is straightforward. First, create
the chain, and then add the targets you want to be included.

First, let's make our targets for the chain. We'll start with a simple model
where we send messages to both a file and stdout.

```c
file_target = stumpless_open_file_target( "chain-example.log" );
stdout_target = stumpless_open_stdout_target( "chain-example-stdout" );
```

Next, let's apply a filter so that the output on the console doesn't get too
overwhelming. We'll apply a mask so that messages lower than info severity
aren't printed out, as well as messages of the highest severity since
we will handle those differently. If you want to see more about how to use
masks to filter messages, check out the [filter example](../filter/README.md).

```c
mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_INFO )
         & ~STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
stumpless_set_target_mask( stdout_target, mask );
```

Now for the main event: making the chain itself! It's pretty straightforward.

```c
// create a new chain
simple_chain = stumpless_new_chain( "example-simple-chain" );

// add our targets to the chain
stumpless_add_target_to_chain( simple_chain, stdout_target );
stumpless_add_target_to_chain( simple_chain, file_target );
```

Sending messages to this chain is also simple: we just treat it the same as any
other target! This will create an entry in the file, as well print an entry to
stdout.

```c
stumpless_add_message( simple_chain, "simple chain message" );
```


## Nesting Chains
Chains also allow us to create hierarchical logging structures. To do this, we
add chains to other chains, applying filters along the way to control message
flow down to lower levels.

To show this, we'll create two more chains. First, an error chain that will
send high-level errors to stderr, as well as to a log buffer where we can
investigate them in our application later.

```c
stderr_target = stumpless_open_stderr_target( "chain-example-stderr" );
error_buffer_target = stumpless_open_buffer_target( "chain-example-buffer",
                                                    error_buffer,
                                                    sizeof( error_buffer ) );
error_chain = stumpless_new_chain( "example-error-chain" );
stumpless_add_target_to_chain( error_chain, stderr_target );
stumpless_add_target_to_chain( error_chain, error_buffer_target );
mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
stumpless_set_target_mask( error_chain, mask );
```

Next, we create a top-level chain, and put our previous two chains into it. This
is the chain that we'll use as our actual logging target.

```c
main_chain = stumpless_new_chain( "example-main-chain" );
stumpless_add_target_to_chain( main_chain, error_chain );
stumpless_add_target_to_chain( main_chain, simple_chain );
```

Now lets send some messages through the chain.

```c
stump_em( "emergency!" );
stump_a( "alert!" );
stump_c( "critical!" );
stump_er( "error!" );
stump_w( "warning..." );
stump_n( "notice" );
stump_i( "informational" );
stump_d( "debug" );
stump_d( "trace" );
```

When we run this program, we see the following output. If you have special
highlighting rules or other handling for `stderr` you'll see the difference
between messages that were sent to it instead of standard output, but you may
not otherwise.

```
# these messages are sent to stderr
<8>1 2024-03-27T12:11:05.815725Z Angus - - - - emergency!
<9>1 2024-03-27T12:11:05.815734Z Angus - - - - alert!
<10>1 2024-03-27T12:11:05.815741Z Angus - - - - critical!
<11>1 2024-03-27T12:11:05.815748Z Angus - - - - error!

# and these appear on stdout
<12>1 2024-03-27T12:11:05.815755Z Angus - - - - warning...
<13>1 2024-03-27T12:11:05.815760Z Angus - - - - notice
<14>1 2024-03-27T12:11:05.815765Z Angus - - - - informational

# note that debug messages are missing, since they were filtered from stdout
```

All of the messages appear in our file, including the debug information:

```
<8>1 2024-03-27T12:11:05.815732Z Angus - - - - emergency!
<9>1 2024-03-27T12:11:05.815739Z Angus - - - - alert!
<10>1 2024-03-27T12:11:05.815746Z Angus - - - - critical!
<11>1 2024-03-27T12:11:05.815753Z Angus - - - - error!
<12>1 2024-03-27T12:11:05.815758Z Angus - - - - warning...
<13>1 2024-03-27T12:11:05.815763Z Angus - - - - notice
<14>1 2024-03-27T12:11:05.815768Z Angus - - - - informational
<15>1 2024-03-27T12:11:05.815770Z Angus - - - - debug
<15>1 2024-03-27T12:11:05.815773Z Angus - - - [trace file="stumpless/docs/examples/chain/chain_example.c" line="84" function="main"] trace
```

And finally, let's run a check on the contents of our error buffer, to see
if there's anything that we need to know about.

```c
printf( "\nerrors logged in memory:\n" );
do {
  read_size = stumpless_read_buffer( error_buffer_target,
                                     message_buffer,
                                     sizeof( message_buffer ) );
  printf( "%s\n", message_buffer );
} while( read_size > 1 );
```

This portion of the output looks like this:

```
errors logged in memory:
<8>1 2024-03-27T12:11:05.815730Z Angus - - - - emergency!
<9>1 2024-03-27T12:11:05.815737Z Angus - - - - alert!
<10>1 2024-03-27T12:11:05.815744Z Angus - - - - critical!
<11>1 2024-03-27T12:11:05.815751Z Angus - - - - error!
```

Finally, we need to clean up. Chains make this pretty easy, providing a
destructor to close all targets within them as well (including other chains).
If you'd rather only close the chain, use `stumpless_close_chain_only` instead.

```c
stumpless_close_chain_and_contents( main_chain );
stumpless_free_all(  );
```
