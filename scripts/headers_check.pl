#!/usr/bin/perl

use strict;
use warnings;

my $file = $ARGV[0];
open(SOURCE, $file) or die("could not open file: $file");

my %manifest = (
  "AF_UNIX" => "sys/socket.h",
  "alloc_mem" => "private/memory.h",
  "clear_error" => "private/error.h",
  "clock" => "time.h",
  "clock_t" => "sys/types.h",
  "CLOCKS_PER_SEC" => "time.h",
  "close" => "unistd.h",
  "EXIT_FAILURE" => "stdlib.h",
  "EXIT_SUCCESS" => "stdlib.h",
  "fclose" => "stdio.h",
  "FILE" => "stdio.h",
  "fopen" => "stdio.h",
  "fprintf" => "stdio.h",
  "free" => "stdlib.h",
  "free_mem" => "private/memory.h",
  "LOG_INFO" => "syslog.h",
  "malloc" => "stdlib.h",
  "memcpy" => "string.h",
  "NULL" => "stddef.h",
  "perror" => "stdio.h",
  "printf" => "stdio.h",
  "raise_memory_allocation_failure" => "private/error.h",
  "recvfrom" => "sys/socket.h",
  "sendto" => "sys/socket.h",
  "SIG_ERR" => "signal.h",
  "SIGINT" => "signal.h",
  "signal" => "signal.h",
  "size_t" => "stddef.h",
  "socklen_t" => "sys/socket.h",
  "ssize_t" => "sys/types.h",
  "struct sockaddr" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "struct stumpless_error" => "stumpless/error.h",
  "struct stumpless_target" => "stumpless.h",
  "struct target" => "private/target.h",
  "stumpless" => "stumpless.h",
  "stumpless_close_target" => "stumpless.h",
  "stumpless_error_id_t" => "stumpless/error.h",
  "stumpless_get_error" => "stumpless/error.h",
  "STUMPLESS_MAX_TARGET_COUNT" => "stumpless.h",
  "stumpless_open_target" => "stumpless.h",
  "STUMPLESS_PIPE_NAME" => "stumpless.h",
  "STUMPLESS_PIPE_NAME_LENGTH" => "stumpless.h",
  "syslog" => "syslog.h"
);

my %actual_includes;
my %needed_includes;
my $skipping=0;

foreach my $line (<SOURCE>) {
  if($line =~ m/\*\//){
    $skipping = 0;
  }
  
  if($line =~ m/\/\*/ or $skipping){
    $skipping = 1;
    next;
  }
  
  if($line =~ m/#include\s*["<](.*)[">]/){
    $actual_includes{$1} = 1;
  } else {
    while(my($k, $v) = each %manifest){
      if($line =~ m/\W$k\W/){
        $needed_includes{$v} = $k;
      }
    }
  }
}

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

close(SOURCE);
