#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/level.h"
#include "private/type.h"

#include "helper.h"

const char * test_default_levels( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
 
  RUN_TEST( default_levels )
  RUN_TEST( to_string )
   
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_default_levels( void )
{
  Level * debug = GetDebugLevel();

  if( debug == NULL )
    return "debug level was not properly created";
  if( strcmp( debug->name, "debug" ) != 0 )
    return "debug level was not properly named";
  
  Level * error = GetErrorLevel();
  if( error == NULL )
    return "error level was not properly created";
  if( strcmp( error->name, "error" ) != 0 )
    return "error level was not properly named";
  
  Level * fatal = GetFatalLevel();
  if( fatal == NULL )
    return "fatal level was not properly created";
  if( strcmp( fatal->name, "fatal" ) != 0 )
    return "fatal level was not properly named";
  
  Level * info = GetInfoLevel();
  if( info == NULL )
    return "info level was not properly created";
  if( strcmp( info->name, "info" ) != 0 )
    return "info level was not properly named";
  
  Level * warning = GetWarningLevel();
  if( warning == NULL )
    return "warning level was not properly created";
  if( strcmp( warning->name, "warning" ) != 0 )
    return "warning level was not properly named";
  
  return NULL;
}

const char *
test_to_string( void )
{
  Level * level = NULL;
  char * description = LevelToString( level );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  level = GetInfoLevel();
  description = LevelToString( level );
  if( description == NULL )
    return "the description string was null for a non-null level pointer";
  if( strstr( description, "info" ) == NULL )
    return "the description did not contain the level's description";
  
  return NULL;
}
