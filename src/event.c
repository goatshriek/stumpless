#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/event.h"
#include "private/level.h"
#include "private/output.h"
#include "private/text_formatter.h"
#include "private/type.h"

#include "private/list/value.h"

char *
EventToString
( Event * event )
{
  Output * output = EventToText( event );
  return OutputToString( output );
}

Event *
GetDebugEvent( void )
{
  return EventForLevel( GetDebugLevel() );
}

Event *
GetErrorEvent( void )
{
  return EventForLevel( GetErrorLevel() );
}

Event *
EventForLevel( Level * level )
{
  if( level == NULL )
    return NULL;
  
  Event * event = malloc( sizeof( Event ) );
  if( event == NULL )
    return NULL;
  
  event->name = NULL;
  event->level = level;
  event->attributes = NULL;
  
  return event;
}

Event *
GetFatalEvent( void )
{
  return EventForLevel( GetFatalLevel() );
}

Event *
GetInfoEvent( void )
{
  return EventForLevel( GetInfoLevel() );
}

Event *
GetWarningEvent( void )
{
  return EventForLevel( GetWarningLevel() );
}
