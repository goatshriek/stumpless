#include "private/logger/log.h"
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

LOG_FUNCTIONS( Short, short )

LOG_FUNCTIONS( SignedChar, signed char )

Status *
LogString
( Logger *logger, const char *value )
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
( Logger *logger, const void *value, unsigned length ){
  return NULL;
}
