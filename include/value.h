#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <types.h>

StumplessValueList *
StumplessArrayValueToValueList( StumplessValue * );

void
StumplessDestroyValue( StumplessValue * );

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
