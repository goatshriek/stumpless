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
( const char *, size_t );

Value *
NewValueForDouble
( double );

Value *
NewValueForDoubleArray
( const double *, size_t );

Value *
NewValueForFloat
( float );

Value *
NewValueForFloatArray
( const float *, size_t );

Value *
NewValueForInt
( int );

Value *
NewValueForIntArray
( const int *, size_t );

Value *
NewValueForLong
( long );

Value *
NewValueForLongArray
( const long *, size_t );

Value *
NewValueForLongDouble
( long double );

Value *
NewValueForLongDoubleArray
( const long double *, size_t );

Value *
NewValueForLongLong
( long long );

Value *
NewValueForLongLongArray
( const long long *, size_t );

Value *
NewValueForShort
( short );

Value *
NewValueForShortArray
( const short *, size_t );

Value *
NewValueForSignedChar
( signed char );

Value *
NewValueForSignedCharArray
( const signed char *, size_t );

Value *
NewValueForString
( const char * );

Value *
NewValueForUnsignedChar
( unsigned char );

Value *
NewValueForUnsignedCharArray
( const unsigned char *, size_t );

Value *
NewValueForUnsignedInt
( unsigned );

Value *
NewValueForUnsignedIntArray
( const unsigned *, size_t );

Value *
NewValueForUnsignedLong
( unsigned long );

Value *
NewValueForUnsignedLongArray
( const unsigned long *, size_t );

Value *
NewValueForUnsignedLongLong
( unsigned long long );

Value *
NewValueForUnsignedLongLongArray
( const unsigned long long *, size_t );

Value *
NewValueForUnsignedShort
( unsigned short );

Value *
NewValueForUnsignedShortArray
( const unsigned short *, size_t );

/**
 * Creates a new Value with the provided void pointer.
 *
 * @param pointer the void pointer to create the Value for
 *
 * @return a new Value with the void pointer provided
 */
Value *
NewValueForVoid
( void *pointer );

#endif
