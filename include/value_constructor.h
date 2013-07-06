#ifndef __STUMPLESS_VALUE_CONSTRUCTOR_H
#define __STUMPLESS_VALUE_CONSTRUCTOR_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromBoolean )( const __STUMPLESS_NAME( Boolean ) * );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromChar )( char );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromDouble )( double );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromFloat )( float );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromInt )( int );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLong )( long );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLongDouble )( long double );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromLongLong )( long long );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromShort )( short );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromSignedChar )( signed char );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromString )( const char * );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedChar )( unsigned char );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedInt )( unsigned );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedLong )( unsigned long );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedLongLong )( unsigned long long );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ValueFromUnsignedShort )( unsigned short );

#endif
