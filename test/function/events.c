#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_to_string();
  if( result != NULL ){
    printf( "To String test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_to_string( void )
{
  StumplessEvent * event = NULL;
  char * description = StumplessEventToString( event );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  return NULL;
}
