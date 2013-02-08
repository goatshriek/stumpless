#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_default_levels( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_default_levels();
  if( result != NULL ){
    printf( "Default Level Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_to_string();
  if( result != NULL ){
    printf( "To String Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_default_levels( void )
{
  StumplessLevel * debug = StumplessGetDebugLevel();

  if( debug == NULL )
    return "debug level was not properly created";
  if( strcmp( debug->name, "debug" ) != 0 )
    return "debug level was not properly named";
  
  StumplessLevel * error = StumplessGetErrorLevel();
  if( error == NULL )
    return "error level was not properly created";
  if( strcmp( error->name, "error" ) != 0 )
    return "error level was not properly named";
  
  StumplessLevel * fatal = StumplessGetFatalLevel();
  if( fatal == NULL )
    return "fatal level was not properly created";
  if( strcmp( fatal->name, "fatal" ) != 0 )
    return "fatal level was not properly named";
  
  StumplessLevel * info = StumplessGetInfoLevel();
  if( info == NULL )
    return "info level was not properly created";
  if( strcmp( info->name, "info" ) != 0 )
    return "info level was not properly named";
  
  StumplessLevel * warning = StumplessGetWarningLevel();
  if( warning == NULL )
    return "warning level was not properly created";
  if( strcmp( warning->name, "warning" ) != 0 )
    return "warning level was not properly named";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessLevel * level = NULL;
  char * description = StumplessLevelToString( level );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  level = StumplessGetInfoLevel();
  description = StumplessLevelToString( level );
  if( description == NULL )
    return "the description string was null for a non-null level pointer";
  
  return NULL;
}
