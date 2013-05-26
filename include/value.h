#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <type.h>

StumplessValueList * // todo remove this function
StumplessArrayValueToValueList( StumplessValue * );

StumplessValueList *
StumplessBooleanArrayValueToValueList( StumplessValue * );

char *
StumplessBooleanValueToString( StumplessValue * );

StumplessValueList *
StumplessCharArrayValueToValueList( StumplessValue * );

char *
StumplessCharValueToString( StumplessValue * );

void
StumplessDestroyValue( StumplessValue * );

StumplessValueList *
StumplessDoubleArrayValueToValueList( StumplessValue * );

char *
StumplessDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessFloatArrayValueToValueList( StumplessValue * );

char *
StumplessFloatValueToString( StumplessValue * );

StumplessValueList *
StumplessGenericValueToValueList( StumplessValue * );

StumplessValueList *
StumplessIntArrayValueToValueList( StumplessValue * );

char *
StumplessIntValueToString( StumplessValue * );

StumplessValueList *
StumplessLongArrayValueToValueList( StumplessValue * );

char *
StumplessLongValueToString( StumplessValue * );

StumplessValueList *
StumplessLongDoubleArrayValueToValueList( StumplessValue * );

char *
StumplessLongDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessLongLongArrayValueToValueList( StumplessValue * );

char *
StumplessLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessShortArrayValueToValueList( StumplessValue * );

char *
StumplessShortValueToString( StumplessValue * );

StumplessValueList *
StumplessSignedCharArrayValueToValueList( StumplessValue * );

char *
StumplessSignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessStringArrayValueToValueList( StumplessValue * );

char *
StumplessStringValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedCharArrayValueToValueList( StumplessValue * );

char *
StumplessUnsignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedIntArrayValueToValueList( StumplessValue * );

char *
StumplessUnsignedIntValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongArrayValueToValueList( StumplessValue * );

char *
StumplessUnsignedLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongLongArrayValueToValueList( StumplessValue * );

char *
StumplessUnsignedLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedShortArrayValueToValueList( StumplessValue * );

char *
StumplessUnsignedShortValueToString( StumplessValue * );

StumplessStatusCode
StumplessValueIntoString( char *, StumplessValue * );

unsigned short // todo remove this function
StumplessValueIsArray( StumplessValue * );

char *
StumplessValueToString( StumplessValue * );

StumplessStatusCode // todo remove this function
StumplessWriteValueToStream( FILE *, StumplessValue * );

#endif
