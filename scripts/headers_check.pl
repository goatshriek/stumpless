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
  "destroy_buffer_target" => "private/target/buffer.h",
  "destroy_socket_target" => "private/target/socket.h",
  "EXIT_FAILURE" => "stdlib.h",
  "EXIT_SUCCESS" => "stdlib.h",
  "fclose" => "stdio.h",
  "FILE" => "stdio.h",
  "fopen" => "stdio.h",
  "format_entry" => "private/formatter.h",
  "fprintf" => "stdio.h",
  "free" => "stdlib.h",
  "free_mem" => "private/memory.h",
  "getpid" => "unistd.h",
  "gmtime" => "time.h",
  "LOG_INFO" => "syslog.h",
  "malloc" => "stdlib.h",
  "memcpy" => "string.h",
  "new_buffer_target" => "private/target/buffer.h",
  "new_rfc5424_timestamp" => "private/formatter.h",
  "new_socket_target" => "private/target/socket.h",
  "NULL" => "stddef.h",
  "perror" => "stdio.h",
  "pid_t" => "sys/types.h",
  "printf" => "stdio.h",
  "raise_memory_allocation_failure" => "private/error.h",
  "recvfrom" => "sys/socket.h",
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
  "std::regex" => "regex",
  "strftime" => "time.h",
  "struct sockaddr" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "struct buffer_target" => "private/target/buffer.h",
  "struct socket_target" => "private/target/socket.h",
  "struct stumpless_error" => "stumpless/error.h",
  "struct stumpless_target" => "stumpless/target.h",
  "time_t" => "time.h",
  "struct tm" => "time.h",
  "stumpless" => "stumpless.h",
  "stumpless_add_entry" => "stumpless/target.h",
  "stumpless_close_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_close_socket_target" => "stumpless/target/socket.h",
  "stumpless_error_id_t" => "stumpless/error.h",
  "stumpless_get_current_target" => "stumpless/target.h",
  "stumpless_get_error" => "stumpless/error.h",
  "stumpless_id_t" => "stumpless.h",
  "STUMPLESS_MAX_TARGET_COUNT" => "stumpless.h",
  "stumpless_open_buffer_target" => "stumpless/target/buffer.h",
  "stumpless_open_socket_target" => "stumpless/target/socket.h",
  "stumpless_set_current_target" => "stumpless/target.h",
  "STUMPLESS_SOCKET_NAME" => "stumpless.h",
  "STUMPLESS_SOCKET_NAME_LENGTH" => "stumpless.h",
  "syslog" => "syslog.h",
  "TestRFC5424Compliance" => "test/function/rfc5424.hpp",
  "gethostname" => "unistd.h"
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
