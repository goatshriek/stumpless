#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_default_events( void );
const char * test_event_for_level( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
 
  result = test_default_events();
  if( result != NULL ){
    printf( "Default Events Test Failed: %s\n", result );
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
test_default_events( void )
{
  StumplessEvent * event = StumplessGetDebugEvent();
  if( event == NULL )
    return "debug event was null";
  if( strcmp( event->level->name, "debug" ) != 0 )
    return "the event does not have a debug level";
  
  event = StumplessGetErrorEvent();
  if( event == NULL )
    return "error event was null";
  if( strcmp( event->level->name, "error" ) != 0 )
    return "the event does not have a error level";
  
  event = StumplessGetFatalEvent();
  if( event == NULL )
    return "fatal event was null";
  if( strcmp( event->level->name, "fatal" ) != 0 )
    return "the event does not have a fatal level";
  
  event = StumplessGetInfoEvent();
  if( event == NULL )
    return "info event was null";
  if( strcmp( event->level->name, "info" ) != 0 )
    return "the event does not have a info level";
  
  event = StumplessGetWarningEvent();
  if( event == NULL )
    return "warning event was null";
  if( strcmp( event->level->name, "warning" ) != 0 )
    return "the event does not have a warning level";
  
  return NULL;
}

const char *
test_event_for_level( void )
{
  StumplessLevel * level = malloc( sizeof( StumplessLevel ) );
  if( level == NULL )
    return "memory allocation failure during testing";
  level->level = 512;
  level->name = "testing level";
  
  StumplessEvent * event = StumplessGetEventForLevel( level );
  if( event == NULL )
    return "event could not be created";
  if( event->level != level )
    return "event did not have the requested level";
  if( event->name != NULL )
    return "the event was not given a blank name";
  if( event->attribute_count != 0 )
    return "the event had a non-zero attribute count";
  
  return NULL;
}

const char *
test_to_string( void )
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
