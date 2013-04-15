#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_to_string( void )
{
  StumplessBoolean * boolean = BuildBoolean();
  if( boolean == NULL )
    return "could not build the test boolean";
  
  char * str = StumplessBooleanToString( NULL );
  if( str != NULL )
    return "the string was not null for a null pointer";
  
  str = StumplessBooleanToString( boolean );
  if( str == NULL )
    return "the string was null for a non-null boolean";
  if( strcmp( str, "true" ) != 0 )
    return "the test boolean value did not yield the correct string output";
  
  return NULL;
}
