#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <type.h>

StumplessValueList * // todo remove this function
StumplessArrayValueToValueList( StumplessValue * );

StumplessValueList *
StumplessBooleanArrayValueAsValueList( StumplessValue * );

char *
StumplessBooleanValueToString( StumplessValue * );

StumplessValueList *
StumplessCharArrayValueAsValueList( StumplessValue * );

char *
StumplessCharValueToString( StumplessValue * );

void
StumplessDestroyValue( StumplessValue * );

StumplessValueList *
StumplessDoubleArrayValueAsValueList( StumplessValue * );

char *
StumplessDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessFloatArrayValueAsValueList( StumplessValue * );

char *
StumplessFloatValueToString( StumplessValue * );

StumplessValueList *
StumplessIntArrayValueAsValueList( StumplessValue * );

char *
StumplessIntValueToString( StumplessValue * );

StumplessValueList *
StumplessLongArrayValueAsValueList( StumplessValue * );

char *
StumplessLongValueToString( StumplessValue * );

StumplessValueList *
StumplessLongDoubleArrayValueAsValueList( StumplessValue * );

char *
StumplessLongDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessLongLongArrayValueAsValueList( StumplessValue * );

char *
StumplessLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessShortArrayValueAsValueList( StumplessValue * );

char *
StumplessShortValueToString( StumplessValue * );

StumplessValueList *
StumplessSignedCharArrayValueAsValueList( StumplessValue * );

char *
StumplessSignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessStringArrayValueAsValueList( StumplessValue * );

char *
StumplessStringValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedCharArrayValueAsValueList( StumplessValue * );

char *
StumplessUnsignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedIntArrayValueAsValueList( StumplessValue * );

char *
StumplessUnsignedIntValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongArrayValueAsValueList( StumplessValue * );

char *
StumplessUnsignedLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongLongArrayValueAsValueList( StumplessValue * );

char *
StumplessUnsignedLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedShortArrayValueAsValueList( StumplessValue * );

char *
StumplessUnsignedShortValueToString( StumplessValue * );

StumplessStatusCode // todo remove this function
StumplessValueIntoString( char *, StumplessValue * );

unsigned short
StumplessValueIsArray( StumplessValue * );

char * // todo remove this function
StumplessValueToString( StumplessValue * );

const char *  // todo remove this function
StumplessValueTypeDefaultFormat( StumplessValueType );

StumplessStatusCode
StumplessWriteValueToStream( FILE *, StumplessValue * );

#endif
