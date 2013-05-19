#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <type.h>

StumplessValueList *
StumplessArrayValueToValueList( StumplessValue * );

StumplessValueList *
StumplessBooleanArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessCharArrayValueAsValueList( StumplessValue * );

void
StumplessDestroyValue( StumplessValue * );

StumplessValueList *
StumplessDoubleArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessFloatArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessIntArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessLongArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessLongDoubleArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessLongLongArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessShortArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessSignedCharArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessStringArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessUnsignedCharArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessUnsignedIntArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongLongArrayValueAsValueList( StumplessValue * );

StumplessValueList *
StumplessUnsignedShortArrayValueAsValueList( StumplessValue * );

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
