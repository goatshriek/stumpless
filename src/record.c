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
  Output * output =  RecordToText( NULL, record );
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
MergeRecords
( Record *primary, Record *secondary )
{
  if( !primary )
    return secondary;
  
  if( !secondary )
    return primary;
  
  if( !primary->message )
    primary->message = secondary->message;
  
  if( !primary->event )
    primary->event = secondary->event;
  
  if( !MergeRecordAttributeLists( primary->attributes, secondary->attributes ) )
    return NULL;
  
  return primary;
}
