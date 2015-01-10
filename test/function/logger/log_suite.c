#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test/function/logger/log_suite.h"
#include "test/helper.h"

int
main
( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( LogString )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestLogString
( void )
{
  return NULL;
}
