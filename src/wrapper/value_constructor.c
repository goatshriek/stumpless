#include "stumpless/value_constructor.h"

#include "private/value_constructor.h"

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromBoolean )
( const __STUMPLESS_NAME( Boolean ) * boolean )
{
  return ValueFromBoolean( boolean );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromChar )
( char character )
{
  return ValueFromChar( character );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromDouble )
( double num )
{
  return ValueFromDouble( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromFloat )
( float num )
{
  return ValueFromFloat( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromInt )
( int num )
{
  return ValueFromInt( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLong )
( long num )
{
  return ValueFromLong( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLongDouble )
( long double num )
{
  return ValueFromLongDouble( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLongLong )
( long long num )
{
  return ValueFromLongLong( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromShort )
( short num )
{
  return ValueFromShort( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromSignedChar )
( signed char num )
{
  return ValueFromSignedChar( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromString )
( const char * str )
{
  return ValueFromString( str );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedChar )
( unsigned char character )
{
  return ValueFromUnsignedChar( character );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedInt )
( unsigned num )
{
  return ValueFromUnsignedInt( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedLong )
( unsigned long num )
{
  return ValueFromUnsignedLong( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedLongLong )
( unsigned long long num )
{
  return ValueFromUnsignedLongLong( num );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedShort )
( unsigned short num )
{
  return ValueFromUnsignedShort( num );
}
