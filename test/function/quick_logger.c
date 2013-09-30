#include <stdio.h>
#include <stdlib.h>

#include "private/configuration.h"
#include "private/type.h"

#include "helper.h"

const char * test_configuration_initializations( void );
const char * test_status_codes( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( configuration_initializations )
  RUN_TEST( status_codes )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_configuration_initializations( void )
{
  LogDebug( "debug message\n" );
  if( GetConfiguration() == NULL )
    return "configuration was not initialized after LogDebug";
  
  LogError( "error message\n" );
  if( GetConfiguration() == NULL )
    return "configuration was not initialized after LogError";
  
  LogFatal( "fatal message\n" );
  if( GetConfiguration() == NULL )
    return "configuration was not initialized after LogFatal";
  
  LogInfo( "information message\n" );
  if( GetConfiguration() == NULL )
    return "configuration was not initialized after LogInfo";
  
  LogWarning( "warning message\n" );
  if( GetConfiguration() == NULL )
    return "configuration was not initialized after LogWarning";

  return NULL;
}

const char *
test_status_codes( void )
{
  if( LogDebug( "debug message\n" ) != STUMPLESS_SUCCESS )
    return "LogDebug returned a failure code";
  
  if( LogError( "error message\n" ) != STUMPLESS_SUCCESS )
    return "LogError returned a failure code";
  
  if( LogFatal( "fatal message\n" ) != STUMPLESS_SUCCESS )
    return "LogFatal returned a failure code";
  
  if( LogInfo( "information message\n" ) != STUMPLESS_SUCCESS )
    return "LogInfo returned a failure code";
  
  if( LogWarning( "warning message\n" ) != STUMPLESS_SUCCESS )
    return "LogWarning returned a failure code";
  
  return NULL;
}
