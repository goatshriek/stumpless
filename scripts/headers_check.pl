#!/usr/bin/perl

use Term::ANSIColor;
use strict;
use warnings;

my $file = $ARGV[0];
open(SOURCE, $file) or die("could not open file: $file");

my %manifest = (
  "AF_UNIX" => "sys/socket.h",
  "alloc_mem" => "private/memory.h",
  "ASSERT_THAT" => "gmock/gmock.h",
  "ASSERT_TRUE" => "gtest/gtest.h",
  "BENCHMARK" => "benchmark/benchmark.h",
  "BENCHMARK_MAIN" => "benchmark/benchmark.h",
  "BOOL" => "windows.h",
  "cache_alloc" => "private/cache.h",
  "cache_free" => "private/cache.h",
  "cache_new" => "private/cache.h",
  "clear_error" => "private/error.h",
  "clock" => "time.h",
  "clock_t" => "sys/types.h",
  "CLOCKS_PER_SEC" => "time.h",
  "close" => "unistd.h",
  "config_destroy_insertion_strings" => "private/config/wrapper.h",
  "config_gethostname" => "private/config/wrapper.h",
  "config_getpagesize" => "private/config/wrapper.h",
  "config_get_now" => "private/config/wrapper.h",
  "config_initialize_insertion_strings" => "private/config/wrapper.h",
  "config_send_entry_to_wel_target" => "private/config/wrapper.h",
  "config_sendto_socket_target" => "private/config/wrapper.h",
  "config_set_entry_wel_type" => "private/config/wrapper.h",
  "cstring_to_sized_string" => "private/strhelper.h",
  "destroy_buffer_target" => "private/target/buffer.h",
  "destroy_file_target" => "private/target/file.h",
  "destroy_insertion_strings" => "private/config/wel_supported.h",
  "destroy_socket_target" => "private/target/socket.h",
  "destroy_target" => "private/target.h",
  "destroy_wel_target" => "private/target/wel.h",
  "DWORD" => "windows.h",
  "EVENTLOG_ERROR_TYPE" => "windows.h",
  "EVENTLOG_INFORMATION_TYPE" => "windows.h",
  "EVENTLOG_SUCCESS" => "windows.h",
  "EVENTLOG_WARNING_TYPE" => "windows.h",
  "EXIT_FAILURE" => "stdlib.h",
  "EXIT_SUCCESS" => "stdlib.h",
  "FAIL" => "gtest/gtest.h",
  "fclose" => "stdio.h",
  "FILE" => "stdio.h",
  "fopen" => "stdio.h",
  "format_entry" => "private/formatter.h",
  "fprintf" => "stdio.h",
  "free" => "stdlib.h",
  "free_mem" => "private/memory.h",
  "fwrite" => "stdio.h",
  "get_facility" => "private/entry.h",
  "get_paged_size" => "private/memory.h",
  "get_priv_target" => "private/target.h",
  "get_prival" => "private/entry.h",
  "get_severity" => "private/entry.h",
  "gethostname" => "unistd.h",
  "getpid" => "unistd.h",
  "gmtime" => "time.h",
  "gmtime_r_get_now" => "private/config/have_gmtime_r.h",
  "HANDLE" => "windows.h",
  "HasSubstr" => "gmock/gmock.h",
  "HAVE_GMTIME_R" => "private/config.h",
  "HAVE_SYS_SOCKET_H" => "private/config.h",
  "HAVE_UNISTD_H" => "private/config.h",
  "HAVE_WINDOWS_H" => "private/config.h",
  "HAVE_WINSOCK2_H" => "private/config.h",
  "initialize_insertion_strings" => "private/config/wel_supported.h",
  "LPCSTR" => "windows.h",
  "LOG_INFO" => "syslog.h",
  "malloc" => "stdlib.h",
  "memcpy" => "string.h",
  "memset" => "string.h",
  "MSG_SIMPLE" => "test/function/windows/events.h",
  "new_buffer_target" => "private/target/buffer.h",
  "new_file_target" => "private/target/file.h",
  "new_socket_target" => "private/target/socket.h",
  "new_target" => "private/target.h",
  "new_wel_target" => "private/target/wel.h",
  "NULL" => "stddef.h",
  "perror" => "stdio.h",
  "pid_t" => "sys/types.h",
  "printf" => "stdio.h",
  "public::testing::Test" => "gtest/gtest.h",
  "raise_argument_empty" => "private/error.h",
  "raise_argument_too_big" => "private/error.h",
  "raise_error" => "private/error.h",
  "raise_file_open_failure" => "private/error.h",
  "raise_file_write_failure" => "private/error.h",
  "raise_invalid_id" => "private/error.h",
  "raise_memory_allocation_failure" => "private/error.h",
  "raise_socket_bind_failure" => "private/error.h",
  "raise_target_unsupported" => "private/error.h",
  "raise_wel_close_failure" => "private/error.h",
  "raise_wel_open_failure" => "private/error.h",
  "realloc" => "stdlib.h",
  "realloc_mem" => "private/memory.h",
  "recvfrom" => "sys/socket.h",
  "ReportEvent" => "windows.h",
  "RFC_5424_FULL_DATE_BUFFER_SIZE" => "private/formatter.h",
  "RFC_5424_FULL_TIME_BUFFER_SIZE" => "private/formatter.h",
  "RFC_5424_MAX_PRI_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_TIMESTAMP_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_HOSTNAME_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_PROCID_LENGTH" => "private/formatter.h",
  "RFC_5424_REGEX_STRING" => "test/function/rfc5424.hpp",
  "RFC_5424_TIME_SECFRAC_BUFFER_SIZE" => "private/formatter.h",
  "RFC_5424_TIMESTAMP_BUFFER_SIZE" => "private/formatter.h",
  "RFC_5424_WHOLE_TIME_BUFFER_SIZE" => "private/formatter.h",
  "RUN_ALL_TESTS" => "gtest/gtest.h",
  "send_entry_to_wel_target" => "private/target/wel.h",
  "send_entry_to_unsupported_target" => "private/target.h",
  "sendto" => "sys/socket.h",
  "sendto_buffer_target" => "private/target/buffer.h",
  "sendto_file_target" => "private/target/file.h",
  "sendto_socket_target" => "private/target/socket.h",
  "sendto_unsupported_target" => "private/target.h",
  "set_entry_wel_type" => "private/config/wel_supported.h",
  "SIG_ERR" => "signal.h",
  "SIGINT" => "signal.h",
  "signal" => "signal.h",
  "size_t" => "stddef.h",
  "snprintf" => "stdio.h",
  "socklen_t" => "sys/socket.h",
  "ssize_t" => "sys/types.h",
  "std::cout" => "iostream",
  "std::ifstream" => "fstream",
  "std::regex" => "regex",
  "strbuilder_append_app_name" => "private/entry.h",
  "strbuilder_get_buffer" => "private/strbuilder.h",
  "strftime" => "time.h",
  "strlen" => "string.h",
  "strncpy" => "string.h",
  "struct buffer_target" => "private/target/buffer.h",
  "struct file_target" => "private/target/file.h",
  "struct sockaddr" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "struct socket_target" => "private/target/socket.h",
  "struct strbuilder" => "private/strbuilder.h",
  "struct stumpless_entry" => "stumpless/entry.h",
  "struct stumpless_error" => "stumpless/error.h",
  "struct stumpless_target" => "stumpless/target.h",
  "struct stumpless_version" => "stumpless/version.h",
  "struct timespec" => "time.h",
  "struct tm" => "time.h",
  "struct wel_target" => "private/target/wel.h",
  "stumpless" => "stumpless/target/socket.h",
  "stumpless_add_entry" => "stumpless/target.h",
  "stumpless_add_wel_insertion_string" => "stumpless/config/wel_supported.h",
  "STUMPLESS_BUFFER_TARGET" => "stumpless/target.h",
  "stumpless_close_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_close_file_target" => "stumpless/target/file.h",
  "stumpless_close_socket_target" => "stumpless/target/socket.h",
  "stumpless_close_wel_target" => "stumpless/target/wel.h",
  "stumpless_error_id_t" => "stumpless/error.h",
  "STUMPLESS_FILE_OPEN_FAILURE" => "stumpless/error.h",
  "STUMPLESS_FILE_TARGET" => "stumpless/target.h",
  "STUMPLESS_FILE_WRITE_FAILURE" => "stumpless/error.h",
  "stumpless_get_current_target" => "stumpless/target.h",
  "stumpless_get_error" => "stumpless/error.h",
  "STUMPLESS_MAJOR_VERSION" => "stumpless/config.h",
  "STUMPLESS_MINOR_VERSION" => "stumpless/config.h",
  "STUMPLESS_MAX_TARGET_COUNT" => "stumpless/target.h",
  "stumpless_new_entry" => "stumpless/entry.h",
  "stumpless_open_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_open_file_target" => "stumpless/target/file.h",
  "stumpless_open_socket_target" => "stumpless/target/socket.h",
  "stumpless_open_local_wel_target" => "stumpless/target/wel.h",
  "stumpless_open_remote_wel_target" => "stumpless/target/wel.h",
  "STUMPLESS_PATCH_VERSION" => "stumpless/config.h",
  "stumpless_set_current_target" => "stumpless/target.h",
  "stumpless_set_entry_message" => "stumpless/entry.h",
  "stumpless_set_free" => "stumpless/memory.h",
  "stumpless_set_malloc" => "stumpless/memory.h",
  "stumpless_set_wel_type" => "stumpless/config/wel_supported.h",
  "STUMPLESS_SOCKET_NAME" => "stumpless/target/socket.h",
  "STUMPLESS_SOCKET_NAME_LENGTH" => "stumpless/target/socket.h",
  "STUMPLESS_SOCKET_SOCKET_TARGETS_SUPPORTED" => "stumpless/config.h",
  "STUMPLESS_SOCKET_TARGET" => "stumpless/target.h",
  "STUMPLESS_SYSLOG_H_COMPATIBLE" => "stumpless/config.h",
  "STUMPLESS_WINDOWS_EVENT_LOG_TARGET" => "stumpless/target.h",
  "STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE" => "stumpless/error.h",
  "STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE" => "stumpless/error.h",
  "syslog" => "syslog.h",
  "SYSTEMTIME" => "windows.h",
  "TestRFC5424Compliance" => "test/function/rfc5424.hpp",
  "TestUTF8Compliance" => "test/function/utf8.hpp",
  "time" => "time.h",
  "time_t" => "time.h",
  "uintptr_t" => "stdint.h",
  "unistd_gethostname" => "private/config/have_unistd.h",
  "unistd_getpagesize" => "private/config/have_unistd.h",
  "unistd_getpid" => "private/config/have_unistd.h",
  "windows_getpagesize" => "private/config/have_windows.h",
  "windows_getpid" => "private/config/have_windows.h",
  "winsock2_gethostname" => "private/config/have_winsock2.h",
  "WORD" => "windows.h"
);

my %actual_includes;
my %needed_includes;
my $skipping=0;

foreach my $line (<SOURCE>) {
  if($line =~ m/\*\//){
    $skipping = 0;
    next;
  }

  if($line =~ m/\/\*/ or $skipping){
    $skipping = 1;
    next;
  }

  if($line =~ m/#\s*include\s*["<](.*)[">]/){
    $actual_includes{$1} = 1;
  } else {
    while(my($k, $v) = each %manifest){
      if($line =~ m/\W$k\W/ or $line =~ m/^$k\W/){
        $needed_includes{$v} = $k;
      }
    }
  }
}

print STDERR color('red');

foreach my $include (keys %actual_includes){
  if(!$needed_includes{$include}){
    print STDERR "$file: unnecessary include: $include\n";
  }
}

foreach my $include (keys %needed_includes){
  if(!$actual_includes{$include}){
    my $symbol = $needed_includes{$include};
    print STDERR "$file: missing include: $include due to usage of $symbol\n";
  }
}

print STDERR color('reset');
close(SOURCE);
