#include <stdlib.h>
#include <stdio.h>

#include "private/configuration.h"
#include "private/type.h"

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
  if( InitializeConfiguration() != NULL )
    return "initialization method returnedi an error";

  Configuration * configuration = GetConfiguration();
  
  if( configuration == NULL )
    return "configuration was not initialized after call";
  
  if( configuration->file == NULL )
    return "file configuration was not initialized";
  
  if( configuration->http == NULL )
    return "http configuration was not initialized";
  
  if( configuration->sorting == NULL )
    return "sorting configuration was not initialized";
  
  if( configuration->string == NULL )
    return "string configuration was not initialized";
  
  if( configuration->threading == NULL )
    return "multithreading configuration was not initialized";
  
  return NULL;
}
