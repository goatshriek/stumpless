#ifndef STUMPLESS_PRIVATE_RAW_LOGGER_H
#define STUMPLESS_PRIVATE_RAW_LOGGER_H

#include "private/type.h"

StatusCode
LogRawBoolean( Boolean * );

StatusCode
LogRawChar( char );

StatusCode
LogRawDouble( double );

StatusCode
LogRawFloat( float );

StatusCode
LogRawInt( int );

StatusCode
LogRawLong( long );

StatusCode
LogRawLongDouble( long double );

StatusCode
LogRawLongLong( long long );

StatusCode
LogRawShort( short );

StatusCode
LogRawSignedChar( signed char );

StatusCode
LogRawString( const char * );

StatusCode
LogRawUnsignedChar( unsigned char );

StatusCode
LogRawUnsignedInt( unsigned );

StatusCode
LogRawUnsignedLong( unsigned long );

StatusCode
LogRawUnsignedLongLong( unsigned long long );

StatusCode
LogRawUnsignedShort( unsigned short );

#endif
