#include <stdlib.h>
#include <stdio.h>

#include "private/logger_profile.h"
#include "private/logger_profile_initializer.h"
#include "private/type.h"

#include "helper.h"

const char * test_initialize_by_name( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( initialize_by_name )
  RUN_TEST( initialize_text )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialize_by_name
( void )
{
  return NULL;
}
