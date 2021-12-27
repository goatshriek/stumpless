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

