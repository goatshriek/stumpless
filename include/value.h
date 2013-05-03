#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <types.h>

void
StumplessDestroyValue( StumplessValue * );

StumplessValue *
StumplessValueFromString( const char * );

StumplessValue *
StumplessValueFromUnsignedInt( unsigned );

StumplessStatusCode
StumplessValueIntoString( char *, StumplessValue * );

unsigned short
StumplessValueIsArray( StumplessValue * );

char *
StumplessValueToString( StumplessValue * );

const char *
StumplessValueTypeDefaultFormat( StumplessValueType );

StumplessStatusCode
StumplessWriteValueToStream( FILE *, StumplessValue * );

#endif
