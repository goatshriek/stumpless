# Changelog
All notable changes to stumpless will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased
 - Add file target capability.
 - Add windows event log target capability.

## [1.0.0] - 2018-07-22
### Added
 - Add `stumpless_set_realloc` function.

### Changed
 - Added local socket parameter to `stumpless_open_socket_target` function.

### Fixed
 - Targets are now removed and their memory freed upon closure.
 - Buffer targets now properly advance to write to the next available portion of
   the buffer instead of overwriting previous messages.
 - The `test/function` README is now accurate.

## [0.1.0] - 2018-07-08
### Added
 - Add socket target capability.
 - Add buffer target capability.
 - Add Travis CI integration.
 - Add AppVeyor integration.
 - Add Google Test suites.
 - Add Google Benchmark capability.
