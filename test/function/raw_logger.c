#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/raw_logger.h"
#include "private/type.h"

#include "helper.h"

const char * test_raw_string_logger( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( raw_string_logger )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_raw_string_logger( void )
{
  StatusCode status;
  
  status = LogRawString( NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a NULL string did not generate the appropriate error";
  
  status = LogRawString( "Test String #1" );
  if( status != STUMPLESS_SUCCESS )
    return "a simple string could not be logged";
  
  return NULL;
}
