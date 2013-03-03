#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <types.h>

void
StumplessDestroyValue( StumplessValue * );

StumplessValue *
StumplessValueFromString( char * );

StumplessStatusCode
StumplessWriteValueToStream( FILE *, StumplessValue * );

#endif
