# Changelog
All notable changes to stumpless will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

For a detailed look at the project's future, including planned features and bug
fixes, check out the
[roadmap](https://github.com/goatshriek/stumpless/blob/master/docs/roadmap.md).


## [3.0.0] - 2024-11-28
### Added
 - Colorization of output in stream targets via ANSI color codes, along with
   supporting functions `stumpless_set_severity_color`.
 - Memory allocation function accessors:
    * `stumpless_get_free`
    * `stumpless_get_malloc`
    * `stumpless_get_realloc`
 - Other new functions:
    * `stumpless_get_priority_string`
 - `BUILD_TESTING` Cmake option controls the building of functionality and
   thread safety tests (default is ON).
 - `BUILD_BENCHMARKING` CMake option controls the building of the performance
   tests (default is OFF).

### Changed
 - Refactor:
   * `stumpless_param_to_string`
   * `stumpless_param_into_string`
   * `stumpless_element_to_string`
 - Update localization for French (fr-FR :fr:)
 - `ENABLE_CPP` CMake option has been renamed to `BUILD_CPP` to align with other
   build options for shared libraries and testing.
 - C++ is no longer required to build the project if testing and benchmarking
   are disabled.

### Fixed
 - Strings that are a case-insensitive prefix of a valid severity string are
   no longer accepted by severity from string functions.
 - Memory leak in slab cache expansion.
 - Use `SO_NOSIGPIPE` where `MSG_NOSIGNAL` is not defined.

### Removed
 - `stumpless/priority.h`, which was merged into `stumpless/prival.h`.
 - `export-gtest` and `export-benchmark` CMake targets, and the related
   `GTEST_PATH` and `BENCHMARK_PATH` CMake options. These libraries are now
   provided using CMake `FetchContent` with `FIND_PACKAGE_ARGS` to search for
   an existing installation.


## [2.2.0] - 2024-05-26
### Added 
 - @since format check enforcement in CI pipeline.
 - `single-file` target for rollup `.c` and `.h` files.
 - SQLite3 logging targets.
 - Target chains.
 - Support for `pkg-config`.
 - `INSTALL_HEADERS` and `INSTALL_HTML` build options.
 - Localizations for:
    * Albanian (sq-AL :albania:)
    * Danish (da-DK :denmark:)
    * Hebrew (he-IL :israel:)
    * Hungarian (hu-HU :hungary:)
    * Japanese (ja-JP :jp:)
    * Sinhala (si-LK :sri_lanka_:)
    * Swahili (sw-KE :kenya:)
    * Teluga (te-IN :india:)
    * Turkish (tr-TR :tr:)

### Fixed
 - Deadlock potential in `stumpless_set_entry_hostname` and
   `stumpless_set_entry_procid` when validation fails.
 - Builds in ANSI C environments.
 - `sys/socket.h`-based TCP network targets will immediately fail with an error
   if the remote end sends a FIN message, instead of waiting for `send` to fail,
   possibly sending messages that are not actually received by the remote end.


## [2.1.0] - 2022-11-13
### Added
 - Custom function logging targets.
 - Localizations for:
    * Bengali (bn-IN :india:)
    * Chinese (zh-CN :cn:)
    * Czech (cz-CZ :czech_republic:)
    * Hindi (hi-IN :india:)
    * Polish (pl-PL :poland:)
    * Portuguese (pt-BR :brazil:)
    * Spanish (es-ES :es:)
 - Systemd journal logging targets (journald).
 - Log source file tracing functions:
    * `stump_trace`
    * `stumpless_trace_entry`
    * `stumpless_trace_log`
    * `stumpless_trace_message`
    * `stumplog_trace`
    * `vstump_trace`
    * `vstumpless_trace_log`
    * `vstumpless_trace_message`
    * `vstumplog_trace`
 - The TRACE log level severity shorthand function macros:
    * `stump_t`
    * `stump_t_entry`
    * `stump_t_log`
    * `stump_t_message`
    * `stumplog_t`
 - Macro `STUMPLESS_SEVERITY_TRACE_VALUE` as an alias for
   `STUMPLESS_SEVERITY_DEBUG_VALUE`.
 - Macro `STUMPLESS_SEVERITY_TRACE` for the new level as an alias for
   the `STUMPLESS_SEVERITY_DEBUG` enum member.
 - Runtime filtering mechanism, as well as default support for log masks, via
   the following functions:
    * `stumpless_get_target_filter`
    * `stumpless_get_target_mask`
    * `stumpless_mask_filter`
    * `stumpless_set_target_filter`
    * `stumpless_set_target_mask`
    * `stumplog_set_mask`
 - Safer and more performant `_str` versions of any function taking a format
   specifier string and variable number of arguments.
 - Default Windows Event Log messages that can be used when none are specified.
 - Full unicode support with Windows Event Log targets, along with the following
   new functions:
    * `stumpless_add_default_wel_event_source`
    * `stumpless_add_wel_event_source`
    * `stumpless_add_wel_event_source_w`
    * `stumpless_get_wel_category`
    * `stumpless_get_wel_event_id`
    * `stumpless_get_wel_insertion_param`
    * `stumpless_get_wel_insertion_string_w`
    * `stumpless_get_wel_type`
    * `stumpless_remove_default_wel_event_source`
    * `stumpless_remove_wel_event_source`
    * `stumpless_remove_wel_event_source_w`
    * `stumpless_set_wel_insertion_string_w`
    * `stumpless_set_wel_insertion_strings_w`
    * `vstumpless_set_wel_insertion_strings_w`
 - `STUMPLESS_OPTION_CONS` is now supported with similar semantics to `LOG_CONS`
   from `syslog.h`.
 - The procid and hostname can be overriden if the defaults are not wanted, via
   the functions:
    * `stumpless_get_entry_hostname`
    * `stumpless_get_entry_procid`
    * `stumpless_set_entry_hostname`
    * `stumpless_set_entry_procid`
 - Other new functions:
    * `stumpless_get_network_protocol`
    * `stumpless_get_target_type_string`
    * `stumpless_get_transport_protocol`

### Changed
 - Auto-generated local socket names use abstract socket names if supported.
 - Auto-generated local socket names are always `stumpless-socket` instead of
   being generated using `mkstemp`.

### Fixed
 - `stumpless_perror` segmentation faults after the following errors:
    * `STUMPLESS_FILE_OPEN_ERROR`
    * `STUMPLESS_FILE_WRITE_ERROR`
    * `STUMPLESS_INVALID_ID`
    * `STUMPLESS_MEMORY_ALLOCATION_FAILURE`
    * `STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED`
    * `STUMPLESS_STREAM_WRITE_FAILURE`
    * `STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED`
    * `STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE`
    * `STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE`
 - Several memory leaks:
    * Object cache leak in some allocation failure scenarios
    * Creating network target with unsupported protocols
 - `close` syscall is no longer called on invalid socket handles
 - TCP network targets do not hang when the session is closed by the receiver.

## [2.0.0] - 2020-12-27
### Added
 - Localization framework for error messages and other library strings, and
   localizations for:
    * French (fr-FR :fr:)
    * German (de-DE :de:)
    * Italian (it-IT :it:)
    * Slovak (sk-SK :slovakia:)
    * Swedish (sv-SE :sweden:)
 - Thread safety for all functionality.
 - The following functions:
    * `stumpless_free_thread`
    * `stumpless_get_element_count`
    * `stumpless_get_target_name`
    * `stumpless_get_target_default_app_name`
    * `stumpless_get_target_default_msgid`
    * `stumpless_param_to_string`
    * `stumpless_read_buffer`
  - The following C++ function bindings:
    * `Entry.GetAppName`
    * `Entry.GetMessage`
    * `Entry.GetMsgid`
    * `Version.Compare`

### Changed
 - C++ namespace from `stumplesscpp` to `stumpless`.
 - Including `stumpless/config.h` no longer defines `WIN32_LEAN_AND_MEAN`.
 - Facilities, options, and severities are now only available in the
   `stumpless/facility.h`, `stumpless/option.h`, and `stumpless/severity.h`
   headers, respectively.
 - Functions that return strings now require the caller to free the string
   when it is no longer needed. Prior to this version these strings pointed
   to internal character buffers that could not be modified. The functions
   affected by this are:
    * `stumpless_get_element_name`
    * `stumpless_get_entry_app_name`
    * `stumpless_get_entry_message`
    * `stumpless_get_entry_msgid`
    * `stumpless_get_entry_param_value_by_index`
    * `stumpless_get_entry_param_value_by_name`
    * `stumpless_get_param_name`
    * `stumpless_get_param_name_by_index`
    * `stumpless_get_param_value`
    * `stumpless_get_param_value_by_index`
    * `stumpless_get_param_value_by_name`
 - The underlying buffer in buffer targets should no longer be read manually,
   but should instead use the new `stumpless_read_buffer` function as the only
   way to read messages.
 - All target open functions no longer require an options or default facility
   parameter, resulting in much more concise code. If either of these fields
   need to be adjusted on a target, use the `stumpless_set_option` and
   `stumpless_set_default_facility` functions after the target has been
   created.
 - Facilities and severities are now `enum`s instead of preprocessor symbols.

### Deprecated
 - `stumpless_destroy_entry` has been deprecated in favor of the more
   descriptive and deliberate `stumpless_destroy_entry_and_contents` and
   `stumpless_destroy_entry_only` functions in order to avoid unintentional
   memory leaks and use-after-free mistakes.
 - `stumpless_destroy_element` has been deprecated in favor of the more
   descriptive and deliberate `stumpless_destroy_element_and_contents` and
   `stumpless_destroy_element_only` functions in order to avoid
   unintentional memory leaks and use-after-free mistakes.

### Fixed
 - Memory leak in opening of network targets on systems using `sys/socket.h`
   for network services.

### Removed
 - `stumpless` and `vstumpless` functions (use `stump` and `vstump` instead).
 - `STUMPLESS_SEVERITY_WARN` symbol.

## [1.6.0] - 2020-07-16
### Added
 - A number of new functions for working with entries, elements, and params.
 - A rollup header, `stumpless.hpp`, for the C++ library to make use easier.
 - Logging functions that can be removed at compile time.

### Fixed
 - Added missing DLL exports of C++ library in standard Visual Studio builds.
 - Local socket names are generated using mkstemp instead of using a static
   counter ([issue #54](https://github.com/goatshriek/stumpless/issues/54)]).
 - The current target is not left pointing at an invalid target structure
   after the current target is closed
   ([issue #52](https://github.com/goatshriek/stumpless/issues/52)).

## [1.5.0] - 2020-05-19
### Added
 - `stumpless_version_to_string` function.
 - Header check enforcement in CI pipeline.
 - C++ library bindings generated by Wrapture.

### Fixed
 - Several portability issues:
   - Build failure in MinGW and Cygwin
   - Conflicting header inclusions
   - Missing headers
   - Missed code in configuration-specific source files
   - Missing error checks

## [1.4.0] - 2019-03-09
### Added
 - Format specifier support for messages and entries.
 - Generic stumpless_close_target function.
 - Example and documentation of file targets.
 - Example and documentation of socket targets.
 - Functions that can replace syslog and vsyslog (stumplog and vstumplog).
 - Default targets specific to the platform.

### Fixed
 - Memory leak where error structures are not freed by stumpless_free_all.
 - Missing error generation for socket logging.

### Changed
 - Network examples are no longer run by the examples build target.

## [1.3.1] - 2019-02-15
### Fixed
 - Code duplication in network target code.

## [1.3.0] - 2019-02-14
### Added
 - Install target and documentation.
 - Memory leak controlled with stumpless_free_all function.
 - Vision statement.
 - STUMPLESS_OPTION_NONE for code readability.
 - stumpless_perror function.
 - Network target capability.

### Fixed
 - Various memory leaks.

## [1.2.0] - 2018-11-09
### Added
 - Increased coverage on object cache.
 - Support for fractional timestamps.
 - File target capability.
 - Windows Event Log target capability.
 - Doxygen documentation support.
 - Tests for unsupported targets.
 - Stream target capability.

### Fixed
 - Use of unsafe fopen when fopen_s is available.
 - Use of unsafe gmtime function when gmtime_r is available.
 - Safely convert from size_t to int types.
 - Inclusion of RFC 5424 test sources in multiple executables, using an object
   library instead.

## [1.1.2] - 2018-10-04
### Fixed
 - Specify googletest release 1.8.1 to fix broken builds.

## [1.1.1] - 2018-08-28
### Added
 - Add SonarCloud quality gate badge to README.

## [1.1.0] - 2018-08-27
### Added
 - Benchmark tests measure the amount of memory allocated.
 - Add `stumpless_set_entry_message` function.
 - Integration with SonarCloud for analysis.

### Fixed
 - Removed versions prior to 1.0.0 to match repository history.
 - Benchmark tests now function properly.
 - Memory efficiency improved significantly.

## [1.0.0] - 2018-07-28
### Added
 - Add socket target capability.
 - Add buffer target capability.
 - Add Travis CI integration.
 - Add AppVeyor integration.
 - Add Google Test suites.
 - Add Google Benchmark capability.
