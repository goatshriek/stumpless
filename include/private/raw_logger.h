#ifndef STUMPLESS_PRIVATE_RAW_LOGGER_H
#define STUMPLESS_PRIVATE_RAW_LOGGER_H

#include "private/type.h"

Status *
LogRawBoolean( Boolean * );

Status *
LogRawChar( char );

Status *
LogRawDouble( double );

Status *
LogRawFloat( float );

Status *
LogRawInt( int );

Status *
LogRawLong( long );

Status *
LogRawLongDouble( long double );

Status *
LogRawLongLong( long long );

Status *
LogRawShort( short );

Status *
LogRawSignedChar( signed char );

Status *
LogRawString( const char * );

Status *
LogRawUnsignedChar( unsigned char );

Status *
LogRawUnsignedInt( unsigned );

Status *
LogRawUnsignedLong( unsigned long );

Status *
LogRawUnsignedLongLong( unsigned long long );

Status *
LogRawUnsignedShort( unsigned short );

#endif
