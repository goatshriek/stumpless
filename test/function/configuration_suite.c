#include <stdlib.h>
#include <stdio.h>

#include "private/configuration.h"
#include "private/type.h"

#include "test/function/configuration.h"
#include "test/helper.h"

int
main
( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Initialize )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestInitialize
( void )
{
  Configuration *configuration;

  if( InitializeConfiguration() )
    return "initialization method returned an error";

  configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "configuration was not initialized after call" )
  FAIL_IF_NULL( configuration->file, "file configuration was not initialized" )
  FAIL_IF_NULL( configuration->http, "http configuration was not initialized" )
  FAIL_IF_NULL( configuration->sorting, "sorting configuration was not initialized" )
  FAIL_IF_NULL( configuration->string, "string configuration was not initialized" )
  FAIL_IF_NULL( configuration->threading, "multithreading configuration was not initialized" )

  return NULL;
}
