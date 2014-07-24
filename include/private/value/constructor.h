#ifndef __STUMPLESS_PRIVATE_VALUE_CONSTRUCTOR_H
#define __STUMPLESS_PRIVATE_VALUE_CONSTRUCTOR_H

#include "private/type.h"

Value *
ValueFromBoolean
( const Boolean * );

Value *
ValueFromChar
( char );

Value *
ValueFromCharArray
( const char *, unsigned );

Value *
ValueFromDouble
( double );

Value *
ValueFromDoubleArray
( const double *, unsigned );

Value *
ValueFromFloat
( float );

Value *
ValueFromFloatArray
( const float *, unsigned );

Value *
ValueFromInt
( int );

Value *
ValueFromIntArray
( const int *, unsigned );

Value *
ValueFromLong
( long );

Value *
ValueFromLongArray
( const long *, unsigned );

Value *
ValueFromLongDouble
( long double );

Value *
ValueFromLongDoubleArray
( const long double *, unsigned );

Value *
ValueFromLongLong
( long long );

Value *
ValueFromLongLongArray
( const long long *, unsigned );

Value *
ValueFromShort
( short );

Value *
ValueFromShortArray
( const short *, unsigned );

Value *
ValueFromSignedChar
( signed char );

Value *
ValueFromSignedCharArray
( const signed char *, unsigned );

Value *
ValueFromString
( const char * );

Value *
ValueFromUnsignedChar
( unsigned char );

Value *
ValueFromUnsignedCharArray
( const unsigned char *, unsigned );

Value *
ValueFromUnsignedInt
( unsigned );

Value *
ValueFromUnsignedIntArray
( const unsigned *, unsigned );

Value *
ValueFromUnsignedLong
( unsigned long );

Value *
ValueFromUnsignedLongArray
( const unsigned long *, unsigned );

Value *
ValueFromUnsignedLongLong
( unsigned long long );

Value *
ValueFromUnsignedLongLongArray
( const unsigned long long *, unsigned );

Value *
ValueFromUnsignedShort
( unsigned short );

Value *
ValueFromUnsignedShortArray
( const unsigned short *, unsigned );

#endif
