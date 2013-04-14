#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_default_events( void );
const char * test_event_for_level( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( test_default_events, "Default Events Test Failed: %s\n" )
  RUN_TEST( test_event_for_level, "Event For Level Test Failed: %s\n" )
  RUN_TEST( test_to_string, "To String Test Failed: %s\n" )
  
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
  if( event->level == NULL )
    return "debug event's level was null";
  if( event->level->name == NULL )
    return "debug event's level did not have a name";
  if( strcmp( event->level->name, "debug" ) != 0 )
    return "the event does not have a debug level";
  
  event = StumplessGetErrorEvent();
  if( event == NULL )
    return "error event was null";
  if( event->level == NULL )
    return "error event's level was null";
  if( event->level->name == NULL )
    return "error event's level did not have a name";
  if( strcmp( event->level->name, "error" ) != 0 )
    return "the event does not have a error level";
  
  event = StumplessGetFatalEvent();
  if( event == NULL )
    return "fatal event was null";
  if( event->level == NULL )
    return "fatal event's level was null";
  if( event->level->name == NULL )
    return "fatal event's level did not have a name";
  if( strcmp( event->level->name, "fatal" ) != 0 )
    return "the event does not have a fatal level";
  
  event = StumplessGetInfoEvent();
  if( event == NULL )
    return "info event was null";
  if( event->level == NULL )
    return "info event's level was null";
  if( event->level->name == NULL )
    return "info event's level did not have a name";
  if( strcmp( event->level->name, "info" ) != 0 )
    return "the event does not have a info level";
  
  event = StumplessGetWarningEvent();
  if( event == NULL )
    return "warning event was null";
  if( event->level == NULL )
    return "warning event's level was null";
  if( event->level->name == NULL )
    return "warning event's level did not have a name";
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
  level->value = 512;
  level->name = "testing level";
  
  StumplessEvent * event = StumplessEventForLevel( level );
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
  if( strstr( description, "debug" ) == NULL )
    return "the description did not contain the name of the event";
  
  return NULL;
}
