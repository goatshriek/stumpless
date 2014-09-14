#include "private/logger.h"
#include "private/logger/sender.h"
#include "private/type.h"
#include "private/value/constructor.h"

#define SEND_FUNCTIONS( name, type )                                           \
Status *                                                                       \
Send##name                                                                     \
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

SEND_FUNCTIONS( Char, char )

SEND_FUNCTIONS( Double, double )

Status *
SendRecord
( Logger *logger, Record *record )
{
  // multiprocessing will call send to other process
  // logging process will be listening with Listen function

  return ProcessRecord( logger, record );
}

SEND_FUNCTIONS( Float, float )

SEND_FUNCTIONS( Int, int )

Status *
SendLoggerStatus
( Logger *logger )
{
  // sends the status to the check status function

  return NULL;
}

SEND_FUNCTIONS( Long, long )

SEND_FUNCTIONS( LongDouble, long double )

SEND_FUNCTIONS( LongLong, long long )

SEND_FUNCTIONS( Short, short )

SEND_FUNCTIONS( SignedChar, signed char )

Status *
SendString
( Logger *logger, const char *value )
{
  return NULL;
}

SEND_FUNCTIONS( UnsignedChar, unsigned char )

SEND_FUNCTIONS( UnsignedInt, unsigned int )

SEND_FUNCTIONS( UnsignedLong, unsigned long )

SEND_FUNCTIONS( UnsignedLongLong, unsigned long long )

SEND_FUNCTIONS( UnsignedShort, unsigned short )

Status *
SendVoid
( Logger *logger, const void *value, unsigned length, const char *format ){
  return NULL;
}
