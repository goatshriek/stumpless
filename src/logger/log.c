#include <stdlib.h>

#include <stumpless/event.h>
#include <stumpless/exception.h>
#include <stumpless/logger/log.h>
#include <stumpless/record.h>
#include <stumpless/value/constructor.h>

#include "private/container/list/adapter.h"
#include "private/container/list/target.h"
#include "private/exception/thrower.h"
#include "private/type.h"

#define LOG_FUNCTIONS( name, type )                                            \
Logger *                                                                       \
Log##name                                                                      \
( Logger *logger, type value )                                                 \
{                                                                              \
  return NULL;                                                                 \
}                                                                              \
                                                                               \
Logger *                                                                       \
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

Logger *
LogRecord
( Logger *logger, Record *record )
{
  if( !logger || !record )
    return logger;

  RecordThroughAdapterList( logger->adapters, record );
  LogToTargetList( logger->targets, record );

  return logger;
}

LOG_FUNCTIONS( Short, short )

LOG_FUNCTIONS( SignedChar, signed char )

Logger *
LogString
( Logger *logger, const char *value )
{
  Event *event;
  Record *record;
  RecordAttribute *attribute;

  if( !logger || !value )
    return logger;

  event = logger->default_event;
  if( !event ){
    event = FindEventByName( "informational" );
    // todo refactor to be fault tolerant
    if( !event )
      return logger;
  }

  record = RecordForEvent( event );
  // todo refactor to be fault tolerant
  if( !record )
    return logger;

  attribute = malloc( sizeof( RecordAttribute ) );
  if( !attribute ){
    ThrowMemoryAllocationException();
    return logger;
  }

  SetRecordAttribute( record, "message", NewValueForString( value ) );

  return LogRecord( logger, record );
}

Logger *
LogStringArray
( Logger *logger, const char *value, unsigned length )
{
  return logger;
}

LOG_FUNCTIONS( UnsignedChar, unsigned char )

LOG_FUNCTIONS( UnsignedInt, unsigned int )

LOG_FUNCTIONS( UnsignedLong, unsigned long )

LOG_FUNCTIONS( UnsignedLongLong, unsigned long long )

LOG_FUNCTIONS( UnsignedShort, unsigned short )

Logger *
LogVoid
( Logger *logger, const void *value, unsigned length )
{
  return logger;
}
