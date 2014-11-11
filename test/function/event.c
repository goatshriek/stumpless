#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/event.h>

#include "private/level.h"
#include "test/helper.h"
#include "test/function/event.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;
  
  TEST( AlertEvent )
  //TEST( CriticalEvent )
  //TEST( DebugEvent )
  //TEST( EmergencyEvent )
  //TEST( ErrorEvent )
  //TEST( ErrorEvent )
  TEST( EventToString )
  //TEST( InformationalEvent )
  //TEST( NoticeEvent )
  //TEST( WarningEvent )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAlertEvent
( void )
{
  Event *event = FindEventByName( "alert" );
  if( !event )
    return "could not find the alert event";
  
  if( event->attributes )
    return "the alert Event had attributes";
  
  ASSERT_STRINGS_EQUAL( "alert", event->name, "the Event's name was not alert" )
  
  Level *level = FindLevelByName( "alert" );
  if( !level )
    return "the alert level could not be found";
  
  if( level != event->level )
    return "the Event did not have the appropriate Level";
  
  return NULL;
}

const char *
TestEventToString
( void )
{
  char *description = EventToString( NULL );
  if( description )
    return "the description was not NULL for a NULL pointer";
  
  Event *event = BuildEvent();
  description = EventToString( event );
  if( !description )
    return "the description was NULL for a valid event pointer";
  if( !strstr( description, "Test Event" ) )
    return "the description did not contain the name of the event";
  
  return NULL;
}
