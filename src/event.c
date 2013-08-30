#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/event.h"
#include "private/formatted_output.h"
#include "private/level.h"
#include "private/text_formatter.h"
#include "private/type.h"
#include "private/value_list.h"

char *
EventToString
( Event * event )
{
  FormattedOutput * output = EventToText( event );
  return FormattedOutputToString( output );
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
  event->attribute_count = 0;
  
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
