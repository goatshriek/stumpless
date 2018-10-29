# Changelog
All notable changes to stumpless will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased
 - Network target capability.
 - Compile-time log level filtering.
 - Format-string style logging from `stumpless` call.
 - Thread-safe operation.

## [1.2.0] - 2018-10-26
### Added
 - Increased coverage on object cache.
 - Support for fractional timestamps.
 - File target capability.
 - Windows Event Log target capability.

### Removed
 - Use of unsafe gmtime function.

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
