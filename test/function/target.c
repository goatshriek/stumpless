#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/type.h"

#include "helper.h"

const char * test_log( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;
  
  RUN_TEST( log )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_log
( void )
{
  return NULL;
}
