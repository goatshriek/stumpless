#ifndef STUMPLESS_RAW_LOGGER_H
#define STUMPLESS_RAW_LOGGER_H

#include <type.h>

StumplessStatusCode
StumplessLogRawBoolean( StumplessBoolean * );

StumplessStatusCode
StumplessLogRawChar( char );

StumplessStatusCode
StumplessLogRawDouble( double );

StumplessStatusCode
StumplessLogRawFloat( float );

StumplessStatusCode
StumplessLogRawInt( int );

StumplessStatusCode
StumplessLogRawLong( long );

StumplessStatusCode
StumplessLogRawLongDouble( long double );

StumplessStatusCode
StumplessLogRawLongLong( long long );

StumplessStatusCode
StumplessLogRawShort( short );

StumplessStatusCode
StumplessLogRawSignedChar( signed char );

StumplessStatusCode
StumplessLogRawString( const char * );

StumplessStatusCode
StumplessLogRawUnsignedChar( unsigned char );

StumplessStatusCode
StumplessLogRawUnsignedInt( unsigned );

StumplessStatusCode
StumplessLogRawUnsignedLong( unsigned long );

StumplessStatusCode
StumplessLogRawUnsignedLongLong( unsigned long long );

StumplessStatusCode
StumplessLogRawUnsignedShort( unsigned short );

#endif
