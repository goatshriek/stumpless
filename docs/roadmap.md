# The Future of Stumpless

See below for details about upcoming releases of Stumpless. If you have feedback
or want to make a suggestion, please submit an issue on the project's
[Github page](https://github.com/goatshriek/stumpless).

## 2.0.0 (next major and minor release)
 * [DEPRECATE] **entry and element destructor synonyms**
   Currently, there are two forms of the destructors for these two structures:
   one that destroys the object itself, and one that destroys the object and all
   of the ones that it contains. The former is named `destroy_..._only` while
   the latter is named `destroy_..._and_contents`. The latter has a synonym
   named simply `destroy`, which does not convey its behavior well. This alias
   will be deprecated, and removed in the next major release in order to prevent
   confusion and misuse of the two forms.
 * [CHANGE] **Destructors no longer clear errors**
   As destruction functions do not throw any errors by design, they should not
   clear the error flags. Clearing them can especially cause confusion in other
   language bindings, where the calling of the destructor is not explicit and
   may be difficult to track down.
 - [CHANGE] **Error codes will be guaranteed to be a consistent value**
   Error ids are currently defined by an enumeration without any values
   specified, which means that they could change across builds. Setting these to
   specific values will make them consistent across all builds, increasing
   interoperability.
 * [CHANGE] **Facilities and severities will be defined by enumerations**
   Enumerations are a cleaner way to represent the set values, and can be made
   compatible with the `syslog.h` values if their backing `int` values match.
   Because function signatures will change, this will be done in a major
   release.
 * [DEPRECATE] **Stream target constructor using `int` instead of `Facility`**
   Enumerations are preferred for working with these set values in C++, and this
   function was inadvertently left in the library during development.
 * [REMOVE] **Options and default facility from all target constructors**
   These are typically boilerplate, and if needed can be set with subsequent
   calls. This will allow for less verbose code in most use cases.

## 2.1.0
 * [ADD] **journald logging target**
   Logging to systemd's journal system is should be relatively straightforward
   to implement, and is an important feature to support.
 * [ADD] **Filters**
   While message severity codes can be used to filter which log messages make
   it through a target at runtime, this is limited and inflexible. Instead, a
   generic filter structure that can filter on a wide variety of properties of
   each log entry and even use custom functions to filter messages.

## 3.0.0
 * [REMOVE] **entry and element destructor synonyms**
   Removing previously deprecated feature.
 * [REMOVE] **Stream target constructor using `int` facility**
   Removing previously deprecated feature.
 * [CHANGE] **Python language bindings to Wrapture instead of SWIG**
   The [Wrapture](https://github.com/goatshriek/wrapture) project is being
   built to provide clean, readable, and explicit language binding functionality
   from C to other target languages, specifically to support Stumpless. Once
   Python is added as a target language, this will be utilized to create the
   associated library bindings, replacing SWIG and removing the dependency. In
   the future, other language bindings will be added using Wrapture as they are
   added to the tool.

## Unallocated to a release
 * [ADD] **Ruby language bindings**
 * [ADD] **C# language bindings**
 * [ADD] **TCL language bindings**
 * [ADD] **Java language bindings**
 * [ADD] **Powershell language bindings**
 * [ADD] **Perl language bindings**
 * [ADD] **Function callback logging target**
 * [ADD] **AWS/S3 logging target**
 * [ADD] **Database logging target**
 * [ADD] **REST endpoint logging target**
 * [ADD] **Hyperledger/blockchain logging target**
 * [CHANGE] **Make network logging non-blocking**
 * [ADD] **Target chaining**
   In some cases a log message needs to be sent to multiple destinations, such
   as to a local file as well as a network server. Target chains will allow this
   stream to be defined as a logging target, and a logging call only made to
   this instead of manually logging to each target.
 * [ADD] **Abstract socket support**
   When creating a Unix socket target, an abstract socket name would allow the
   socket to be hidden from the local filesystem. This has currently been left
   out due to portability issues, but using this capability when it is available
   would increase the 'cleanliness' of using socket targets.

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
