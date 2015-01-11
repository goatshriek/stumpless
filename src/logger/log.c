#include <stdlib.h>

#include <stumpless/event.h>
#include <stumpless/exception.h>
#include <stumpless/logger/log.h>
#include <stumpless/record.h>
#include <stumpless/value/constructor.h>

#include "private/container/list/adapter.h"
#include "private/container/list/target.h"
#include "private/type.h"

#define LOG_FUNCTIONS( name, type )                                            \
Exception *                                                                       \
Log##name                                                                      \
( Logger *logger, type value )                                                 \
{                                                                              \
  return NULL;                                                                 \
}                                                                              \
                                                                               \
Exception *                                                                       \
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

Exception *
LogRecord
( Logger *logger, Record *record )
{
  if( !logger || !record )
    return RaiseException( "empty argument" );

  RecordThroughAdapterList( logger->adapters, record );
  return LogToTargetList( logger->targets, record );
}

LOG_FUNCTIONS( Short, short )

LOG_FUNCTIONS( SignedChar, signed char )

Exception *
LogString
( Logger *logger, const char *value )
{
  Event *event;
  Record *record;
  RecordAttribute *attribute;

  if( !logger || !value )
    return RaiseException( "empty argument" );

  event = logger->default_event;
  if( !event ){
    event = FindEventByName( "informational" );
    if( !event )
      return RaiseException( "event failure" );
  }

  record = RecordForEvent( event );
  if( !record )
    return RaiseException( "record failure" );

  attribute = malloc( sizeof( RecordAttribute ) );
  if( !attribute )
    return RaiseException( "record failure" );

  SetRecordAttribute( record, "message", NewValueForString( value ) );

  return LogRecord( logger, record );
}

Exception *
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

Exception *
LogVoid
( Logger *logger, const void *value, unsigned length )
{
  return NULL;
}
