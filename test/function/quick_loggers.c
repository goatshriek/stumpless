#include <stdio.h>
#include <stdlib.h>

#include <stumpless.h>

const char * test_configuration_initializations( void );
const char * test_status_codes( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  result = test_configuration_initializations();
  if( result != NULL ){
    printf( "Configuration Initializations Test Failed: %s\n", result );
    failure_count++;
  }

  result = test_status_codes();
  if( result != NULL ){
    printf( "Status Code Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_configuration_initializations( void )
{
  return "still need to write test";
}

const char *
test_status_codes( void )
{
  return NULL;
}
