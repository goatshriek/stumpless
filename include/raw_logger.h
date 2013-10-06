#ifndef __STUMPLESS_RAW_LOGGER_H
#define __STUMPLESS_RAW_LOGGER_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawBoolean )( __STUMPLESS_NAME( Boolean ) * );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawChar )( char );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawDouble )( double );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawFloat )( float );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawInt )( int );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawLong )( long );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawLongDouble )( long double );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawLongLong )( long long );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawShort )( short );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawSignedChar )( signed char );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawString )( const char * );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawUnsignedChar )( unsigned char );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawUnsignedInt )( unsigned );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawUnsignedLong )( unsigned long );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawUnsignedLongLong )( unsigned long long );

__STUMPLESS_NAME( Status * )
__STUMPLESS_NAME( LogRawUnsignedShort )( unsigned short );

#endif
