use strict;
use warnings;

sub uniq {
  my %seen;
  grep !$seen{$_}++, @_;
}

my $file = "stumpless.c";
open(SOURCE, $file) or die("could not open file");

my %manifest = (
  "memcpy" => "string.h",
  "printf" => "stdio.h",
  "socklen_t" => "sys/socket.h",
  "recvfrom" => "sys/socket.h",
  "perror" => "stdio.h",
  "ssize_t" => "sys/un.h",
  "EXIT_FAILURE" => "stdlib.h",
  "EXIT_SUCCESS" => "stdlib.h",
  "NULL" => "stdlib.h",
  "struct sockaddr" => "sys/socket.h",
  "struct sockaddr_un" => "sys/un.h",
  "stumpless" => "stumpless.h",
  "close" => "unistd.h"
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