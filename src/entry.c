#include <stdlib.h>

#include "private/entry.h"
#include "private/event.h"
#include "private/output.h"
#include "private/text_formatter.h"
#include "private/type.h"

#include "private/list/entry_attribute.h"
#include "private/list/value.h"

char *
EntryToString
( Entry * entry )
{
  Output * output =  EntryToText( entry, NULL );
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
  // todo set attributes to defaults if present
  
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

Entry *
MergeEntries
( Entry * primary, Entry * secondary )
{
  if( primary == NULL )
    return secondary;
  
  if( secondary == NULL )
    return primary;
  
  if( primary->description == NULL )
    primary->description = secondary->description;
  
  if( primary->event == NULL )
    primary->event = secondary->event;
  
  if( MergeEntryAttributeLists( primary->attributes, secondary->attributes ) == NULL )
    return NULL;
  
  return primary;
}
