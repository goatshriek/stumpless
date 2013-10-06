#ifndef STUMPLESS_PRIVATE_VALUE_H
#define STUMPLESS_PRIVATE_VALUE_H

#include "private/type.h"

ValueList *
BooleanArrayValueToValueList
( Value * );

Status *
BooleanValueIntoString
( char *, Value * );

char *
BooleanValueToString
( Value * );

ValueList *
CharArrayValueToValueList
( Value * );

Status *
CharValueIntoString
( char *, Value * );

char *
CharValueToString
( Value * );

void
DestroyValue
( Value * );

ValueList *
DoubleArrayValueToValueList
( Value * );

Status *
DoubleValueIntoString
( char *, Value * );

char *
DoubleValueToString
( Value * );

ValueList *
FloatArrayValueToValueList
( Value * );

Status *
FloatValueIntoString
( char *, Value * );

char *
FloatValueToString
( Value * );

ValueList *
IntArrayValueToValueList
( Value * );

Status *
IntValueIntoString
( char *, Value * );

char *
IntValueToString
( Value * );

ValueList *
LongArrayValueToValueList
( Value * );

Status *
LongValueIntoString
( char *, Value * );

char *
LongValueToString
( Value * );

ValueList *
LongDoubleArrayValueToValueList
( Value * );

Status *
LongDoubleValueIntoString
( char *, Value * );

char *
LongDoubleValueToString
( Value * );

ValueList *
LongLongArrayValueToValueList
( Value * );

Status *
LongLongValueIntoString
( char *, Value * );

char *
LongLongValueToString
( Value * );

ValueList *
ShortArrayValueToValueList
( Value * );

Status *
ShortValueIntoString
( char *, Value * );

char *
ShortValueToString
( Value * );

ValueList *
SignedCharArrayValueToValueList
( Value * );

Status *
SignedCharValueIntoString
( char *, Value * );

char *
SignedCharValueToString
( Value * );

ValueList *
StringArrayValueToValueList
( Value * );

Status *
StringValueIntoString
( char *, Value * );

char *
StringValueToString
( Value * );

ValueList *
UnsignedCharArrayValueToValueList
( Value * );

Status *
UnsignedCharValueIntoString
( char *, Value * );

char *
UnsignedCharValueToString
( Value * );

ValueList *
UnsignedIntArrayValueToValueList
( Value * );

Status *
UnsignedIntValueIntoString
( char *, Value * );

char *
UnsignedIntValueToString
( Value * );

ValueList *
UnsignedLongArrayValueToValueList
( Value * );

Status *
UnsignedLongValueIntoString
( char *, Value * );

char *
UnsignedLongValueToString
( Value * );

ValueList *
UnsignedLongLongArrayValueToValueList
( Value * );

Status *
UnsignedLongLongValueIntoString
( char *, Value * );

char *
UnsignedLongLongValueToString
( Value * );

ValueList *
UnsignedShortArrayValueToValueList
( Value * );

Status *
UnsignedShortValueIntoString
( char *, Value * );

char *
UnsignedShortValueToString
( Value * );

Status *
ValueIntoString
( char *, Value * );

Status *
ValueIntoString
( char *, Value * );

char *
ValueToString
( Value * );

ValueList *
ValueToValueList
( Value * );

#endif
