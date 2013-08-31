#include <raw_logger.h>

#include "private/raw_logger.h"

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawBoolean )
( __STUMPLESS_NAME( Boolean ) * raw_boolean )
{
  return LogRawBoolean( raw_boolean );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawChar )
( char raw_char )
{
  return LogRawChar( raw_char );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawDouble )
( double raw_double )
{
  return LogRawDouble( raw_double );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawFloat )
( float raw_float )
{
  return LogRawFloat( raw_float );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawInt )
( int raw_int )
{
  return LogRawInt( raw_int );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawLong )
( long raw_long )
{
  return LogRawLong( raw_long );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawLongDouble )
( long double raw_long_double )
{
  return LogRawLongDouble( raw_long_double );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawLongLong )
( long long raw_long_long )
{
  return LogRawLongLong( raw_long_long );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawShort )
( short raw_short )
{
  return LogRawShort( raw_short );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawSignedChar )
( signed char raw_signed_char )
{
  return LogRawSignedChar( raw_signed_char );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawString )
( const char * raw_string )
{
  return LogRawString( raw_string );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawUnsignedChar )(
 unsigned char raw_unsigned_char )
{
  return LogRawUnsignedChar( raw_unsigned_char );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawUnsignedInt )
( unsigned raw_unsigned_int )
{
  return LogRawUnsignedInt( raw_unsigned_int );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawUnsignedLong )
( unsigned long raw_unsigned_long )
{
  return LogRawUnsignedLong( raw_unsigned_long );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawUnsignedLongLong )
( unsigned long long raw_unsigned_long_long )
{
  return LogRawUnsignedLongLong( raw_unsigned_long_long );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( LogRawUnsignedShort )
( unsigned short raw_unsigned_short )
{
  return LogRawUnsignedShort( raw_unsigned_short );
}
