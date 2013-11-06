#include "stumpless/value.h"

#include "private/value.h"

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( BooleanArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return BooleanArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BooleanValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return BooleanValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( BooleanValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return BooleanValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( CharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return CharArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CharValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return CharValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( CharValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return CharValueToString( value );
}

void
__STUMPLESS_NAME( DestroyValue )
( __STUMPLESS_NAME( Value ) * value )
{
  DestroyValue( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( DoubleArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return DoubleArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( DoubleValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return DoubleValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( DoubleValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return DoubleValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( FloatArrayValueToValueList )
( __STUMPLESS_NAME( Value ) *  value)
{
  return FloatArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( FloatValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return FloatValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( FloatValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return FloatValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return ValueToValueList( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( IntArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return IntArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( IntValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return IntValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( IntValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return IntValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return LongValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( LongValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongDoubleArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongDoubleArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongDoubleValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return LongDoubleValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( LongDoubleValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongDoubleValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongLongArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongLongValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return LongLongValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( LongLongValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return LongLongValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ShortArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return ShortArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ShortValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return ShortValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( ShortValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return ShortValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( SignedCharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return SignedCharArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SignedCharValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return SignedCharValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( SignedCharValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return SignedCharValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( StringArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return StringArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( StringValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return StringValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( StringValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return StringValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedCharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedCharArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedCharValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedCharValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( UnsignedCharValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedCharValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedIntArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedIntArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedIntValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedIntValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( UnsignedIntValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedIntValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedLongValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( UnsignedLongValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedLongLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongLongArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedLongLongValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongLongValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( UnsignedLongLongValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedLongLongValueToString( value );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedShortArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedShortArrayValueToValueList( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedShortValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedShortValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( UnsignedShortValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return UnsignedShortValueToString( value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ValueIntoString )
( char * str, __STUMPLESS_NAME( Value ) * value )
{
  return ValueIntoString( str, value );
}

char *
__STUMPLESS_NAME( ValueToString )
( __STUMPLESS_NAME( Value ) * value )
{
  return ValueToString( value );
}
