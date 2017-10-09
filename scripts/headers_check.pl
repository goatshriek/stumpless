#!/usr/bin/perl

use strict;
use warnings;

my $file = "stumplessd.c";
open(SOURCE, $file) or die("could not open file");

my %manifest = (
  "memcpy" => "string.h",
  "printf" => "stdio.h",
  "perror" => "stdio.h",
  "socklen_t" => "sys/socket.h",
  "recvfrom" => "sys/socket.h",
  "struct sockaddr" => "sys/socket.h",
  "sendto" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "close" => "unistd.h",
  "EXIT_FAILURE" => "stdlib.h",
  "EXIT_SUCCESS" => "stdlib.h",
  "NULL" => "stdlib.h",
  "signal" => "signal.h",
  "SIGINT" => "signal.h",
  "SIG_ERR" => "signal.h",
  "stumpless" => "stumpless.h",
  "struct stumpless_target" => "stumpless.h",
  "stumpless_open_target" => "stumpless.h",
  "stumpless_close_target" => "stumpless.h",
  "STUMPLESS_PIPE_NAME" => "stumpless.h",
  "STUMPLESS_PIPE_NAME_LENGTH" => "stumpless.h",
  "STUMPLESS_MAX_TARGET_COUNT" => "stumpless.h",
  "clock_t" => "sys/types.h",
  "ssize_t" => "sys/types.h",
  "clock" => "time.h",
  "CLOCKS_PER_SEC" => "time.h"
);

my %actual_includes;
my %needed_includes;

foreach my $line (<SOURCE>) {
  if($line =~ m/#include\s*["<](.*)[">]/){
    $actual_includes{$1} = 1;
  } else {
    while(my($k, $v) = each %manifest){
      if($line =~ m/\W$k\W/){
        $needed_includes{$v} = 1;
      }
    }
  }
}

foreach my $include (keys %actual_includes){
  if(!$needed_includes{$include}){
  print "unnecessary include: $include\n";
  }
}

foreach my $include (keys %needed_includes){
  if(!$actual_includes{$include}){
    print "missing include: $include\n";
  }  
}

close(SOURCE);
