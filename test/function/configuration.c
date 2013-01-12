#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

const char * test_initialization( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  result = test_initialization();
  if( result != NULL ){
    printf( "Initialization Test Failed: %s\n", result );
    failure_count++;
  }

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialization( void )
{
  if( stumpless_configuration != NULL )
    return "starting configuration was not empty";
  
  if( StumplessInitializeConfiguration() != STUMPLESS_SUCCESS )
    return "initialization method returned error code";

  if( stumpless_configuration == NULL )
    return "configuration was not initialized after call";
  
  return NULL;
}
