#include <stdlib.h>

#include <stumpless/config.h>
#include <stumpless/event.h>
#include <stumpless/formatter/text.h>
#include <stumpless/record.h>
#include <stumpless/record_attribute.h>

#ifdef __STUMPLESS_HAVE_TIME_H
#include <time.h>
#endif

#include "private/container/dictionary.h"
#include "private/output.h"
#include "private/type.h"
#include "private/value/constructor.h"

Record *
MergeRecords
( Record *primary, Record *secondary )
{
  if( !primary )
    return secondary;

  if( !secondary )
    return primary;

  if( !primary->event )
    primary->event = secondary->event;

  if( !MergeDictionaries( primary->attributes, secondary->attributes ) )
    return NULL;

  return primary;
}

Record *
NewAlertRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "alert" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewCriticalRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "critical" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewDebugRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "debug" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewEmergencyRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "emergency" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewErrorRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "error" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewInformationalRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "informational" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewNoticeRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "notice" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
NewWarningRecord
( const char *message )
{
  Record *record = RecordForEvent( FindEventByName( "warning" ) );
  if( !record )
    return NULL;

  return SetRecordAttribute( record, "message", NewValueForString( message ) );
}

Record *
RecordForEvent
( Event *event )
{
  if( !event )
    return NULL;

  Record *record = malloc( sizeof( Record ) );
  if( !record )
    return NULL;

  record->event = event;
  record->attributes = NewRecordAttributeDictionaryForEventAttributeDictionary( event->attributes );

#ifdef __STUMPLESS_HAVE_TIME_H
  time( &record->time );
#endif

  return record;
}

char *
RecordToString
( const Record *record )
{
  return OutputToString( RecordToText( NULL, record ) );
}

Record *
SetRecordAttribute
( Record *record, const char *name, Value *value )
{
  if( !record || !name )
    return NULL;

  return record;
}
