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
  Status * status;
  
  status = LogRawString( NULL );
  FAIL_IF_NULL( status, "a NULL string did not generate an error" )
  
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL string did not generate the appropriate status" )
  
  status = LogRawString( "Test String #1" );
  if( status != NULL )
    return "a simple string could not be logged";
  
  return NULL;
}
