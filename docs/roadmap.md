# The Future of Stumpless
See below for details about upcoming releases of Stumpless. If you have feedback
or want to make a suggestion, please submit an issue on the project's
[Github page](https://github.com/goatshriek/stumpless).


## 3.0.0 (next major release)
 * [REMOVE] **entry and element destructor synonyms**
   Removing previously deprecated feature.
 * [REMOVE] **Stream target constructor using `int` facility**
   Removing previously deprecated feature.
 * [REMOVE] **entry id field**
   Removing unused field.
 * [CHANGE] **Python language bindings to Wrapture instead of SWIG**
   The [Wrapture](https://github.com/goatshriek/wrapture) project is being
   built to provide clean, readable, and explicit language binding functionality
   from C to other target languages, specifically to support Stumpless. Once
   Python is added as a target language, this will be utilized to create the
   associated library bindings, replacing SWIG and removing the dependency. In
   the future, other language bindings will be added using Wrapture as they are
   added to the tool.
 * [CHANGE] **Implement asynchronous logging modes**
   Asynchronous logging can provide significantly less latency to the calling
   application. This will provide more benefit to some targets than others,
   most notably network-based targets. Because some error reporting mechanisms
   may need to change to accomodate this, it will be done in a major release.
 * [CHANGE] **Error enum values start from 1 instead of 0**
   This will allow function that return negative integers in error scenarios to
   pass along a more meaningful return value.
 * [CHANGE] **Entry app name and msgid no longer NULL-terminated.**
   Improve efficiency and memory safety by only using these as byte buffers.
 * [CHANGE] **Rename `STUMPLESS_DEFAULT_TRANSPORT_PORT`**
   This symbol will be renamed so that it is clear that it refers to a string
   literal, likely by adding a `_STR` suffix.
 * [CHANGE] **`const` usage will be reviewed**
   Some functions currently have `const` specified for parameters where this is
   not strictly true. This will be reviewed and removed throughout the code,
   for both public and private functions.
 * [CHANGE] **Target names will be optional and not part of construction.**
   This will remove unnecessary parameters when names are not needed, and
   separate names from functional needs like filenames. A way to retrieve
   targets by name will be included in this change as well.
 * [CHANGE] **CMake version requirement increase.**
   In order to clean up the CMake scripts and avoid deprecation warnings, the
   required version of CMake will change in this release to a minimum of 3.11.
   The requirement minimum version may be even higher after the actual
   implementation of this change.
 * [ADD] **Runtime localization support.**
   The ability to choose the language used at runtime could be especially useful
   in distributed builds, where the same binary may be used in very different
   locations, and doing a specific build would be inconvenient.
 * [ADD] **`mark` struct for specific instances of an entry.**
   This will allow for more efficient use and passing of formatted fields, and
   also allow for a single timestamp when sending an entry through a chain of
   targets.


## Unallocated to a release
 * [ADD] **Ruby language bindings**
 * [ADD] **C# language bindings**
 * [ADD] **TCL language bindings**
 * [ADD] **Java language bindings**
 * [ADD] **Powershell language bindings**
 * [ADD] **Perl/Raku language bindings**
 * [ADD] **Crystal language bindings**
 * [ADD] **AWS/S3 logging target**
 * [ADD] **REST endpoint logging target**
 * [ADD] **Hyperledger/blockchain logging target**
 * [ADD] **Apache Kafka logging target**
 * [ADD] **Ability to limit the rate of logging (per message, per byte)**
 * [ADD] **Logging target for Windows Debug log**
 * [ADD] **Error callbacks**
   Allow the user to define actions to take when specific errors are
   encountered.
 * [ADD] **Configuration file support**
   Many other logging solutions provide a way to configure logging via a
   separate configuration file that defines targets and their options. Stumpless
   will likely not implement it's own format, but rather add the ability to load
   the configuration files from other such tools to provide equivalent
   capabilities. This will also need to include an ability to retrieve a target
   by name, enforce uniqueness of names, and include other changes that require
   it to be done in a major release.


## What you'll find here and what you wont
Stumpless is under active development, and has a long list of new features and
improvements waiting to be implemented. Some of these are detailed in the issues
list on the project Github website, but this is certainly not a comprehensive
list of planned updates. Similarly, work that is in progress on new features is
tracked as a project on the Github repository, but future planned work does not
exist there either. Instead, the plans for future direction are kept here, in
the project roadmap.

Items are added to the roadmap once they have been identified, assessed for
level of effort, and prioritized based on community needs. Each item is assigned
to a semantic version, along with its change type, a description, and the
reasoning behind it. Where they exist, you will see references to issues on the
Github repository where you can go for more details on the origin of the
request. Once a version is in work, you will be able to find a corresponding
project on the Github repository with each roadmap item listed as a task. Once
all tasks are complete, the version will be released and the next started.

Once an item has been implemented it will be removed from the roadmap. If you
would like to see a history of changes on the existing codebase, check out the
ChangeLog (ChangeLog.md in the project root) to see what was included in each
version of the library. In most cases, roadmap items will be removed from this
document and placed there upon completion.

Note that the timelines associated with each change are vague at best. The
project team is not currently big enough to realistically make any promises, so
timing is often left out to prevent folks from feeling cheated if something
takes longer than expected.


## A Note about Github issues and projects
A fair question to ask is why the roadmap is not being managed within the issue
and project features of Github itself, since this is where the project is
currently hosted. Indeed, suggestions submitted by the community are tracked as
issues, and projects are already created for ongoing work. There are a few
reasons that a separate roadmap is maintained:
 * **Issues are used to exclusively track bugs and community requests.**
   This certainly isn't a hard and fast rule, and isn't followed by many other
   projects, but it is how Wrapture is managed. Keeping the issue count as a
   clear indicator of known problems and community requests lets the project
   maintainers (and anyone interested in looking at how well it is being
   maintained) immediately see how much outstanding work exists. Of course,
   the roadmap may have features requested by the community or enhancements made
   clear by bug reports, but it will also have a number of features and tweaks
   that have a lower priority.
 * **Project direction should come packaged with the product.**
   Again this isn't a commonly followed rule, but it is one that the project
   author follows. Anyone that obtains the source code of the project at a
   single point in time should be able to quickly see the current direction of
   the project. Maintaining the roadmap within the version control of the source
   itself facilitates this, the same way that licensing and copyright
   notifications are traditionally bundled with code. And if you don't care,
   you can always ignore them.
