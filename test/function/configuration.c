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
  FAIL_IF_NULL( configuration, "configuration was not initialized after call" )
  FAIL_IF_NULL( configuration->default_file, "file configuration was not initialized" )
  FAIL_IF_NULL( configuration->default_http, "http configuration was not initialized" )
  FAIL_IF_NULL( configuration->sorting, "sorting configuration was not initialized" )
  FAIL_IF_NULL( configuration->string, "string configuration was not initialized" )
  FAIL_IF_NULL( configuration->threading, "multithreading configuration was not initialized" )
  
  return NULL;
}
