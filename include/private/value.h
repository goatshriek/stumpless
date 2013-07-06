#ifndef STUMPLESS_PRIVATE_VALUE_H
#define STUMPLESS_PRIVATE_VALUE_H

#include <type.h>

ValueList *
BooleanArrayValueToValueList( Value * );

StatusCode
BooleanValueIntoString( char *, Value * );

char *
BooleanValueToString( Value * );

ValueList *
CharArrayValueToValueList( Value * );

StatusCode
CharValueIntoString( char *, Value * );

char *
CharValueToString( Value * );

void
DestroyValue( Value * );

ValueList *
DoubleArrayValueToValueList( Value * );

StatusCode
DoubleValueIntoString( char *, Value * );

char *
DoubleValueToString( Value * );

ValueList *
FloatArrayValueToValueList( Value * );

StatusCode
FloatValueIntoString( char *, Value * );

char *
FloatValueToString( Value * );

ValueList *
IntArrayValueToValueList( Value * );

StatusCode
IntValueIntoString( char *, Value * );

char *
IntValueToString( Value * );

ValueList *
LongArrayValueToValueList( Value * );

StatusCode
LongValueIntoString( char *, Value * );

char *
LongValueToString( Value * );

ValueList *
LongDoubleArrayValueToValueList( Value * );

StatusCode
LongDoubleValueIntoString( char *, Value * );

char *
LongDoubleValueToString( Value * );

ValueList *
LongLongArrayValueToValueList( Value * );

StatusCode
LongLongValueIntoString( char *, Value * );

char *
LongLongValueToString( Value * );

ValueList *
ShortArrayValueToValueList( Value * );

StatusCode
ShortValueIntoString( char *, Value * );

char *
ShortValueToString( Value * );

ValueList *
SignedCharArrayValueToValueList( Value * );

StatusCode
SignedCharValueIntoString( char *, Value * );

char *
SignedCharValueToString( Value * );

ValueList *
StringArrayValueToValueList( Value * );

StatusCode
StringValueIntoString( char *, Value * );

char *
StringValueToString( Value * );

ValueList *
UnsignedCharArrayValueToValueList( Value * );

StatusCode
UnsignedCharValueIntoString( char *, Value * );

char *
UnsignedCharValueToString( Value * );

ValueList *
UnsignedIntArrayValueToValueList( Value * );

StatusCode
UnsignedIntValueIntoString( char *, Value * );

char *
UnsignedIntValueToString( Value * );

ValueList *
UnsignedLongArrayValueToValueList( Value * );

StatusCode
UnsignedLongValueIntoString( char *, Value * );

char *
UnsignedLongValueToString( Value * );

ValueList *
UnsignedLongLongArrayValueToValueList( Value * );

StatusCode
UnsignedLongLongValueIntoString( char *, Value * );

char *
UnsignedLongLongValueToString( Value * );

ValueList *
UnsignedShortArrayValueToValueList( Value * );

StatusCode
UnsignedShortValueIntoString( char *, Value * );

char *
UnsignedShortValueToString( Value * );

StatusCode
ValueIntoString( char *, Value * );

StatusCode
ValueIntoString( char *, Value * );

char *
ValueToString( Value * );

ValueList *
ValueToValueList( Value * );

#endif
