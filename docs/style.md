# Stumpless Coding Style
Stumpless follows a fairly straightforward style, although it is not a
well-known one such as the K&R standard. Because the formatting in the code base
is admittedly not common, there will be some leniency in changes that do not
follow it perfectly. This is up to the pull request reviewer's discretion.

If you are not sure about a formatting choice, you can simply run the GNU indent
wrapper available in `scripts/indent.sh` to format your changes. Note that you
will need to make sure that this does not introduce changes to parts of the
source file that you did not change. `indent` will save the original file as the
original with a `~` character at the end if you need to go back, or you can use
the git history.

Here are a few other style points to follow in the code base:

 * **No `#ifdef` directives are allowed in source (`.c`) files.**
   Source code with preprocesor directives that add, alter, or remove
   functionality are easy to add, but scatter configuration-specific behavior
   and build environment dependencies across source files, and make it harder to
   understand program flow. These snippets should instead be factored into
   separate config source modules that keep portability handling code away from
   other logic and easy to find, understand, and modify. See the
   [portability guide](portability.md) for more context on this decision and how
   to work within the limitation.
 * **Spaces are used for indentation (2 per indent level).**
   We recognize that there are many a heated conversation that can be had about
   the "tabs vs. spaces" war. Please respect this project's chosen convention
   and avoid the use of tabs.
 * **Alphabetize items in sections** Functions in header files and test cases
   are the big items here. There are cases where alphabetization makes something
   less clear than some other order, and in those cases it's of course fine to
   use the clearer order instead. But always default to inserting things in
   alphabetical order unless there is some reason to do otherwise.


## Naming Conventions
There are a few standard prefixes, suffixes, and other naming standards that
are followed in the functions and variables in the source code. Understanding
these will help you follow the logic of code and understand how to choose names
in your own additions.

 * **`config_` prefix** Functions that start with `config_` are dependent on the
   build configuration of the project. They may resolve to a different function
   when built on different platforms or with different flags, but will always
   have the same semantics. See the [portability guide](portability.md) for more
   information on how portability is handled in function and header names.
 * **`locked_` prefix** Functions that start with `locked_` make the assumption
   that some or all of their parameters are protected by holding a mutex before
   they are called. They are not thread safe on their own, so it is up to the
   caller to lock the resources. These are useful when you need to perform an
   operation, but using a thread-safe version would cause deadlock by trying to
   get a mutex that is already held. Often, the version of the function without
   the locked prefix simply acquires the locks, and then calls the `locked_`
   version.
 * **`unchecked_` prefix** Some functions start with `unsafe_` to mark that they
   do not perform any checking on their arguments. These allow callers to avoid
   NULL checks and other checks that would be redundant because the checks have
   already been performed elsewhere. Of course, the caller needs to make sure
   that they do any necessary checks before calling these.
