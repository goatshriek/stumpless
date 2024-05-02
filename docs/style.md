# Stumpless Coding Style
Stumpless follows a fairly straightforward style, although it is not a
well-known one such as the K&R standard. Because the formatting in the code base
is admittedly not common and even inconsistent in some places, there will be
some leniency in changes that do not follow it perfectly. This is up to the pull
request reviewer's discretion.

Here are a few other style points to follow in the code base:

 * **No `#ifdef` directives are allowed in source (`.c`) files.**
   Source code with preprocessor directives that add, alter, or remove
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

 * **`stumpless_` prefix** Functions and types that are provided by the library
   almost all begin with `stumpless_` to minimize namespace conflicts with users
   of the library. There are a few exceptions to this rule (like `stump` and
   `stumplog`), but in general if you are creating a new public-facing function
   then it should start with this prefix.
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
 * **`unchecked_` prefix** Some functions start with `unchecked_` to mark that
   they do not perform any checks on their arguments. These allow callers to
   avoid NULL checks and other checks that would be redundant because they have
   already been performed elsewhere. Of course, the caller needs to make sure
   that they do any necessary checks before calling these.
 * **`_w` suffix** Functions with a `_w` at the end have arguments that are wide
   character strings in UTF-16 encoding, instead of the UTF-8 multibyte strings
   that are standard for arguments. These functions are provided to ease use in
   Windows environments, where wide strings may be the standard instead of
   multibyte. The suffix is similar to the 'A' vs. 'W' suffixes applied to
   Windows functions to delineate ASCII vs. wide string arguments. Keep in mind
   that this is different though; stumpless uses multibyte strings otherwise,
   not just ASCII!
 * **`_str` suffix** For functions that support format specifiers, there may
   also be a version with `_str` added to the end. These functions are the same
   as the format specifier version, but don't support format specifiers and
   instead take a single string. `_str` functions require less parsing and have
   fewer security concerns, and so should be used whenever possible over the
   format specifier version.
 * **`new` constructors and `destroy` destructors** Constructors with "new" in
   the name, such as `stumpless_new_entry`, allocate the memory for a new
   structure and return it after initializing it. Structures created this way
   should be destroyed using the "destroy" destructors, which deallocate any
   memory needed to, such as `stumpless_destroy_entry_and_contents`.
 * **`load` constructors and `unload` destructors** Constructors with "load" in
   the name do the same setup as the "new" constructors, but instead of
   dynamically allocating memory for the structure they populate a structure
   provided as a parameter. These are often faster, as they use fewer dynamic
   memory allocation routines. Structures initialized this way must be
   destroyed using the "unload" destructors. One such pair of functions is
   `stumpless_load_entry` and `stumpless_unload_entry`.
 * **`open` constructors** Functions that use "open" instead of "new" or "load"
   do the same as a "new" constructor, but also move them to an opened state.
   Currently, only network targets may be in a state other than open, if the
   connection with the log endpoint is not active.
