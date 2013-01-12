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
  stumpless_configuration = NULL;
  StumplessLogDebug( "debug message\n" );
  if( stumpless_configuration == NULL )
    return "configuration was not initialized after StumplessLogDebug";
  
  stumpless_configuration = NULL;
  StumplessLogError( "error message\n" );
  if( stumpless_configuration == NULL )
    return "configuration was not initialized after StumplessLogError";
  
  stumpless_configuration = NULL;
  StumplessLogFatal( "fatal message\n" );
  if( stumpless_configuration == NULL )
    return "configuration was not initialized after StumplessLogFatal";
  
  stumpless_configuration = NULL;
  StumplessLogInfo( "information message\n" );
  if( stumpless_configuration == NULL )
    return "configuration was not initialized after StumplessLogInfo";
  
  stumpless_configuration = NULL;
  StumplessLogWarning( "warning message\n" );
  if( stumpless_configuration == NULL )
    return "configuration was not initialized after StumplessLogWarning";

  return NULL;
}

const char *
test_status_codes( void )
{
  if( StumplessLogDebug( "debug message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogDebug returned a failure code";
  
  if( StumplessLogError( "error message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogError returned a failure code";
  
  if( StumplessLogFatal( "fatal message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogFatal returned a failure code";
  
  if( StumplessLogInfo( "information message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogInfo returned a failure code";
  
  if( StumplessLogWarning( "warning message\n" ) != STUMPLESS_SUCCESS )
    return "StumplessLogWarning returned a failure code";
  
  return NULL;
}
