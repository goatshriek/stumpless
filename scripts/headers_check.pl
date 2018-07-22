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
  "clear_error" => "private/error.h",
  "clock" => "time.h",
  "clock_t" => "sys/types.h",
  "CLOCKS_PER_SEC" => "time.h",
  "close" => "unistd.h",
  "config_gethostname" => "private/config/wrapper.h",
  "cstring_to_sized_string" => "private/strhelper.h",
  "destroy_buffer_target" => "private/target/buffer.h",
  "destroy_socket_target" => "private/target/socket.h",
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
  "get_facility" => "private/entry.h",
  "get_priv_target" => "private/target.h",
  "get_prival" => "private/entry.h",
  "get_severity" => "private/entry.h",
  "gethostname" => "unistd.h",
  "getpid" => "unistd.h",
  "gmtime" => "time.h",
  "HasSubstr" => "gmock/gmock.h",
  "LOG_INFO" => "syslog.h",
  "malloc" => "stdlib.h",
  "memcpy" => "string.h",
  "memset" => "string.h",
  "new_buffer_target" => "private/target/buffer.h",
  "new_rfc5424_timestamp" => "private/formatter.h",
  "new_socket_target" => "private/target/socket.h",
  "NULL" => "stddef.h",
  "perror" => "stdio.h",
  "pid_t" => "sys/types.h",
  "printf" => "stdio.h",
  "raise_invalid_id" => "private/error.h",
  "raise_memory_allocation_failure" => "private/error.h",
  "raise_socket_bind_failure" => "private/error.h",
  "realloc" => "stdlib.h",
  "realloc_mem" => "private/memory.h",
  "recvfrom" => "sys/socket.h",
  "RFC_5424_MAX_PRI_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_TIMESTAMP_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_HOSTNAME_LENGTH" => "private/formatter.h",
  "RFC_5424_MAX_PROCID_LENGTH" => "private/formatter.h",
  "RFC_5424_REGEX_STRING" => "test/function/rfc5424.hpp",
  "RUN_ALL_TESTS" => "gtest/gtest.h",
  "sendto" => "sys/socket.h",
  "sendto_buffer_target" => "private/target/buffer.h",
  "sendto_socket_target" => "private/target/socket.h",
  "SIG_ERR" => "signal.h",
  "SIGINT" => "signal.h",
  "signal" => "signal.h",
  "size_t" => "stddef.h",
  "snprintf" => "stdio.h",
  "socklen_t" => "sys/socket.h",
  "ssize_t" => "sys/types.h",
  "std::cout" => "iostream",
  "std::regex" => "regex",
  "strbuilder_append_app_name" => "private/entry.h",
  "strftime" => "time.h",
  "strlen" => "string.h",
  "struct id_map" => "private/id.h",
  "struct buffer_target" => "private/target/buffer.h",
  "struct sockaddr" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "struct socket_target" => "private/target/socket.h",
  "struct strbuilder" => "private/strbuilder.h",
  "struct stumpless_entry" => "stumpless/entry.h",
  "struct stumpless_error" => "stumpless/error.h",
  "struct stumpless_target" => "stumpless/target.h",
  "struct stumpless_version" => "stumpless/version.h",
  "struct tm" => "time.h",
  "stumpless" => "stumpless/target/socket.h",
  "stumpless_add_entry" => "stumpless/target.h",
  "stumpless_close_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_close_socket_target" => "stumpless/target/socket.h",
  "stumpless_error_id_t" => "stumpless/error.h",
  "stumpless_get_current_target" => "stumpless/target.h",
  "stumpless_get_error" => "stumpless/error.h",
  "stumpless_id_t" => "stumpless/id.h",
  "STUMPLESS_MAX_TARGET_COUNT" => "stumpless/target.h",
  "stumpless_new_entry" => "stumpless/entry.h",
  "stumpless_open_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_open_socket_target" => "stumpless/target/socket.h",
  "stumpless_set_current_target" => "stumpless/target.h",
  "stumpless_set_free" => "stumpless/memory.h",
  "stumpless_set_malloc" => "stumpless/memory.h",
  "STUMPLESS_SOCKET_NAME" => "stumpless/target/socket.h",
  "STUMPLESS_SOCKET_NAME_LENGTH" => "stumpless/target/socket.h",
  "syslog" => "syslog.h",
  "TestRFC5424Compliance" => "test/function/rfc5424.hpp",
  "TestUTF8Compliance" => "test/function/utf8.hpp",
  "time_t" => "time.h"
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
  
  if($line =~ m/#include\s*["<](.*)[">]/){
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
