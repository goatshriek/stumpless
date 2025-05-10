option(BUILD_SHARED_LIBS "Build shared libraries" ON)

string(CONCAT build_cpp_help_string
  "Build the C++ language binding library. The library will be added to the "
  "'all' target and will be installed via the 'install' target, alongside the "
  "C library. Other targets (such as 'docs' and 'check') will have a '-cpp' "
  "version that takes the same action for the C++ library. For example, build "
  "the 'check-cpp' target to build and run the test suite for the C++ library."
)
option(BUILD_CPP ${build_cpp_help_string} OFF)
option(BUILD_PYTHON "build the Python language binding libary" OFF)

option(BUILD_BENCHMARKING "build the benchmarking tests" OFF)

option(ENABLE_THREAD_SAFETY "support thread-safe functionality" ON)

option(ENABLE_CHAIN_TARGETS "support chain targets" ON)
option(ENABLE_JOURNALD_TARGETS "support systemd journald service targets" ON)
option(ENABLE_NETWORK_TARGETS "support network targets" ON)
option(ENABLE_SOCKET_TARGETS "support unix domain socket targets" ON)
option(ENABLE_SQLITE3_TARGETS "support sqlite3 targets" ON)
option(ENABLE_WINDOWS_EVENT_LOG_TARGETS "support windows event log targets" ON)

option(INSTALL_EXAMPLES "install examples" ON)
option(INSTALL_HEADERS "install header files" ON)
option(INSTALL_HTML "install html documentation" ON)
option(INSTALL_MANPAGES "install generated manpages" ON)

option(COVERAGE "Include coverage information" OFF)
option(FUZZ "Support fuzzing with libFuzzer" OFF)

string(CONCAT enable_deprecation_warnings_help_string
  "Print warnings to the standard output when deprecated functionality is used."
)
option(ENABLE_DEPRECATION_WARNINGS ${enable_deprecation_warnings_help_string} ON)


# default settings
set(CHAIN_TARGET_ARRAY_LENGTH 4
  CACHE STRING "the chain target static array size"
)

string(CONCAT default_facility_help_string
  "The facility code to use for messages where one is not explicitly provided."
)
set(DEFAULT_FACILITY "STUMPLESS_FACILITY_USER"
  CACHE STRING ${default_facility_help_string}
)

string(CONCAT default_file_help_string
  "The name of the file opened if the default target is to a file."
)
set(DEFAULT_FILE "stumpless-default.log"
  CACHE STRING "${default_file_help_string}"
)

string(CONCAT default_severity_help_string
  "The severity code to use for messages where one is not explicitly provided."
)
set(DEFAULT_SEVERITY "STUMPLESS_SEVERITY_INFO"
  CACHE STRING ${default_severity_help_string}
)

set(FALLBACK_PAGESIZE 4096
  CACHE STRING "the memory page size to use if it cannot be detected at runtime"
)

string(CONCAT sqlite3_src_path_help_string
  "The path to a SQLite3 source file, referred to as an 'amalgamation' in "
  "SQLite documentation. If this variable is set, it is used to link SQLite3 "
  "statically with Stumpless, instead of the default dynamic linking."
)
set(SQLITE3_SRC_PATH ""
  CACHE FILEPATH ${sqlite3_src_path_help_string}
)

string(CONCAT sqlite3_include_path_help_string
  "The path to the sqlite3.h header matching the source file provided in "
  "SQLITE3_SRC_PATH. If the header is already in the include directores, this "
  "does not need to be specified."
)
set(SQLITE3_INCLUDE_PATH ""
  CACHE FILEPATH ${sqlite3_include_path_help_string}
)

set(SQLITE3_DEFAULT_TABLE_NAME "logs"
  CACHE STRING "the name of the table used by default for SQLite3 targets"
)

set(SQLITE3_RETRY_MAX 3
  CACHE STRING "the maximum number of retries on SQLite3 operations"
)

string(CONCAT locale_help_string
  "The locale used for strings passed by the library, for example error "
  "messages. If this is not set it will use the LANG environment variable "
  "of the build system."
)
set(LOCALE $ENV{LANG}
  CACHE STRING ${locale_help_string}
)
