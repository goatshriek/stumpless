#ifndef __STUMPLESS_VALUE_CONSTRUCTOR_H
#define __STUMPLESS_VALUE_CONSTRUCTOR_H

#include <stumpless/type.h>

Value *
ValueFromBoolean
( const Boolean * );

Value *
ValueFromChar
( char );

Value *
ValueFromDouble
( double );

Value *
ValueFromFloat
( float );

Value *
ValueFromInt
( int );

Value *
ValueFromLong
( long );

Value *
ValueFromLongDouble
( long double );

Value *
ValueFromLongLong
( long long );

Value *
ValueFromShort
( short );

Value *
ValueFromSignedChar
( signed char );

Value *
ValueFromString
( const char * );

Value *
ValueFromUnsignedChar
( unsigned char );

Value *
ValueFromUnsignedInt
( unsigned );

Value *
ValueFromUnsignedLong
( unsigned long );

Value *
ValueFromUnsignedLongLong
( unsigned long long );

Value *
ValueFromUnsignedShort
( unsigned short );

#endif
