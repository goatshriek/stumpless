#include <stdlib.h>

#include <stumpless/event.h>
#include <stumpless/logger/log.h>
#include <stumpless/record.h>
#include <stumpless/value/constructor.h>

#include "private/container/list/target.h"
#include "private/status.h"
#include "private/type.h"

#define LOG_FUNCTIONS( name, type )                                            \
Status *                                                                       \
Log##name                                                                      \
( Logger *logger, type value )                                                 \
{                                                                              \
  return NULL;                                                                 \
}                                                                              \
                                                                               \
Status *                                                                       \
Send##name##Array                                                              \
( Logger *logger, const type *value, unsigned length )                         \
{                                                                              \
  return NULL;                                                                 \
}

LOG_FUNCTIONS( Char, char )

LOG_FUNCTIONS( Double, double )

LOG_FUNCTIONS( Float, float )

LOG_FUNCTIONS( Int, int )

LOG_FUNCTIONS( Long, long )

LOG_FUNCTIONS( LongDouble, long double )

LOG_FUNCTIONS( LongLong, long long )

Status *
LogRecord
( Logger *logger, Record *record )
{
  if( !logger || !record )
    return RaiseStatus( "empty argument" );

  RecordThroughAdapterList( logger->adapters, record );
  return LogToTargetList( logger->targets, record );
}

LOG_FUNCTIONS( Short, short )

LOG_FUNCTIONS( SignedChar, signed char )

Status *
LogString
( Logger *logger, const char *value )
{
  if( !logger || !value )
    return RaiseStatus( "empty argument" );

  Event *event = logger->default_event;
  if( !event ){
    event = FindEventByName( "informational" );
    if( !event )
      return RaiseStatus( "event failure" );
  }

  Record *record = RecordForEvent( event );
  if( !record )
    return RaiseStatus( "record failure" );

  RecordAttribute *attribute = malloc( sizeof( RecordAttribute ) );
  if( !attribute )
    return RaiseStatus( "record failure" );

  SetRecordAttribute( record, "message", NewValueForString( value ) );

  return LogRecord( logger, record );
}

Status *
LogStringArray
( Logger *logger, const char *value, unsigned length )
{
  return NULL;
}

LOG_FUNCTIONS( UnsignedChar, unsigned char )

LOG_FUNCTIONS( UnsignedInt, unsigned int )

LOG_FUNCTIONS( UnsignedLong, unsigned long )

LOG_FUNCTIONS( UnsignedLongLong, unsigned long long )

LOG_FUNCTIONS( UnsignedShort, unsigned short )

Status *
LogVoid
( Logger *logger, const void *value, unsigned length )
{
  return NULL;
}
