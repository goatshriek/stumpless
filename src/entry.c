#include <stdlib.h>

#include "private/entry.h"
#include "private/event.h"
#include "private/output.h"
#include "private/text_formatter.h"
#include "private/type.h"
#include "private/value_list.h"

char *
EntryToString
( Entry * entry )
{
  Output * output =  EntryToText( entry );
  return OutputToString( output ); 
}

Entry *
GetDebugEntry
( void )
{
  return EntryForEvent( GetDebugEvent() );
}

Entry *
EntryForEvent
( Event * event )
{
  if( event == NULL )
    return NULL;
  
  Entry * entry = malloc( sizeof( Entry ) );
  
  if( entry == NULL )
    return NULL;
  
  entry->event = event;
  
  return entry;
}

Entry *
GetErrorEntry
( void )
{
  return EntryForEvent( GetErrorEvent() );
}

Entry *
GetFatalEntry
( void )
{
  return EntryForEvent( GetFatalEvent() );
}

Entry *
GetInfoEntry
( void )
{
  return EntryForEvent( GetInfoEvent() );
}

Entry *
GetWarningEntry
( void )
{
  return EntryForEvent( GetWarningEvent() );
}
