#include <stdlib.h>

#include "private/record.h"
#include "private/event.h"
#include "private/output.h"
#include "private/type.h"

#include "private/formatter/text.h"

#include "private/container/list/record_attribute.h"
#include "private/container/list/value.h"

char *
RecordToString
( Record * record )
{
  Output * output =  RecordToText( record, NULL );
  return OutputToString( output ); 
}

Record *
GetDebugRecord
( void )
{
  return RecordForEvent( GetDebugEvent() );
}

Record *
RecordForEvent
( Event * event )
{
  if( !event )
    return NULL;
  
  Record * record = malloc( sizeof( Record ) );
  if( !record )
    return NULL;
  
  record->event = event;
  record->attributes = RecordAttributeListForEventAttributeList(event->attributes );

  return record;
}

Record *
GetErrorRecord
( void )
{
  return RecordForEvent( GetErrorEvent() );
}

Record *
GetFatalRecord
( void )
{
  return RecordForEvent( GetFatalEvent() );
}

Record *
GetInfoRecord
( void )
{
  return RecordForEvent( GetInfoEvent() );
}

Record *
GetWarningRecord
( void )
{
  return RecordForEvent( GetWarningEvent() );
}

Record *
MergeEntries
( Record * primary, Record * secondary )
{
  if( primary == NULL )
    return secondary;
  
  if( secondary == NULL )
    return primary;
  
  if( primary->description == NULL )
    primary->description = secondary->description;
  
  if( primary->event == NULL )
    primary->event = secondary->event;
  
  if( MergeRecordAttributeLists( primary->attributes, secondary->attributes ) == NULL )
    return NULL;
  
  return primary;
}
