#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_event_formatter( void );
const char * test_level_formatter( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_event_formatter();
  if( result != NULL ){
    printf( "Event Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_level_formatter();
  if( result != NULL ){
    printf( "Level Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_event_formatter( void )
{
  StumplessEvent * event = NULL;
  char * description = StumplessEventToString( event );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  event = StumplessGetDebugEvent();
  description = StumplessEventToString( event );
  if( description == NULL )
    return "the description was null for a valid event pointer";
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  StumplessLevel * level = NULL;
  char * description = StumplessGetLevelAsText( level );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  level = StumplessGetInfoLevel();
  description = StumplessGetLevelAsText( level );
  if( description == NULL )
    return "the description string was null for a valid level pointer";
  
  return NULL;
}
