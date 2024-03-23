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


# Simple Sequence
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
         & ~STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ALERT );
stumpless_set_target_mask( stdout_target, mask );
```

Now for the main event: making the chain itself! It's pretty straightforward.

```c
simple_chain = stumpless_new_chain( "example-chain" );
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
Chains also allow us to create hierarchical logging structures, similar to those
that other frameworks provide. To do this, we add chains to other chains,
applying filters along the way to control message flow down to lower levels.

To show this, we'll create two more chains. First, an error chain that will
send the high-level errors we filtered off of stdout to stderr instead, as well
as to a log buffer where we can investigate them in our application later if we
need to.
