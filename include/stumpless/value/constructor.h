#ifndef __STUMPLESS_VALUE_CONSTRUCTOR_H
#define __STUMPLESS_VALUE_CONSTRUCTOR_H

#include <stumpless/type.h>

Value *
NewValueForBoolean
( const Boolean * );

Value *
NewValueForChar
( char );

Value *
NewValueForCharArray
( const char *, unsigned );

Value *
NewValueForDouble
( double );

Value *
NewValueForDoubleArray
( const double *, unsigned );

Value *
NewValueForFloat
( float );

Value *
NewValueForFloatArray
( const float *, unsigned );

Value *
NewValueForInt
( int );

Value *
NewValueForIntArray
( const int *, unsigned );

Value *
NewValueForLong
( long );

Value *
NewValueForLongArray
( const long *, unsigned );

Value *
NewValueForLongDouble
( long double );

Value *
NewValueForLongDoubleArray
( const long double *, unsigned );

Value *
NewValueForLongLong
( long long );

Value *
NewValueForLongLongArray
( const long long *, unsigned );

Value *
NewValueForShort
( short );

Value *
NewValueForShortArray
( const short *, unsigned );

Value *
NewValueForSignedChar
( signed char );

Value *
NewValueForSignedCharArray
( const signed char *, unsigned );

Value *
NewValueForString
( const char * );

Value *
NewValueForUnsignedChar
( unsigned char );

Value *
NewValueForUnsignedCharArray
( const unsigned char *, unsigned );

Value *
NewValueForUnsignedInt
( unsigned );

Value *
NewValueForUnsignedIntArray
( const unsigned *, unsigned );

Value *
NewValueForUnsignedLong
( unsigned long );

Value *
NewValueForUnsignedLongArray
( const unsigned long *, unsigned );

Value *
NewValueForUnsignedLongLong
( unsigned long long );

Value *
NewValueForUnsignedLongLongArray
( const unsigned long long *, unsigned );

Value *
NewValueForUnsignedShort
( unsigned short );

Value *
NewValueForUnsignedShortArray
( const unsigned short *, unsigned );

#endif
