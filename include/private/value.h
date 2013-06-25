#ifndef STUMPLESS_VALUE_H
#define STUMPLESS_VALUE_H

#include <type.h>

StumplessValueList *
StumplessBooleanArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessBooleanValueIntoString( char *, StumplessValue * );

char *
StumplessBooleanValueToString( StumplessValue * );

StumplessValueList *
StumplessCharArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessCharValueIntoString( char *, StumplessValue * );

char *
StumplessCharValueToString( StumplessValue * );

void
StumplessDestroyValue( StumplessValue * );

StumplessValueList *
StumplessDoubleArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessDoubleValueIntoString( char *, StumplessValue * );

char *
StumplessDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessFloatArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessFloatValueIntoString( char *, StumplessValue * );

char *
StumplessFloatValueToString( StumplessValue * );

StumplessValueList *
StumplessGenericValueToValueList( StumplessValue * );

StumplessValueList *
StumplessIntArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessIntValueIntoString( char *, StumplessValue * );

char *
StumplessIntValueToString( StumplessValue * );

StumplessValueList *
StumplessLongArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessLongValueIntoString( char *, StumplessValue * );

char *
StumplessLongValueToString( StumplessValue * );

StumplessValueList *
StumplessLongDoubleArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessLongDoubleValueIntoString( char *, StumplessValue * );

char *
StumplessLongDoubleValueToString( StumplessValue * );

StumplessValueList *
StumplessLongLongArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessLongLongValueIntoString( char *, StumplessValue * );

char *
StumplessLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessShortArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessShortValueIntoString( char *, StumplessValue * );

char *
StumplessShortValueToString( StumplessValue * );

StumplessValueList *
StumplessSignedCharArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessSignedCharValueIntoString( char *, StumplessValue * );

char *
StumplessSignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessStringArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessStringValueIntoString( char *, StumplessValue * );

char *
StumplessStringValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedCharArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessUnsignedCharValueIntoString( char *, StumplessValue * );

char *
StumplessUnsignedCharValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedIntArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessUnsignedIntValueIntoString( char *, StumplessValue * );

char *
StumplessUnsignedIntValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessUnsignedLongValueIntoString( char *, StumplessValue * );

char *
StumplessUnsignedLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedLongLongArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessUnsignedLongLongValueIntoString( char *, StumplessValue * );

char *
StumplessUnsignedLongLongValueToString( StumplessValue * );

StumplessValueList *
StumplessUnsignedShortArrayValueToValueList( StumplessValue * );

StumplessStatusCode
StumplessUnsignedShortValueIntoString( char *, StumplessValue * );

char *
StumplessUnsignedShortValueToString( StumplessValue * );

StumplessStatusCode
StumplessValueIntoString( char *, StumplessValue * );

StumplessStatusCode
StumplessValueIntoString( char *, StumplessValue * );

char *
StumplessValueToString( StumplessValue * );

#endif
