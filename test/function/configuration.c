#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

#include "helper.h"

const char * test_initialization( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( initialization )

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
  
  if( stumpless_configuration->file == NULL )
    return "file configuration was not initialized";
  
  if( stumpless_configuration->http == NULL )
    return "http configuration was not initialized";
  
  if( stumpless_configuration->multithreading == NULL )
    return "multithreading configuration was not initialized";
  
  if( stumpless_configuration->sorting == NULL )
    return "sorting configuration was not initialized";
  
  if( stumpless_configuration->string == NULL )
    return "string configuration was not initialized";
  
  return NULL;
}
