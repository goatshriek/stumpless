#ifndef __STUMPLESS_VALUE_H
#define __STUMPLESS_VALUE_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( BooleanArrayValueToValueList 
)( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BooleanValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( BooleanValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( CharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CharValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( CharValueToString )
( __STUMPLESS_NAME( Value ) * );

void
__STUMPLESS_NAME( DestroyValue )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( DoubleArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( DoubleValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( DoubleValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( FloatArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( FloatValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( FloatValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( IntArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( IntValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( IntValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( LongValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongDoubleArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongDoubleValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( LongDoubleValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( LongLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LongLongValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( LongLongValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ShortArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ShortValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( ShortValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( SignedCharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SignedCharValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( SignedCharValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( StringArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( StringValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( StringValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedCharArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedCharValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( UnsignedCharValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedIntArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedIntValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( UnsignedIntValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedLongValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( UnsignedLongValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedLongLongArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedLongLongValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( UnsignedLongLongValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( UnsignedShortArrayValueToValueList )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( UnsignedShortValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( UnsignedShortValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ValueIntoString )
( char *, __STUMPLESS_NAME( Value ) * );

char *
__STUMPLESS_NAME( ValueToString )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ValueToValueList )
( __STUMPLESS_NAME( Value ) * );

#endif
